#ifndef LIB_PSS_PSM_UNIQUE_OBJECT_H
#define LIB_PSS_PSM_UNIQUE_OBJECT_H 1
#include <memory>
#include <atomic>
#include <cassert>
#include <LibShared.hpp>
using namespace Shared::Debug;

namespace Sce::Pss::Core {

	template<typename T> class PsmUniqueObject : public std::enable_shared_from_this<T> {
	private:
		static T* tmpPtr;
		static void initalizeSharedPointer() {
			assert(PsmUniqueObject<T>::Exists());

			if (PsmUniqueObject<T>::tmpPtr != nullptr) {
				PsmUniqueObject<T>::uniqueObjectPtr = PsmUniqueObject<T>::tmpPtr->shared_from_this();
				PsmUniqueObject<T>::tmpPtr = nullptr;
			}
		}
	protected:
		static std::shared_ptr<T> uniqueObjectPtr;
	public:
		PsmUniqueObject() {
			Logger::Debug(__FUNCTION__);
			assert(!PsmUniqueObject<T>::Exists());
			PsmUniqueObject<T>::uniqueObjectPtr = nullptr;
			PsmUniqueObject<T>::tmpPtr = reinterpret_cast<T*>(this);
		}

		~PsmUniqueObject() {
			PsmUniqueObject<T>::Dereference();
		}

		static std::shared_ptr<T> GetUniqueObject() {
			PsmUniqueObject<T>::initalizeSharedPointer();
			return PsmUniqueObject<T>::uniqueObjectPtr;
		}

		static bool Exists() {
			return (PsmUniqueObject<T>::uniqueObjectPtr != nullptr ||
					PsmUniqueObject<T>::tmpPtr != nullptr);
		}
		
		static void Dereference() {
			PsmUniqueObject<T>::tmpPtr = nullptr;
			PsmUniqueObject<T>::uniqueObjectPtr = nullptr;
		}

	};

	template<typename T> std::shared_ptr<T> PsmUniqueObject<T>::uniqueObjectPtr = nullptr;
	template<typename T> T* PsmUniqueObject<T>::tmpPtr = nullptr;
}
#endif