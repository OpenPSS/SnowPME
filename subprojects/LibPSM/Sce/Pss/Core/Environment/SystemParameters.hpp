#ifndef LIB_PSS_SYSTEMPARAMETERS_H
#define LIB_PSS_SYSTEMPARAMETERS_H 1
#include <string>
#include <iostream>
#include <mono/mono.h>
#include <Sce/Pss/Core/Environment/ParameterKey.hpp>

namespace Sce::Pss::Core::Environment {
	

	class SystemParameters {
	public:
		static int GetInt(ParameterKey key, int *value);
		static int GetFloat(ParameterKey key, float *value);
		static int GetString(ParameterKey key, MonoString* *value);
	};
}
#endif
