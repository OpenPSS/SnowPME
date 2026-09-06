#ifndef LIB_PSS_PSMACTION_LIST_H
#define LIB_PSS_PSMACTION_LIST_H 1
#include <list>
#include <stdint.h>
#include <Sce/Pss/Core/PsmMutexObject.hpp>
#include <Sce/Pss/Core/PsmUniqueObject.hpp>
#include <Sce/Pss/Core/System/Handles.hpp>
#include <Sce/Pss/Core/Graphics/PsmFree.hpp>

namespace Sce::Pss::Core::Graphics {
	class PsmFreeList : public PsmMutexObject<PsmFreeList> {
	private:
		static std::vector<PsmFree> freeList;
	public:
		
		static void AddEntry(PsmFree freeEntry);
		
		template <typename... Args> static void AddEntry(Args&&... args) {
			LOG_FUNCTION();
			LOCK_GUARD_STATIC();
			freeList.emplace_back(std::forward<Args>(args)...);
		}
		
		static void FreeHeldObjects();

	};
}

#endif
