#include <Sce/Pss/Core/Services/NetworkRequest.hpp>
#include <Sce/Pss/Core/Error.hpp>

namespace Sce::Pss::Core::Services {
	int NetworkRequest::CreateRequestNative(int type, std::string function, std::string json, int* requestHandle) {
		UNIMPLEMENTED();
	}
	int NetworkRequest::QueueRequestNative(int type, std::string function, std::string json, int* requestHandle) {
		UNIMPLEMENTED();
	}
	int NetworkRequest::DestroyRequestNative(int requestHandle) {
		UNIMPLEMENTED();
	}
	int NetworkRequest::GetResponseNative(int requestHandle, std::string* response) {
		UNIMPLEMENTED();
	}
	int NetworkRequest::RegisterThreadNative(){
		UNIMPLEMENTED();
	}
	int NetworkRequest::UnregisterThreadNative(){
		UNIMPLEMENTED();
	}
}
