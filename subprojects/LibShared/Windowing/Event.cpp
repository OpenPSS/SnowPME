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
		this->PutResponse(args);
	}

	Event::Event(EventType typeId, void* args, size_t length) {
		this->typeId = typeId;
		this->PutResponse(args, length);
	}

	std::vector<std::byte>& Event::ArgumentVec() {
		return this->arguments;
	}

	std::byte* Event::ArgumentArray() {
		return this->arguments.data();
	}

	std::byte Event::ArgumentByte(int index) {
		ASSERT(index <= static_cast<int>(this->ArgumentCount()));
		return this->arguments.at(index);
	}

	size_t Event::ArgumentCount() {
		return this->arguments.size();
	}

	// RESPONSE

	std::vector<std::byte>& Event::ResponseVec() {
		this->WaitResponse();
		return this->response;
	}

	std::byte* Event::ResponseArray() {
		this->WaitResponse();
		return this->response.data();
	}

	std::byte Event::ResponseByte(int index) {
		this->WaitResponse();
		ASSERT(index <= static_cast<int>(this->ArgumentCount()));
		return this->response.at(index);
	}

	size_t Event::ResponseCount() {
		this->WaitResponse();
		return this->response.size();
	}

	void Event::PutArguments(std::vector<std::byte>& args) {
		this->arguments = args;
		this->notifier.release();
	}

	void Event::PutArguments(void* args, size_t length) {
		this->arguments.resize(length);
		memcpy(this->arguments.data(), args, length);
		this->notifier.release();
	}

	void Event::PutResponse(std::vector<std::byte>& response) {
		this->response = response;
		this->notifier.release();
	}


	void Event::PutResponse(void* response, size_t length) {
		this->response.resize(length);
		memcpy(this->response.data(), response, length);
		this->notifier.release();
	}

	void Event::WaitResponse() {
		if (!hasResponded) {
			this->notifier.acquire();
			hasResponded = true;
		}
	}

}