#ifndef SHARED_ASSERT_H
#define SHARED_ASSERT_H 1
#include <cassert>
#include <cstdlib>
#include <cstdint>
#include <string>
#include <Debug/Logger.hpp>


namespace Shared::Debug {
	class Assert {
	public:
		static void CrossPlatformAssertDialog(std::string message, std::string file, uint32_t lineNumber);
	};

	#define _PANIC_MESSAGE(msg) Shared::Debug::Assert::CrossPlatformAssertDialog(msg, std::string(__FILE__), static_cast<uint32_t>(__LINE__))

	#define ASSERT(expression) if(!(expression)) { \
									_PANIC_MESSAGE(#expression); \
								}

	#ifdef NDEBUG
	#undef assert
	#define assert ASSERT
	#endif

	#define PANIC(message) _PANIC_MESSAGE(message);

}

#endif