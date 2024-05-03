#include <Sce/Pss/Core/Environment/CommonDialogState.hpp>
#include <Sce/Pss/Core/Environment/CommonDialogResult.hpp>
#include <Sce/Pss/Core/Services/InAppPurchaseDialog.hpp>

namespace Sce::Pss::Core::Services {
	int InAppPurchaseDialog::NewNative(int type, int* handle) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int InAppPurchaseDialog::ReleaseNative(int type, int handle) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int InAppPurchaseDialog::OpenNative(int type, int handle, CommandArguments* cmdArg) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int InAppPurchaseDialog::AbortNative(int type, int handle) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int InAppPurchaseDialog::GetState(int type, int handle, Sce::Pss::Core::Environment::CommonDialogState* state) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int InAppPurchaseDialog::GetResult(int type, int handle, Sce::Pss::Core::Environment::CommonDialogResult* result, CommandResults* results) {
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
}
