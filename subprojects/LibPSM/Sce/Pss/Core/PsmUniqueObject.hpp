#ifndef LIB_PSS_PSM_UNIQUE_OBJECT_H
#define LIB_PSS_PSM_UNIQUE_OBJECT_H 1
#include <memory>
#include <atomic>
#include <cassert>
#include <LibShared.hpp>
using namespace Shared::Debug;

namespace Sce::Pss::Core {

	template<typename T> class PsmUniqueObject {
	private:
		static std::shared_ptr<T> uObjPtr;
	public:
		~PsmUniqueObject() {
			if (PsmUniqueObject<T>::UniqueObjectExists()) {
				PsmUniqueObject<T>::MakeLocalObject();
			}
		}

		static std::shared_ptr<T> MakeUniqueObject(std::shared_ptr<T> ptr) {
			// fail if a uniqueobject already exists
			assert(!PsmUniqueObject<T>::UniqueObjectExists());
			
			// set unique object to shared_ptr of this 
			PsmUniqueObject<T>::uObjPtr = std::reinterpret_pointer_cast<T>(ptr);
			return ptr;
		}

		static std::shared_ptr<T> UniqueObject() {
			assert(PsmUniqueObject<T>::UniqueObjectExists());
			return PsmUniqueObject<T>::uObjPtr;
		}

		static bool UniqueObjectExists() {
			return (PsmUniqueObject<T>::uObjPtr != nullptr);
		}
		
		static void MakeLocalObject() {
			assert(!PsmUniqueObject<T>::UniqueObjectExists());
			PsmUniqueObject<T>::uObjPtr = nullptr;
		}

	};

	template<typename T> std::shared_ptr<T> PsmUniqueObject<T>::uObjPtr = nullptr;
}
#endif