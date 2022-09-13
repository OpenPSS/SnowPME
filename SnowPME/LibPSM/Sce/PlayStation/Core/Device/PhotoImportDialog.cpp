#include "PhotoImportDialog.hpp"

namespace Sce::PlayStation::Core::Device {
	int PhotoImportDialog::NewNative(int type, int *handle){
		cout << "Sce::PlayStation::Core::Device::NewNative(int, int *) Unimplemented." << endl;
		return 0;
	}
	int PhotoImportDialog::ReleaseNative(int type, int handle){
		cout << "Sce::PlayStation::Core::Device::ReleaseNative(int, int) Unimplemented." << endl;
		return 0;
	}
	int PhotoImportDialog::OpenNative(int type, int handle, DialogArguments *dialogArguments){
		cout << "Sce::PlayStation::Core::Device::OpenNative(int, int, Sce::PlayStation::Core::Device::PhotoImportDialog/DialogArguments *) Unimplemented." << endl;
		return 0;
	}
	int PhotoImportDialog::AbortNative(int type, int handle){
		cout << "Sce::PlayStation::Core::Device::AbortNative(int, int) Unimplemented." << endl;
		return 0;
	}
	int PhotoImportDialog::GetState(int type, int handle, CommonDialogState *commonDialogState){
		cout << "Sce::PlayStation::Core::Device::GetState(int, int, Sce::PlayStation::Core::Environment::CommonDialogState *) Unimplemented." << endl;
		return 0;
	}
	int PhotoImportDialog::GetResult(int type, int handle, CommonDialogResult *commonDialogState, DialogResults *dialogResults){
		cout << "Sce::PlayStation::Core::Device::GetResult(int, int, Sce::PlayStation::Core::Environment::CommonDialogResult *, Sce::PlayStation::Core::Device::PhotoImportDialog/DialogResults *) Unimplemented." << endl;
		return 0;
	}
}
