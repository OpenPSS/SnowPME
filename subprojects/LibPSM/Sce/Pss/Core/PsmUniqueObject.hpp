#ifndef LIB_PSS_PSM_UNIQUE_OBJECT_H
#define LIB_PSS_PSM_UNIQUE_OBJECT_H 1
#include <atomic>
#include <Sce/Pss/Core/Errorable.hpp>
#include <LibShared.hpp>

namespace Sce::Pss::Core {
	template<typename T> class PsmUniqueObject {
	private:
		static std::atomic<T*> uniqueObjectPtr;
	public:
		PsmUniqueObject() {
			if (this->GetUniqueObject() != nullptr) {
				Shared::Debug::Logger::Error("UniqueObject already found, overwriting...");
				delete this->GetUniqueObject();
			}
			PsmUniqueObject<T>::uniqueObjectPtr.store((T*)this);
		}

		~PsmUniqueObject() {
			PsmUniqueObject<T>::uniqueObjectPtr.store((T*)nullptr);
		}

		static T* GetUniqueObject() {
			return (T*)(PsmUniqueObject<T>::uniqueObjectPtr.load());
		}

	};

	template<typename T> std::atomic<T*> PsmUniqueObject<T>::uniqueObjectPtr(nullptr);
}
#endif