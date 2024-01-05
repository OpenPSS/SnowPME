#include <Sce/Pss/Core/Environment/SystemParameters.hpp>

namespace Sce::Pss::Core::Environment {
	int SystemParameters::GetInt(ParameterKey key, int *value){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int SystemParameters::GetFloat(ParameterKey key, float *value){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int SystemParameters::GetString(ParameterKey key, MonoString** value){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
}
