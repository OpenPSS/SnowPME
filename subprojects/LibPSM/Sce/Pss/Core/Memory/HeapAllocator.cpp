#include <Sce/Pss/Core/Memory/HeapAllocator.hpp>
#include <string>
#include <iostream>
#include <mutex>
#include <LibShared.hpp>

using namespace Shared::Debug;

namespace Sce::Pss::Core::Memory {
	std::unordered_map<std::string, std::shared_ptr<HeapAllocator>> HeapAllocator::heapList;

	HeapAllocator::HeapAllocator(size_t heapSize, const std::string& heapName) {
		this->HeapName = heapName;
		this->TotalHeapSize = heapSize;

	}

	void* HeapAllocator::sce_psm_malloc(int sz) {
		LOCK_GUARD();

		/*if (this->UsedSpace + sz > this->TotalHeapSize) {
			Logger::Warn("couldn't allocate memory " + std::to_string(sz) + " bytes(name = " + this->HeapName + ")");
			Logger::Debug("This should exceeed the resource heap limit, but since it barely works ima allow it for now ..");
		}*/

		// allocate a vector of uint8_t, of the given size
		std::shared_ptr<std::vector<uint8_t>> vec = std::make_shared<std::vector<uint8_t>>(sz);

		// increase the total size by the size of the vector
		this->UsedSpace += vec->size();

		// get the ptr to the buffer
		uint8_t* buffer = vec->data();

		// make a note of this allocation in the heapAllocations map.
		this->heapAllocations[(uintptr_t)buffer] = vec;

		return reinterpret_cast<void*>(buffer);
	}
	void HeapAllocator::sce_psm_free(void* buffer) {
		LOCK_GUARD();

		// lookup the vector from this map
		std::shared_ptr<std::vector<uint8_t>> vec = this->heapAllocations[reinterpret_cast<uintptr_t>(buffer)];

		// minus the total space from the vector, from the total used space
		this->UsedSpace -= vec->size();

		// remove the buffer from the map
		this->heapAllocations.erase(reinterpret_cast<uintptr_t>(buffer));

	}

}
