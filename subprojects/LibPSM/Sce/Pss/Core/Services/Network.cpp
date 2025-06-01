#include <Sce/Pss/Core/Services/Network.hpp>
#include <Sce/Pss/Core/Error.hpp>

namespace Sce::Pss::Core::Services {
	int Network::CheckStateNative(uint32_t* state){
		Unimplemented();
	}
	int Network::GetOnlineIdNative(std::string* id) {
		Unimplemented();
	}
	int Network::GetAccountIdNative(unsigned long* id){
		Unimplemented();
	}
	int Network::SetWebRequestDelegate(uintptr_t handle){
		Unimplemented();
	}
	int Network::SetAuthServer(bool useAuth){
		Unimplemented();
	}
	int Network::GetAuthTicketDataNative(std::string* data) {
		Unimplemented();
	}
	int Network::ResetAuthTicketNative(){
		Unimplemented();
	}
	int Network::SetAppIdNative(std::string appId){
		Unimplemented();
	}
}
