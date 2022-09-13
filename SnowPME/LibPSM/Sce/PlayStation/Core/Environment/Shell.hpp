#ifndef LIB_PSM_SHELL_H
#define LIB_PSM_SHELL_H 1
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <iostream>
using namespace std;

namespace Sce::PlayStation::Core::Environment {

	enum ActionType : unsigned int
	{
		None = 0,
		Browser = 1
	};

	typedef struct Action
	{
		ActionType type;
		string parameter0;
		string parameter1;
		string parameter2;
		string parameter3;
	} Action;

	class Shell {
	public:
		static int ExecuteNative(Action *data);
	};
}
#endif
