#ifndef SHARED_NAMEDEVENT_H
#define SHARED_NAMEDEVENT_H 1
#include <Windowing/EventType.hpp>
#include <Debug/Assert.hpp>
#include <String/Format.hpp>

#include <random>
#include <vector>
#include <cstdint>
#include <string>
#include <semaphore>
#include <atomic>

namespace Shared::Windowing {

	class Event {
	private:
		EventType typeId = EventType::None;
		uint32_t uid = rand();
		std::vector<std::byte> arguments;
		std::vector<std::byte> response;
		std::binary_semaphore notifier{0};
		std::atomic<bool> hasResponded = false;
	public:
		uint32_t Uid();
		EventType TypeID();

		Event(EventType typeId, std::vector<std::byte>& args);
		Event(EventType typeId, void* args, size_t length);
		Event(EventType typeId);

		std::vector<std::byte>& ArgumentVec();
		std::byte* ArgumentArray();
		std::byte ArgumentByte(int index);
		size_t ArgumentCount();

		std::vector<std::byte>& ResponseVec();
		std::byte* ResponseArray();
		std::byte ResponseByte(int index);
		size_t ResponseCount();


		void PutArguments(std::vector<std::byte>& args);
		void PutArguments(void* args, size_t length);

		void PutResponse(std::vector<std::byte>& response);
		void PutResponse(void* response, size_t length);

		bool HasResponse();
		void WaitResponse();

	};

}


#endif