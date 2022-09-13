#ifndef LIB_PSM_NETWORK_H
#define LIB_PSM_NETWORK_H 1
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <iostream>
using namespace std;

namespace Sce::PlayStation::Core::Services {
	class Network {
	public:
		static int CheckStateNative(uint32_t * state);
		static int GetOnlineIdNative(string *id);
		static int GetAccountIdNative(unsigned long * id);
		static int SetWebRequestDelegate(uintptr_t handle);
		static int SetAuthServer(bool useAuth);
		static int GetAuthTicketDataNative(string *data);
		static int ResetAuthTicketNative();
		static int SetAppIdNative(string appId);
	};
}
#endif
