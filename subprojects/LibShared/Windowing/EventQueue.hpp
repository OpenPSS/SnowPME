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
		static std::mutex lockResponseQueue;

		static std::queue<std::shared_ptr<Event>> requestQueue;
		static std::unordered_map<uint32_t, std::shared_ptr<Event>> responseQueue;
	public:
		static std::shared_ptr<Event> GetNextRequest();
		static void PushRequest(std::shared_ptr<Event> request);

		static std::shared_ptr<Event> GetResponse(std::shared_ptr<Event> request);
		static void PushResponse(std::shared_ptr<Event> response);

		static std::shared_ptr<Event> DispatchEvent(std::shared_ptr<Event> request);

	};
}

#endif