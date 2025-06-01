#include <Sce/Pss/Core/Services/NetworkRequest.hpp>
#include <Sce/Pss/Core/Error.hpp>

namespace Sce::Pss::Core::Services {
	int NetworkRequest::CreateRequestNative(int type, std::string function, std::string json, int* requestHandle) {
		Unimplemented();
	}
	int NetworkRequest::QueueRequestNative(int type, std::string function, std::string json, int* requestHandle) {
		Unimplemented();
	}
	int NetworkRequest::DestroyRequestNative(int requestHandle) {
		Unimplemented();
	}
	int NetworkRequest::GetResponseNative(int requestHandle, std::string* response) {
		Unimplemented();
	}
	int NetworkRequest::RegisterThreadNative(){
		Unimplemented();
	}
	int NetworkRequest::UnregisterThreadNative(){
		Unimplemented();
	}
}
