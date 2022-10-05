#include "NetworkRequest.hpp"

namespace Sce::PlayStation::Core::Services {
	int NetworkRequest::CreateRequestNative(int type, std::string function, std::string json, int* requestHandle) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int NetworkRequest::QueueRequestNative(int type, std::string function, std::string json, int* requestHandle) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int NetworkRequest::DestroyRequestNative(int requestHandle) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int NetworkRequest::GetResponseNative(int requestHandle, std::string* response) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int NetworkRequest::RegisterThreadNative(){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int NetworkRequest::UnregisterThreadNative(){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
}
