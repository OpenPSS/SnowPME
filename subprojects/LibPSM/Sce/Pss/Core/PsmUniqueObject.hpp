#ifndef LIB_PSS_PSM_UNIQUE_OBJECT_H
#define LIB_PSS_PSM_UNIQUE_OBJECT_H 1
#include <Sce/Pss/Core/Errorable.hpp>

namespace Sce::Pss::Core {
	template<typename T> class PsmUniqueObject {
	private:
		static T* uniqueObjectPtr;
	public:
		PsmUniqueObject() {
			assert(!PsmUniqueObject<T>::Exists());
			PsmUniqueObject<T>::uniqueObjectPtr = reinterpret_cast<T*>(this);
		}

		~PsmUniqueObject() {
			uniqueObjectPtr = nullptr;
		}

		static T* GetUniqueObject() {
			return PsmUniqueObject<T>::uniqueObjectPtr;
		}

		static bool Exists() {
			return (PsmUniqueObject<T>::uniqueObjectPtr != nullptr);
		}

	};

	template<typename T> T* PsmUniqueObject<T>::uniqueObjectPtr = nullptr;
}
#endif