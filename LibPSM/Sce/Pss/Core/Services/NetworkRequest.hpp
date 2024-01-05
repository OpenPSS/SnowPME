#ifndef LIB_PSS_NETWORKREQUEST_H
#define LIB_PSS_NETWORKREQUEST_H 1
#include <cstdint>

#include <string>
#include <iostream>


namespace Sce::Pss::Core::Services {
	class NetworkRequest {
	public:
		static int CreateRequestNative(int type, std::string function, std::string json, int *requestHandle);
		static int QueueRequestNative(int type, std::string function, std::string json, int *requestHandle);
		static int DestroyRequestNative(int requestHandle);
		static int GetResponseNative(int requestHandle, std::string *response);
		static int RegisterThreadNative();
		static int UnregisterThreadNative();
	};
}
#endif
