#ifndef LIB_PSM_SHELL_H
#define LIB_PSM_SHELL_H 1
#include <cstdint>

#include <string>
#include <iostream>


namespace Sce::PlayStation::Core::Environment {

	enum ActionType : unsigned int
	{
		None = 0,
		Browser = 1
	};

	typedef struct Action
	{
		ActionType type;
		std::string parameter0;
		std::string parameter1;
		std::string parameter2;
		std::string parameter3;
	} Action;

	class Shell {
	public:
		static int ExecuteNative(Action *data);
	};
}
#endif
