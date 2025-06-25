#ifndef LIB_PSS_PSM_OBJECT_H
#define LIB_PSS_PSM_OBJECT_H 1
#include <Sce/Pss/Core/Errorable.hpp>
#include <Sce/Pss/Core/Error.hpp>
#include <Sce/Pss/Core/System/Handles.hpp>
#include <Sce/Pss/Core/PsmMutexObject.hpp>
#include <Sce/Pss/Core/PsmUniqueObject.hpp>
#include <Sce/Pss/Core/Memory/HeapAllocator.hpp>
#include <mutex>
#include <memory>

namespace Sce::Pss::Core {
	template<typename T> class PsmObject : public std::enable_shared_from_this<T>, public Errorable, public PsmMutexObject<T> {
	private:
		int handle = Sce::Pss::Core::System::Handles::NoHandle;
	public:
		bool IsDisposed = false;
		~PsmObject() {
			LOCK_GUARD();
			this->IsDisposed = true;
			Sce::Pss::Core::System::Handles::Delete(this->handle);

			this->handle = Sce::Pss::Core::System::Handles::NoHandle;
		};


		int Handle() {
			if (!Sce::Pss::Core::System::Handles::IsValid(this->handle)) {
				this->handle = Sce::Pss::Core::System::Handles::Create(reinterpret_cast<T*>(this));
			}
			return this->handle;
		}

		void* operator new(size_t size) {
			Logger::Debug("Allocating: " + std::to_string(size) + " // " + typeid(T).name());
			std::shared_ptr<Sce::Pss::Core::Memory::HeapAllocator> alloc = Sce::Pss::Core::Memory::HeapAllocator::UniqueObject();
			return alloc->sce_psm_malloc(size);
		}

		void operator delete(void* ptr) {
			Logger::Debug("Freeing: " + std::to_string(reinterpret_cast<uintptr_t>(ptr)) + " // " + typeid(T).name());
			std::shared_ptr<Sce::Pss::Core::Memory::HeapAllocator> alloc = Sce::Pss::Core::Memory::HeapAllocator::UniqueObject();
			alloc->sce_psm_free(ptr);
		}
	};

}

#endif