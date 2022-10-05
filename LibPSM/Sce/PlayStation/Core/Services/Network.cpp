#include "Network.hpp"

namespace Sce::PlayStation::Core::Services {
	int Network::CheckStateNative(uint32_t* state){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int Network::GetOnlineIdNative(std::string* id) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int Network::GetAccountIdNative(unsigned long* id){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int Network::SetWebRequestDelegate(uintptr_t handle){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int Network::SetAuthServer(bool useAuth){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int Network::GetAuthTicketDataNative(std::string* data) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int Network::ResetAuthTicketNative(){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int Network::SetAppIdNative(std::string appId){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
}
