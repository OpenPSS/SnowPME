#include "SystemParameters.hpp"

namespace Sce::PlayStation::Core::Environment {
	int SystemParameters::GetInt(ParameterKey key, int *value){
		std::cout << "Sce::PlayStation::Core::Environment::GetInt(Sce::PlayStation::Core::Environment::SystemParameters/ParameterKey, int *) Unimplemented." << std::endl;
		return 0;
	}
	int SystemParameters::GetFloat(ParameterKey key, float *value){
		std::cout << "Sce::PlayStation::Core::Environment::GetFloat(Sce::PlayStation::Core::Environment::SystemParameters/ParameterKey, float *) Unimplemented." << std::endl;
		return 0;
	}
	int SystemParameters::GetString(ParameterKey key, std::string *value){
		std::cout << "Sce::PlayStation::Core::Environment::GetString(Sce::PlayStation::Core::Environment::SystemParameters/ParameterKey, string *) Unimplemented." << std::endl;
		return 0;
	}
}
