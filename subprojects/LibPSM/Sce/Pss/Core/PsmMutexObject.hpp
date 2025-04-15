#ifndef LIB_PSS_PSM_MUTEX_OBJECT_H
#define LIB_PSS_PSM_MUTEX_OBJECT_H 1
#include <mutex>

#define LOCK_GUARD() std::scoped_lock<std::mutex> lock(this->objectLock)
#define LOCK_GUARD_STATIC() std::scoped_lock<std::mutex> lock(objectLockStatic)

namespace Sce::Pss::Core {
	template<typename T> class PsmMutexObject {
	protected:
		std::mutex objectLock;
		static std::mutex objectLockStatic;
	};

	template<typename T> std::mutex PsmMutexObject<T>::objectLockStatic;
}

#endif