#ifndef SHARED_PROGRESSTRACKER_COUNTER_H
#define SHARED_PROGRESSTRACKER_COUNTER_H 1
#include <atomic>
#include <mutex>

namespace Shared::Threading {
	class ProgressTracker {
	private:
		
		// progress bar
		std::atomic<bool> showProgress;
		std::atomic<uint64_t> numDone;
		std::atomic<uint64_t> numTotal;
		std::mutex progressLock;

	public:
		float Progress();
		uint64_t NumDone();
		uint64_t NumTotal();
		bool ShowProgress();

		void SetNumTotal(uint64_t numTotal);
		void SetNumDone(uint64_t numDone);
		void SetShowProgress(bool showProgress);

		void Increment(int totalIncrement = 1);
		void Reset(int total = 0);

		ProgressTracker();
	};
}


#endif