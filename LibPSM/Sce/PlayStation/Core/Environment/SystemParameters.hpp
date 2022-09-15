#ifndef LIB_PSM_SYSTEMPARAMETERS_H
#define LIB_PSM_SYSTEMPARAMETERS_H 1
#include <cstdint>

#include <string>
#include <iostream>


namespace Sce::PlayStation::Core::Environment {
	enum ParameterKey : unsigned int
	{
		Language = 0,
		GamePadButtonMeaning = 1,
		YesNoLayout = 2,
		DisplayDpiX = 3,
		DisplayDpiY = 4
	};

	class SystemParameters {
	public:
		static int GetInt(ParameterKey key, int *value);
		static int GetFloat(ParameterKey key, float *value);
		static int GetString(ParameterKey key, std::string *value);
	};
}
#endif
