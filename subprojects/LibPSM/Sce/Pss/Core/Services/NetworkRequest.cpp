#include <Sce/Pss/Core/Services/NetworkRequest.hpp>
#include <Sce/Pss/Core/Error.hpp>
#include <mono/mono.h>

namespace Sce::Pss::Core::Services {
	int NetworkRequest::CreateRequestNative(int type, MonoString* function, MonoString* json, int* requestHandle) {
		UNIMPLEMENTED();
	}
	int NetworkRequest::QueueRequestNative(int type, MonoString* function, MonoString* json, int* requestHandle) {
		UNIMPLEMENTED();
	}
	int NetworkRequest::DestroyRequestNative(int requestHandle) {
		UNIMPLEMENTED();
	}
	int NetworkRequest::GetResponseNative(int requestHandle, MonoString* response) {
		UNIMPLEMENTED();
	}
	int NetworkRequest::RegisterThreadNative(){
		UNIMPLEMENTED();
	}
	int NetworkRequest::UnregisterThreadNative(){
		UNIMPLEMENTED();
	}
}
