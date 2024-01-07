#include <Threading/ThreadSafeCounter.hpp>

namespace Shared::Threading {
	std::mutex ThreadSafeCounter::incDecMutex = std::mutex();

	void ThreadSafeCounter::Increment(int* value) {
		incDecMutex.lock();
		*value++;
		incDecMutex.unlock();
	}

	void ThreadSafeCounter::Decrement(int* value) {
		incDecMutex.lock();
		*value--;
		incDecMutex.unlock();
	}

	int ThreadSafeCounter::GetValue(int* value) {
		incDecMutex.lock();
		int valueCopy = *value;
		incDecMutex.unlock();
		return valueCopy;
	}

}