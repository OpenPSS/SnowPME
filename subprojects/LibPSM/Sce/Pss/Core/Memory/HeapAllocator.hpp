#ifndef LIB_PSS_HEAPALLOCATOR_H
#define LIB_PSS_HEAPALLOCATOR_H 1
#include <vector>
#include <map>
#include <string>
#include <mutex>

#include <Sce/Pss/Core/PsmMutexObject.hpp>
#include <Sce/Pss/Core/PsmUniqueObject.hpp>

namespace Sce::Pss::Core::Memory {

	class HeapAllocator : public PsmUniqueObject<HeapAllocator>, public PsmMutexObject<HeapAllocator> {
	private:
		std::map<uintptr_t, std::vector<uint8_t>*> heapAllocations;
	public:
		HeapAllocator(size_t heapSize, const std::string& heapName);
		~HeapAllocator();

		size_t TotalHeapSize = 0;
		size_t UsedSpace = 0;
		std::string HeapName;

		uint8_t* sce_psm_malloc(int sz);
		void sce_psm_free(uint8_t* buffer);
	};

}
#endif