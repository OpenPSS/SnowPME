#include <Sce/Pss/Core/Memory/HeapAllocator.hpp>
#include <string>
#include <iostream>
#include <mutex>
#include <LibShared.hpp>

using namespace Shared::Debug;

namespace Sce::Pss::Core::Memory {

	HeapAllocator::HeapAllocator(size_t heapSize, const std::string& heapName) {
		this->HeapName = heapName;
		this->TotalHeapSize = heapSize;

		this->heapAllocations = std::map<uintptr_t, std::vector<uint8_t>*>();
	}
	HeapAllocator::~HeapAllocator()
	{
		LOCK_GUARD();

		for (std::map<uintptr_t, std::vector<uint8_t>*>::iterator i = heapAllocations.begin(); i != heapAllocations.end(); ++i)
		{
			std::vector<uint8_t>* vec = i->second;
			delete vec;
		}

	}
	uint8_t* HeapAllocator::sce_psm_malloc(int sz) {
		LOCK_GUARD();

		/*if (this->UsedSpace + sz > this->TotalHeapSize) {
			Logger::Warn("couldn't allocate memory " + std::to_string(sz) + " bytes(name = " + this->HeapName + ")");
			Logger::Debug("This should exceeed the resource heap limit, but since it barely works ima allow it for now ..");
		}*/

		// allocate a vector of uint8_t, of the given size
		std::vector<uint8_t>* vec = new std::vector<uint8_t>(sz);

		// increase the total size by the size of the vector
		this->UsedSpace += vec->size();

		// get the ptr to the buffer
		uint8_t* buffer = vec->data();

		// make a note of this allocation in the heapAllocations map.
		this->heapAllocations[(uintptr_t)buffer] = vec;

		return buffer;
	}
	void HeapAllocator::sce_psm_free(uint8_t* buffer) {
		LOCK_GUARD();

		// lookup the vector from this map
		std::vector<uint8_t>* vec = this->heapAllocations[(uintptr_t)buffer];

		// minus the total space from the vector, from the total used space
		this->UsedSpace -= vec->size();

		// free the vector
		delete vec;

		// remove the buffer from the map
		this->heapAllocations.erase((uintptr_t)buffer);

	}
	HeapAllocator* HeapAllocator::GetResourceHeapAllocator() {
		LOCK_GUARD_STATIC();
		return HeapAllocator::GetUniqueObject();
	}
	HeapAllocator* HeapAllocator::CreateResourceHeapAllocator(size_t resourceHeapSize) {
		LOCK_GUARD_STATIC();
		return new HeapAllocator(resourceHeapSize, "ScePsmResourceHeap");
	}

}
