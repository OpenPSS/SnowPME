#include "InAppPurchaseDialog.hpp"

namespace Sce::PlayStation::Core::Services {
	int InAppPurchaseDialog::NewNative(int type, int* handle) {
		cout << "Sce::PlayStation::Core::Services::NewNative(int, int *) Unimplemented." << endl;
		return 0;
	}
	int InAppPurchaseDialog::ReleaseNative(int type, int handle) {
		cout << "Sce::PlayStation::Core::Services::ReleaseNative(int, int) Unimplemented." << endl;
		return 0;
	}
	int InAppPurchaseDialog::OpenNative(int type, int handle, CommandArguments* cmdArg) {
		cout << "Sce::PlayStation::Core::Services::OpenNative(int, int, Sce::PlayStation::Core::Services::InAppPurchaseDialog/CommandArguments *) Unimplemented." << endl;
		return 0;
	}
	int InAppPurchaseDialog::AbortNative(int type, int handle) {
		cout << "Sce::PlayStation::Core::Services::AbortNative(int, int) Unimplemented." << endl;
		return 0;
	}
	int InAppPurchaseDialog::GetState(int type, int handle, CommonDialogState* state) {
		cout << "Sce::PlayStation::Core::Services::GetState(int, int, Sce::PlayStation::Core::Environment::CommonDialogState *) Unimplemented." << endl;
		return 0;
	}
	int InAppPurchaseDialog::GetResult(int type, int handle, CommonDialogResult* result, CommandResults* results) {
		cout << "Sce::PlayStation::Core::Services::GetResult(int, int, Sce::PlayStation::Core::Environment::CommonDialogResult *, Sce::PlayStation::Core::Services::InAppPurchaseDialog/CommandResults *) Unimplemented." << endl;
		return 0;
	}
}
