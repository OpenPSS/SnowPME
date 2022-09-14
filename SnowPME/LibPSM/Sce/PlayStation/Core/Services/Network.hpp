#ifndef LIB_PSM_NETWORK_H
#define LIB_PSM_NETWORK_H 1
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <iostream>


namespace Sce::PlayStation::Core::Services {
	class Network {
	public:
		static int CheckStateNative(uint32_t * state);
		static int GetOnlineIdNative(std::string *id);
		static int GetAccountIdNative(unsigned long * id);
		static int SetWebRequestDelegate(uintptr_t handle);
		static int SetAuthServer(bool useAuth);
		static int GetAuthTicketDataNative(std::string *data);
		static int ResetAuthTicketNative();
		static int SetAppIdNative(std::string appId);
	};
}
#endif
