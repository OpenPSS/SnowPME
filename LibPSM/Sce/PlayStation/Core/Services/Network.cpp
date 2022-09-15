#include "Network.hpp"

namespace Sce::PlayStation::Core::Services {
	int Network::CheckStateNative(uint32_t* state){
		std::cout << "Sce::PlayStation::Core::Services::CheckStateNative(uint32_t *) Unimplemented." << std::endl;
		return 0;
	}
	int Network::GetOnlineIdNative(std::string* id) {
		std::cout << "Sce::PlayStation::Core::Services::GetOnlineIdNative(string *) Unimplemented." << std::endl;
		return 0;
	}
	int Network::GetAccountIdNative(unsigned long* id){
		std::cout << "Sce::PlayStation::Core::Services::GetAccountIdNative(unsigned long *) Unimplemented." << std::endl;
		return 0;
	}
	int Network::SetWebRequestDelegate(uintptr_t handle){
		std::cout << "Sce::PlayStation::Core::Services::SetWebRequestDelegate(intptr) Unimplemented." << std::endl;
		return 0;
	}
	int Network::SetAuthServer(bool useAuth){
		std::cout << "Sce::PlayStation::Core::Services::SetAuthServer(bool) Unimplemented." << std::endl;
		return 0;
	}
	int Network::GetAuthTicketDataNative(std::string* data) {
		std::cout << "Sce::PlayStation::Core::Services::GetAuthTicketDataNative(string *) Unimplemented." << std::endl;
		return 0;
	}
	int Network::ResetAuthTicketNative(){
		std::cout << "Sce::PlayStation::Core::Services::ResetAuthTicketNative() Unimplemented." << std::endl;
		return 0;
	}
	int Network::SetAppIdNative(std::string appId){
		std::cout << "Sce::PlayStation::Core::Services::SetAppIdNative(string)) Unimplemented." << std::endl;
		return 0;
	}
}
