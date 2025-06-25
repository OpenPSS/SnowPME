#include <Windowing/Event.hpp>
#include <cstring>
#include <cstdint>
#include <cstdlib>

namespace Shared::Windowing {
	EventType Event::TypeID() {
		return this->typeId;
	}

	uint32_t Event::Uid() {
		return this->uid;
	}

	Event::Event(EventType typeId) {
		this->typeId = typeId;
	}

	Event::Event(EventType typeId, std::vector<std::byte>& args) {
		this->typeId = typeId;
		ArgsReplace(args);
	}

	Event::Event(EventType typeId, void* args, size_t length) {
		this->typeId = typeId;
		ArgsReplace(args, length);
	}


	std::vector<std::byte>& Event::Args() {
		return this->arguments;
	}

	std::byte* Event::ArgsArray() {
		return this->arguments.data();
	}

	std::byte Event::Arg(int index) {
		ASSERT(index <= this->Count());
		return this->arguments.at(index);
	}

	void Event::ArgsReplace(std::vector<std::byte>& args) {
		this->arguments = args;
	}


	void Event::ArgsReplace(void* args, size_t length) {
		this->arguments.resize(length);
		memcpy(this->ArgsArray(), args, length);
	}

	size_t Event::Count() {
		return this->arguments.size();
	}

}