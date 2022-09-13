#ifndef LIB_PSM_NETWORKREQUEST_H
#define LIB_PSM_NETWORKREQUEST_H 1
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <iostream>
using namespace std;

namespace Sce::PlayStation::Core::Services {
	class NetworkRequest {
	public:
		static int CreateRequestNative(int type, string function, string json, int *requestHandle);
		static int QueueRequestNative(int type, string function, string json, int *requestHandle);
		static int DestroyRequestNative(int requestHandle);
		static int GetResponseNative(int requestHandle, string *response);
		static int RegisterThreadNative();
		static int UnregisterThreadNative();
	};
}
#endif
