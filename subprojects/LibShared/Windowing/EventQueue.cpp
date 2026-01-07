#include <Windowing/EventQueue.hpp>
#include <Windowing/Event.hpp>

#include <cstring>
#include <cstdint>
#include <memory>
#include <mutex>
#include <unordered_map>
#include <list>

#include <Debug/Logger.hpp>
#include <String/Format.hpp>

using namespace Shared::String;
using namespace Shared::Debug;

namespace Shared::Windowing {


	std::mutex EventQueue::lockRequestQueue;
	std::queue<std::shared_ptr<Event>> EventQueue::requestQueue;

	std::shared_ptr<Event> EventQueue::GetNextRequest() {
		std::lock_guard<std::mutex> lock(lockRequestQueue);
		if (requestQueue.empty()) return nullptr;

		std::shared_ptr<Event> request = requestQueue.front();
		requestQueue.pop();

		return request;
	}
	void EventQueue::PushRequest(std::shared_ptr<Event> request) {
		ASSERT(!request->HasResponse());

		std::lock_guard<std::mutex> lock(lockRequestQueue);
		requestQueue.push(request);
	}

	std::shared_ptr<Event> EventQueue::DispatchEvent(std::shared_ptr<Event> evtRequest) {
		Logger::Debug("Sending event // " + Format::Hex(static_cast<uint32_t>(evtRequest->TypeID())));
		PushRequest(evtRequest);
		evtRequest->WaitResponse();
		Logger::Debug("Got response to event // " + Format::Hex(static_cast<uint32_t>(evtRequest->TypeID())));
		return evtRequest;
	}
}