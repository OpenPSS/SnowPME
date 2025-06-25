#include <Windowing/EventQueue.hpp>
#include <Windowing/Event.hpp>

#include <cstring>
#include <cstdint>
#include <memory>
#include <mutex>
#include <unordered_map>
#include <list>

namespace Shared::Windowing {


	std::mutex EventQueue::lockRequestQueue;
	std::mutex EventQueue::lockResponseQueue;

	std::queue<std::shared_ptr<Event>> EventQueue::requestQueue;
	std::unordered_map<uint32_t, std::shared_ptr<Event>> EventQueue::responseQueue;

	// requests

	std::shared_ptr<Event> EventQueue::GetNextRequest() {
		std::lock_guard<std::mutex> lock(lockRequestQueue);
		if (requestQueue.empty()) return nullptr;

		std::shared_ptr<Event> request = requestQueue.front();
		requestQueue.pop();

		return request;
	}
	void EventQueue::PushRequest(std::shared_ptr<Event> request) {
		std::lock_guard<std::mutex> lock(lockRequestQueue);
		requestQueue.push(request);
	}

	// responses

	std::shared_ptr<Event> EventQueue::GetResponse(std::shared_ptr<Event> request) {
		std::lock_guard<std::mutex> lock(lockResponseQueue);

		if (responseQueue.empty()) return nullptr;

		if (responseQueue.contains(request->Uid())) {
			std::shared_ptr<Event> response = responseQueue[request->Uid()];
			responseQueue.erase(request->Uid());
			return response;
		}

		return nullptr;
	}

	void EventQueue::PushResponse(std::shared_ptr<Event> response) {
		std::lock_guard<std::mutex> lock(lockResponseQueue);
		responseQueue.insert(std::make_pair(response->Uid(), response));
	}


	std::shared_ptr<Event> EventQueue::DispatchEvent(std::shared_ptr<Event> evtRequest) {

		PushRequest(evtRequest);
		std::shared_ptr<Event> response = nullptr;;

		do {
			response = GetResponse(evtRequest);
		} while (response == nullptr);

		return response;
	}
}