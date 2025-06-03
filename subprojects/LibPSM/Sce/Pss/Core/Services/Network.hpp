#ifndef LIB_PSS_NETWORK_H
#define LIB_PSS_NETWORK_H 1
#include <cstdint>
#include <string>
#include <iostream>
#define MONO_ZERO_LEN_ARRAY 1
#include <mono/mono.h>

namespace Sce::Pss::Core::Services {
	class Network {
	public:
		static int CheckStateNative(uint32_t * state);
		static int GetOnlineIdNative(MonoString *id);
		static int GetAccountIdNative(unsigned long * id);
		static int SetWebRequestDelegate(uintptr_t handle);
		static int SetAuthServer(bool useAuth);
		static int GetAuthTicketDataNative(MonoString *data);
		static int ResetAuthTicketNative();
		static int SetAppIdNative(MonoString* appId);
	};
}
#endif
