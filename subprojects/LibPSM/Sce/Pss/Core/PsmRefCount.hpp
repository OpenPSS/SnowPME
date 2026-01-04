#ifndef LIB_PSS_PSM_REF_COUNT_H
#define LIB_PSS_PSM_REF_COUNT_H 1

#include <LibShared.hpp>
#include <Sce/Pss/Core/System/Handles.hpp>
#include <Sce/Pss/Core/PsmMutexObject.hpp>
#include <Sce/Pss/Core/Memory/HeapAllocator.hpp>
#include <memory>
#include <atomic>

namespace Sce::Pss::Core {
	template<typename T> class PsmRefCount : public Errorable, public PsmMutexObject<PsmRefCount<T>> {
		template<typename U> friend class PsmRefCount;

	protected:
		std::atomic<size_t> totalReferences = 0;
		int handle = Sce::Pss::Core::System::Handles<T>::NoHandle;
	public:

		PsmRefCount() = default;
		virtual ~PsmRefCount() = default;

		template <typename... Args, typename = T> static T* Create(Args&&... args) {
			T* obj = new T(std::forward<Args>(args)...);
			obj->handle = Sce::Pss::Core::System::Handles<T>::Create(obj);
			return obj;
		}

		static T* Create(T* obj) {
			obj->handle = Sce::Pss::Core::System::Handles<T>::Create(obj);
			return obj;
		}

		static bool AddRef(int handle) {
			if (T::CheckHandle(handle)) {
				T* object = dynamic_cast<T*>(T::LookupHandle(handle));

				object->totalReferences++;
				return true;
			}

			return false;
		}

		static bool Delete(int handle) {
			if (T::CheckHandle(handle)) {
				T* object = dynamic_cast<T*>(T::LookupHandle(handle));
				return T::Delete(object);
			}

			return false;
		}

		static bool Delete(T* object) {
			if (object != nullptr) {
				object->totalReferences--;
				if (object->TotalReferences() > 0)
					return false;

				if(CheckHandle(object->Handle()))
					Sce::Pss::Core::System::Handles<T>::Delete(object->Handle());

				delete object;

				return true;
			}

			return false;
		}

		size_t TotalReferences() {
			return this->totalReferences;
		}

		int Handle() {
			return handle;
		}

		static T* LookupHandle(int handle) {
			return Sce::Pss::Core::System::Handles<T>::GetRaw(handle);
		}

		static bool CheckHandle(int handle) {
			return Sce::Pss::Core::System::Handles<T>::IsValid(handle);
		}


		void* operator new(size_t size) {
			Shared::Debug::Logger::Debug("Allocating: " + std::to_string(size) + " // " + typeid(T).name());
			std::shared_ptr<Sce::Pss::Core::Memory::HeapAllocator> alloc = Sce::Pss::Core::Memory::HeapAllocator::UniqueObject();
			return alloc->sce_psm_malloc(size);
		}

		void operator delete(void* ptr) {
			Shared::Debug::Logger::Debug("Freeing: " + std::to_string(reinterpret_cast<uintptr_t>(ptr)) + " // " + typeid(T).name());
			std::shared_ptr<Sce::Pss::Core::Memory::HeapAllocator> alloc = Sce::Pss::Core::Memory::HeapAllocator::UniqueObject();
			alloc->sce_psm_free(ptr);
		}


	};

}

#endif