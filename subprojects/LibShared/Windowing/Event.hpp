#ifndef SHARED_NAMEDEVENT_H
#define SHARED_NAMEDEVENT_H 1
#include <Windowing/EventType.hpp>
#include <Debug/Assert.hpp>
#include <String/StringUtil.hpp>

#include <random>
#include <vector>
#include <cstdint>
#include <string>

namespace Shared::Windowing {

	class Event {
	private:
		EventType typeId = EventType::None;
		uint32_t uid = rand();
		std::vector<std::byte> arguments;
	public:
		uint32_t Uid();
		EventType TypeID();

		Event(EventType typeId, std::vector<std::byte>& args);
		Event(EventType typeId, void* args, size_t length);
		Event(EventType typeId);

		std::vector<std::byte>& Args();
		std::byte* ArgsArray();
		std::byte Arg(int index);
		size_t Count();

		void ArgsReplace(std::vector<std::byte>& args);
		void ArgsReplace(void* args, size_t length);

	};

}


#endif