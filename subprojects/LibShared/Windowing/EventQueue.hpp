#ifndef SHARED_WINDOWEVENT_H
#define SHARED_WINDOWEVENT_H 1
#include <Windowing/Event.hpp>
#include <Windowing/EventType.hpp>

#include <cstdint>
#include <queue>
#include <memory>
#include <mutex>
#include <unordered_map>

namespace Shared::Windowing {
	class EventQueue  {
	private:
		static std::mutex lockRequestQueue;

		static std::queue<std::shared_ptr<Event>> requestQueue;
	public:
		static std::shared_ptr<Event> GetNextRequest();
		static void PushRequest(std::shared_ptr<Event> request);

		static std::shared_ptr<Event> DispatchEvent(std::shared_ptr<Event> request);

	};
}

#endif