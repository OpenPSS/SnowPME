#include <Windowing/EventQueue.hpp>
#include <Windowing/Event.hpp>

#include <cstdint>
#include <queue>
#include <memory>
#include <mutex>


namespace Shared::Windowing {


	std::mutex EventQueue::lockRequestQueue;
	std::mutex EventQueue::lockResponseQueue;

	std::list<std::shared_ptr<Event>> EventQueue::requestQueue;
	std::list<std::shared_ptr<Event>> EventQueue::responseQueue;

	std::shared_ptr<Event> EventQueue::GetNextRequest() {
		std::lock_guard<std::mutex> lock(lockRequestQueue);
		if (requestQueue.empty()) return nullptr;

		std::shared_ptr<Event> request = requestQueue.back();
		requestQueue.pop_back();

		return request;
	}
	void EventQueue::PushRequest(std::shared_ptr<Event> request) {
		std::lock_guard<std::mutex> lock(lockRequestQueue);
		requestQueue.push_back(request);
	}

	std::shared_ptr<Event> EventQueue::GetResponse(std::shared_ptr<Event> request) {
		std::lock_guard<std::mutex> lock(lockResponseQueue);

		if (responseQueue.empty()) return nullptr;


		for (std::shared_ptr<Event>& response : responseQueue) {
			if (response->Uid() == request->Uid()) {
				responseQueue.remove(response);
				return response;
			}
		}

		return nullptr;
	}

	void EventQueue::PushResponse(std::shared_ptr<Event> response) {
		std::lock_guard<std::mutex> lock(lockResponseQueue);
		responseQueue.push_back(response);
	}

	std::shared_ptr<Event> EventQueue::DispatchEvent(std::shared_ptr<Event> evtRequest) {

		PushRequest(evtRequest);

		std::shared_ptr<Event> response = nullptr;;

		do {
			response = GetResponse(evtRequest);
		} while (response != nullptr);

		return response;
	}
}