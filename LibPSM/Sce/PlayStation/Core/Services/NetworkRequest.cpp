#include "NetworkRequest.hpp"

namespace Sce::PlayStation::Core::Services {
	int NetworkRequest::CreateRequestNative(int type, std::string function, std::string json, int* requestHandle) {
		std::cout << "Sce::PlayStation::Core::Services::CreateRequestNative(int, string, string, int *) Unimplemented." << std::endl;
		return 0;
	}
	int NetworkRequest::QueueRequestNative(int type, std::string function, std::string json, int* requestHandle) {
		std::cout << "Sce::PlayStation::Core::Services::QueueRequestNative(int, string, string, int *) Unimplemented." << std::endl;
		return 0;
	}
	int NetworkRequest::DestroyRequestNative(int requestHandle) {
		std::cout << "Sce::PlayStation::Core::Services::DestroyRequestNative(int) Unimplemented." << std::endl;
		return 0;
	}
	int NetworkRequest::GetResponseNative(int requestHandle, std::string* response) {
		std::cout << "Sce::PlayStation::Core::Services::GetResponseNative(int, string *) Unimplemented." << std::endl;
		return 0;
	}
	int NetworkRequest::RegisterThreadNative(){
		std::cout << "Sce::PlayStation::Core::Services::RegisterThreadNative() Unimplemented." << std::endl;
		return 0;
	}
	int NetworkRequest::UnregisterThreadNative(){
		std::cout << "Sce::PlayStation::Core::Services::UnregisterThreadNative() Unimplemented." << std::endl;
		return 0;
	}
}
