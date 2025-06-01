#include <Sce/Pss/Core/Services/Network.hpp>
#include <Sce/Pss/Core/Error.hpp>

namespace Sce::Pss::Core::Services {
	int Network::CheckStateNative(uint32_t* state){
		UNIMPLEMENTED();
	}
	int Network::GetOnlineIdNative(std::string* id) {
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
	int Network::GetAuthTicketDataNative(std::string* data) {
		UNIMPLEMENTED();
	}
	int Network::ResetAuthTicketNative(){
		UNIMPLEMENTED();
	}
	int Network::SetAppIdNative(std::string appId){
		UNIMPLEMENTED();
	}
}
