#include <Threading/ProgressTracker.hpp>
#include <thread>
#include <mutex>

namespace Shared::Threading {
	float ProgressTracker::Progress() {
		return (float)((double)(this->NumDone()) / (double)(this->NumTotal()) * 1.0);
	}

	uint64_t ProgressTracker::NumDone() {
		return this->numDone.load();
	}
	uint64_t ProgressTracker::NumTotal() {
		return this->numTotal.load();
	}
	bool ProgressTracker::ShowProgress() {
		return this->showProgress.load();
	}

	void ProgressTracker::SetNumTotal(uint64_t numTotal) {
		this->numTotal.store(numTotal);
	}
	void ProgressTracker::SetNumDone(uint64_t numDone) {
		this->numDone.store(numDone);

	}
	void ProgressTracker::SetShowProgress(bool showProgress) {
		this->showProgress.store(showProgress);
	}

	void ProgressTracker::Increment(int totalIncrement) {
		std::scoped_lock<std::mutex> lock(this->progressLock);

		this->SetNumDone(this->NumDone() + totalIncrement);
	}
	void ProgressTracker::Reset(int total) {
		std::scoped_lock<std::mutex> lock(this->progressLock);

		this->SetNumTotal(total);
		this->SetNumDone(0);
		this->SetShowProgress(false);
	}

	ProgressTracker::ProgressTracker() {
		this->Reset();
	}
}