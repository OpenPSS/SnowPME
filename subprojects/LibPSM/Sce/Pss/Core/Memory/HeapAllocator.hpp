#ifndef LIB_PSS_HEAPALLOCATOR_H
#define LIB_PSS_HEAPALLOCATOR_H 1
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <mutex>
#include <LibShared.hpp>

#include <Sce/Pss/Core/PsmMutexObject.hpp>
#include <Sce/Pss/Core/PsmUniqueObject.hpp>
#include <Sce/Pss/Core/Error.hpp>

namespace Sce::Pss::Core::Memory {

	class HeapAllocator : public PsmUniqueObject<HeapAllocator>, public PsmMutexObject<HeapAllocator> {
	private:
		static std::unordered_map<std::string, std::shared_ptr<HeapAllocator>> heapList;
		static size_t freeMemory;

		std::unordered_map<uintptr_t, std::shared_ptr<std::vector<uint8_t>>> heapAllocations;

	public:
		HeapAllocator(size_t heapSize, const std::string& heapName);
		std::string HeapName;

		size_t UsedSpace = 0;
		size_t TotalHeapSize = 0;

		void* sce_psm_realloc(void* buffer, int sz);
		void* sce_psm_malloc(int sz);
		void sce_psm_free(void* buffer);

		static uintptr_t fake_malloc(size_t sz);
		static size_t fake_free(size_t sz);
	};

}


#define CUSTOM_ALLOC() \
void* operator new(size_t size) { \
	LOG_FUNCTION(); \
	std::shared_ptr<Sce::Pss::Core::Memory::HeapAllocator> alloc = Sce::Pss::Core::Memory::HeapAllocator::UniqueObject(); \
	return alloc->sce_psm_malloc(size); \
} \
\
void operator delete(void* ptr) { \
	LOG_FUNCTION(); \
	std::shared_ptr<Sce::Pss::Core::Memory::HeapAllocator> alloc = Sce::Pss::Core::Memory::HeapAllocator::UniqueObject(); \
	alloc->sce_psm_free(ptr); \
} 


#endif