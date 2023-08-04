#ifndef LIB_PSM_SYSTEMPARAMETERS_H
#define LIB_PSM_SYSTEMPARAMETERS_H 1
#include <string>
#include <iostream>
#include <mono/mono.h>
#include <Sce/PlayStation/Core/Environment/ParameterKey.hpp>

namespace Sce::PlayStation::Core::Environment {
	

	class SystemParameters {
	public:
		static int GetInt(ParameterKey key, int *value);
		static int GetFloat(ParameterKey key, float *value);
		static int GetString(ParameterKey key, MonoString* *value);
	};
}
#endif
