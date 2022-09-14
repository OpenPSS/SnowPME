#include "InAppPurchaseDialog.hpp"

namespace Sce::PlayStation::Core::Services {
	int InAppPurchaseDialog::NewNative(int type, int* handle) {
		std::cout << "Sce::PlayStation::Core::Services::NewNative(int, int *) Unimplemented." << std::endl;
		return 0;
	}
	int InAppPurchaseDialog::ReleaseNative(int type, int handle) {
		std::cout << "Sce::PlayStation::Core::Services::ReleaseNative(int, int) Unimplemented." << std::endl;
		return 0;
	}
	int InAppPurchaseDialog::OpenNative(int type, int handle, CommandArguments* cmdArg) {
		std::cout << "Sce::PlayStation::Core::Services::OpenNative(int, int, Sce::PlayStation::Core::Services::InAppPurchaseDialog/CommandArguments *) Unimplemented." << std::endl;
		return 0;
	}
	int InAppPurchaseDialog::AbortNative(int type, int handle) {
		std::cout << "Sce::PlayStation::Core::Services::AbortNative(int, int) Unimplemented." << std::endl;
		return 0;
	}
	int InAppPurchaseDialog::GetState(int type, int handle, CommonDialogState* state) {
		std::cout << "Sce::PlayStation::Core::Services::GetState(int, int, Sce::PlayStation::Core::Environment::CommonDialogState *) Unimplemented." << std::endl;
		return 0;
	}
	int InAppPurchaseDialog::GetResult(int type, int handle, CommonDialogResult* result, CommandResults* results) {
		std::cout << "Sce::PlayStation::Core::Services::GetResult(int, int, Sce::PlayStation::Core::Environment::CommonDialogResult *, Sce::PlayStation::Core::Services::InAppPurchaseDialog/CommandResults *) Unimplemented." << std::endl;
		return 0;
	}
}
