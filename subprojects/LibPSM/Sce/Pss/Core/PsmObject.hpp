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
	template<typename T> class PsmObject : public Errorable, public PsmMutexObject<PsmObject<T>> {
		template<typename U> friend class PsmObject;

	protected:
		int handle = Sce::Pss::Core::System::Handles<T>::NoHandle;
		PsmObject() = default;
		~PsmObject() {
			this->handle = Sce::Pss::Core::System::Handles<T>::NoHandle;
		};
		
	public:
		
		template <typename... Args, typename = T> static std::shared_ptr<T> Create(Args&&... args) {
			std::shared_ptr<T> obj = std::make_shared<T>(std::forward<Args>(args)...);
			obj->handle = Sce::Pss::Core::System::Handles<T>::Create(obj);
			return obj;
		}

		static std::shared_ptr<T> Create(std::shared_ptr<T> obj) {
			std::reinterpret_pointer_cast<T>(obj)->handle = Sce::Pss::Core::System::Handles<T>::Create(obj);
			return obj;
		}

		static void Delete(std::shared_ptr<T> obj) {
			if (Sce::Pss::Core::System::Handles<T>::IsValid(obj->Handle())) {
				Sce::Pss::Core::System::Handles<T>::Delete(obj->Handle());
			}
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