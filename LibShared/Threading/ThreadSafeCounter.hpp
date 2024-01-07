#ifndef SHARED_THREADSAFE_COUNTER_H
#define SHARED_THREADSAFE_COUNTER_H 1
#include <mutex>

namespace Shared::Threading {
	class ThreadSafeCounter {
	private:
		static std::mutex incDecMutex;
	public:
		static void Increment(int* value);
		static void Decrement(int* value);
		static int GetValue(int* value);
	};
}

#endif