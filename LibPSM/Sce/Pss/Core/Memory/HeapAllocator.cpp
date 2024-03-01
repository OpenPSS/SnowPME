#include <Sce/Pss/Core/Memory/HeapAllocator.hpp>
#include <string>
#include <iostream>
#include <mutex>
#include <LibShared.hpp>
using namespace Shared::Debug;

namespace Sce::Pss::Core::Memory {
	HeapAllocator* HeapAllocator::resourceHeapAllocator = nullptr;

	HeapAllocator::HeapAllocator(size_t heapSize, std::string heapName) {
		this->HeapName = heapName;
		this->TotalHeapSize = heapSize;

		this->heapAllocations = std::map<uintptr_t, std::vector<uint8_t>*>();
	}
	HeapAllocator::~HeapAllocator() 
	{
		this->allocMutex.lock();

		for (std::map<uintptr_t, std::vector<uint8_t>*>::iterator i = heapAllocations.begin(); i != heapAllocations.end(); ++i)
		{
			std::vector<uint8_t>* vec = i->second;
			delete vec;
		}

		HeapAllocator::resourceHeapAllocator = nullptr;
		this->allocMutex.unlock();
	}
	uint8_t* HeapAllocator::sce_psm_malloc(int sz) {
		this->allocMutex.lock();

		if (this->UsedSpace + sz > this->TotalHeapSize) {
			Logger::Warn("couldn't allocate memory " + std::to_string(sz) + " bytes(name = " + this->HeapName + ")");
#ifndef _DEBUG
			this->allocMutex.unlock();
			return nullptr;
#endif
		}

		// allocate a vector of uint8_t, of the given size
		std::vector<uint8_t>* vec = new std::vector<uint8_t>(sz);

		// increase the total size by the size of the vector
		this->UsedSpace += vec->size();
		
		// get the ptr to the buffer
		uint8_t* buffer = vec->data();

		// make a note of this allocation in the heapAllocations map.
		this->heapAllocations[(uintptr_t)buffer] = vec;

		this->allocMutex.unlock();
		return buffer;
	}
	void HeapAllocator::sce_psm_free(uint8_t* buffer) {
		this->allocMutex.lock();

		// lookup the vector from this map
		std::vector<uint8_t>* vec = this->heapAllocations[(uintptr_t)buffer];

		// minus the total space from the vector, from the total used space
		this->UsedSpace -= vec->size();

		// free the vector
		delete vec;

		// remove the buffer from the map
		this->heapAllocations.erase((uintptr_t)buffer);

		this->allocMutex.unlock();
	}
	HeapAllocator* HeapAllocator::GetResourceHeapAllocator() {
		if (HeapAllocator::resourceHeapAllocator == nullptr)
			throw std::exception("resource heap allocator is not yet initalized.");

		return HeapAllocator::resourceHeapAllocator;
	}
	HeapAllocator* HeapAllocator::CreateResourceHeapAllocator(size_t resourceHeapSize) {
		if (HeapAllocator::resourceHeapAllocator != nullptr)
			delete HeapAllocator::resourceHeapAllocator;

		HeapAllocator::resourceHeapAllocator = new HeapAllocator(resourceHeapSize, "ScePsmResourceHeap");
		return HeapAllocator::resourceHeapAllocator;
	}

}