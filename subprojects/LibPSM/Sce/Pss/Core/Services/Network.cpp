#include <Sce/Pss/Core/Services/Network.hpp>
#include <Sce/Pss/Core/Error.hpp>
#include <mono/mono.h>

namespace Sce::Pss::Core::Services {
	int Network::CheckStateNative(uint32_t* state){
		UNIMPLEMENTED();
	}
	int Network::GetOnlineIdNative(MonoString* id) {
		UNIMPLEMENTED();
	}
	int Network::GetAccountIdNative(unsigned long* id){
		UNIMPLEMENTED();
	}
	int Network::SetWebRequestDelegate(uintptr_t handle){
		UNIMPLEMENTED();
	}
	int Network::SetAuthServer(bool useAuth){
		UNIMPLEMENTED();
	}
	int Network::GetAuthTicketDataNative(MonoString* data) {
		UNIMPLEMENTED();
	}
	int Network::ResetAuthTicketNative(){
		UNIMPLEMENTED();
	}
	int Network::SetAppIdNative(MonoString* appId){
		UNIMPLEMENTED();
	}
}
