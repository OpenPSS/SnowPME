#ifndef LIB_PSS_PSM_REF_COUNT_H
#define LIB_PSS_PSM_REF_COUNT_H 1

#include <LibShared.hpp>
#include <Sce/Pss/Core/System/Handles.hpp>
#include <Sce/Pss/Core/PsmMutexObject.hpp>
#include <Sce/Pss/Core/Memory/HeapAllocator.hpp>
#include <Sce/Pss/Core/Errorable.hpp>
#include <Sce/Pss/Core/Error.hpp>
#include <memory>
#include <atomic>

namespace Sce::Pss::Core {
	template<typename T> class PsmRefCount : public Errorable, public PsmMutexObject<PsmRefCount<T>> {
		template<typename U> friend class PsmRefCount;

	protected:
		int handle = Sce::Pss::Core::System::Handles<T>::NoHandle;
		std::atomic<size_t> totalReferences = 0;
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
				T* obj = dynamic_cast<T*>(T::LookupHandle(handle));

				obj->AddRef();
				return true;
			}

			return false;
		}

		static bool Delete(int handle) {
			if (T::CheckHandle(handle)) {
				T* obj = dynamic_cast<T*>(T::LookupHandle(handle));
				return T::Delete(obj);
			}

			return false;
		}

		static bool Delete(T* obj) {
			if (obj != nullptr) {
				if (obj->RemoveRef() > 0)
					return false;

				if(CheckHandle(obj->Handle()))
					Sce::Pss::Core::System::Handles<T>::Delete(obj->Handle());

				delete obj;

				return true;
			}

			return false;
		}

		size_t RefCount() {
			return this->totalReferences;
		}

		size_t AddRef() {
			return this->totalReferences++;
		}
		
		size_t RemoveRef() {
			return this->totalReferences--;
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

		CUSTOM_ALLOC();

	};

}

#endif