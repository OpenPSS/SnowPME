#ifndef LIB_PSS_PSM_UNIQUE_OBJECT_H
#define LIB_PSS_PSM_UNIQUE_OBJECT_H 1
#include <Sce/Pss/Core/Errorable.hpp>
#include <Sce/Pss/Core/PsmMutexObject.hpp>

namespace Sce::Pss::Core {
	template<typename T> class PsmUniqueObject : public PsmMutexObject<T> {
	private:
		static T* uniqueObjectPtr;
	public:
		PsmUniqueObject() {
			LOCK_GUARD();
			assert(!PsmUniqueObject<T>::Exists());
			PsmUniqueObject<T>::uniqueObjectPtr = reinterpret_cast<T*>(this);
		}

		~PsmUniqueObject() {
			LOCK_GUARD();
			uniqueObjectPtr = nullptr;
		}

		static T* GetUniqueObject() {
			LOCK_GUARD_STATIC();
			return PsmUniqueObject<T>::uniqueObjectPtr;
		}

		static bool Exists() {
			return PsmUniqueObject<T>::uniqueObjectPtr != nullptr;
		}

	};

	template<typename T> T* PsmUniqueObject<T>::uniqueObjectPtr = nullptr;
}
#endif