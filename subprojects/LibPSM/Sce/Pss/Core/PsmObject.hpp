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
#include <utility>
#include <type_traits>

namespace Sce::Pss::Core {
	template<typename T> class PsmObject : public Errorable, public PsmMutexObject<T> {

	private:
		int handle = Sce::Pss::Core::System::Handles::NoHandle;
	protected:
		PsmObject() {
			this->handle = Sce::Pss::Core::System::Handles::Create(reinterpret_cast<T*>(this));
		}
		~PsmObject() {
			this->IsDisposed = true;
			this->handle = Sce::Pss::Core::System::Handles::NoHandle;
		};
		
	public:
		bool IsDisposed = false;

		template <typename... Args, typename = T> static T* Create(Args&&... args) {

			T* obj = new T(std::forward<Args>(args)...);
			obj->handle = Sce::Pss::Core::System::Handles::Create(obj);
			return obj;
		}

		static void Delete(T* obj) {

			if (Sce::Pss::Core::System::Handles::IsValid(obj->Handle())) {
				Sce::Pss::Core::System::Handles::Delete(obj->Handle());
			}
			
			delete obj;
		}
		
		int Handle() {
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