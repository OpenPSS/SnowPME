#include "CameraImportDialog.hpp"

namespace Sce::PlayStation::Core::Device {
	int CameraImportDialog::NewNative(int type, int *handle){
		cout << "Sce::PlayStation::Core::Device::NewNative(int, int *) Unimplemented." << endl;
		return 0;
	}
	int CameraImportDialog::ReleaseNative(int type, int handle){
		cout << "Sce::PlayStation::Core::Device::ReleaseNative(int, int) Unimplemented." << endl;
		return 0;
	}
	int CameraImportDialog::OpenNative(int type, int handle, DialogArguments *dialogArguments){
		cout << "Sce::PlayStation::Core::Device::OpenNative(int, int, Sce::PlayStation::Core::Device::CameraImportDialog/DialogArguments *) Unimplemented." << endl;
		return 0;
	}
	int CameraImportDialog::AbortNative(int type, int handle){
		cout << "Sce::PlayStation::Core::Device::AbortNative(int, int) Unimplemented." << endl;
		return 0;
	}
	int CameraImportDialog::GetState(int type, int handle, CommonDialogState* commonDialogState){
		cout << "Sce::PlayStation::Core::Device::GetState(int, int, Sce::PlayStation::Core::Environment::CommonDialogState *) Unimplemented." << endl;
		return 0;
	}
	int CameraImportDialog::GetResult(int type, int handle, CommonDialogResult* commonDialogResult, DialogResults* dialogResults){
		cout << "Sce::PlayStation::Core::Device::GetResult(int, int, Sce::PlayStation::Core::Environment::CommonDialogResult *, Sce::PlayStation::Core::Device::CameraImportDialog/DialogResults *) Unimplemented." << endl;
		return 0;
	}
}
