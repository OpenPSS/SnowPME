#ifndef LIB_PSS_PSM_MUTEX_OBJECT_H
#define LIB_PSS_PSM_MUTEX_OBJECT_H 1
#include <mutex>
#include <memory>

#define LOCK_GUARD() std::scoped_lock<std::mutex> lock(*GetObjectMutex())
#define LOCK_GUARD_STATIC() std::scoped_lock<std::mutex> lock(*GetStaticObjectMutex())

namespace Sce::Pss::Core {
	template<typename T> class PsmMutexObject {
	private:
		// create mutexes
		std::mutex* objectLock = new std::mutex();
		inline static std::mutex* objectLockStatic = new std::mutex();

	public:
		// get mutexes
		std::mutex* GetObjectMutex() {
			return this->objectLock;
		}

		static std::mutex* GetStaticObjectMutex() {
			return T::objectLockStatic;
		}

		PsmMutexObject() = default;
		virtual ~PsmMutexObject() {
			delete this->objectLock;
			this->objectLock = nullptr;
		}
	};

}

#endif