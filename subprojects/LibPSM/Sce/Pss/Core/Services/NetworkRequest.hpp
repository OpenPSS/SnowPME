#ifndef LIB_PSS_NETWORKREQUEST_H
#define LIB_PSS_NETWORKREQUEST_H 1
#include <cstdint>

#include <string>
#include <iostream>
#include <mono/mono.h>

namespace Sce::Pss::Core::Services {
	class NetworkRequest {
	public:
		static int CreateRequestNative(int type, MonoString* function, MonoString* json, int* requestHandle);
		static int QueueRequestNative(int type, MonoString* function, MonoString* json, int* requestHandle);
		static int DestroyRequestNative(int requestHandle);
		static int GetResponseNative(int requestHandle, MonoString* response);
		static int RegisterThreadNative();
		static int UnregisterThreadNative();
	};
}
#endif
