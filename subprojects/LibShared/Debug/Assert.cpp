#include <Debug/Assert.hpp>
#include <Windowing/WindowControl.hpp>
using namespace Shared::Windowing;

namespace Shared::Debug {

	void Assert::CrossPlatformAssertDialog(std::string message, std::string file, uint32_t lineNumber) {
		std::string assertMsg = "ASSERTION FAILED!\n\n" + message + "\n\nin file: " + file + ":" + std::to_string(lineNumber);

		if (WindowControl::IsInitalized()) {
			if (WindowControl::YesNoDialog(assertMsg, "ASSERTION!")) {
				std::abort();
			}
		}
		else {
			Logger::Error(assertMsg);
			std::abort();
		}

	}
}