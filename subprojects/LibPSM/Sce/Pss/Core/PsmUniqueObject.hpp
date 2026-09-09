#ifndef LIB_PSS_PSM_UNIQUE_OBJECT_H
#define LIB_PSS_PSM_UNIQUE_OBJECT_H 1
#include <memory>
#include <atomic>
#include <LibShared.hpp>
#include <Sce/Pss/Core/System/Handles.hpp>
using namespace Shared::Debug;

namespace Sce::Pss::Core {

	template<typename T> class PsmUniqueObject {
	private:
		inline static std::shared_ptr<T> uObjPtr = nullptr;
	public:
		virtual ~PsmUniqueObject() {
			if (PsmUniqueObject<T>::UniqueObjectExists()) {
				PsmUniqueObject<T>::MakeLocalObject();
			}
		}

		static T* MakeUniqueObject(int obj) {
			// fail if a uniqueobject already exists
			ASSERT(!PsmUniqueObject<T>::UniqueObjectExists());
		
			uObjPtr = Sce::Pss::Core::System::Handles<T>::GetShared(obj);
		
			return uObjPtr.get();
		}

		static T* MakeUniqueObject(std::shared_ptr<T>& ptr) {
			// fail if a uniqueobject already exists
			ASSERT(!PsmUniqueObject<T>::UniqueObjectExists());
			
			// set unique object to shared_ptr of this 
			uObjPtr = ptr;

			return uObjPtr.get();
		}

		static T* UniqueObject() {
			ASSERT(PsmUniqueObject<T>::UniqueObjectExists());
			return PsmUniqueObject<T>::uObjPtr.get();
		}

		static bool UniqueObjectExists() {
			return (PsmUniqueObject<T>::uObjPtr != nullptr);
		}
		
		static void MakeLocalObject() {
			if (PsmUniqueObject<T>::UniqueObjectExists()) {
				PsmUniqueObject<T>::uObjPtr = nullptr;
			}
		}
	};

}
#endif