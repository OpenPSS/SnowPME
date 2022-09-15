#include "PhotoImportDialog.hpp"

namespace Sce::PlayStation::Core::Device {
	int PhotoImportDialog::NewNative(int type, int *handle){
		std::cout << "Sce::PlayStation::Core::Device::NewNative(int, int *) Unimplemented." << std::endl;
		return 0;
	}
	int PhotoImportDialog::ReleaseNative(int type, int handle){
		std::cout << "Sce::PlayStation::Core::Device::ReleaseNative(int, int) Unimplemented." << std::endl;
		return 0;
	}
	int PhotoImportDialog::OpenNative(int type, int handle, DialogArguments *dialogArguments){
		std::cout << "Sce::PlayStation::Core::Device::OpenNative(int, int, Sce::PlayStation::Core::Device::PhotoImportDialog/DialogArguments *) Unimplemented." << std::endl;
		return 0;
	}
	int PhotoImportDialog::AbortNative(int type, int handle){
		std::cout << "Sce::PlayStation::Core::Device::AbortNative(int, int) Unimplemented." << std::endl;
		return 0;
	}
	int PhotoImportDialog::GetState(int type, int handle, CommonDialogState *commonDialogState){
		std::cout << "Sce::PlayStation::Core::Device::GetState(int, int, Sce::PlayStation::Core::Environment::CommonDialogState *) Unimplemented." << std::endl;
		return 0;
	}
	int PhotoImportDialog::GetResult(int type, int handle, CommonDialogResult *commonDialogState, DialogResults *dialogResults){
		std::cout << "Sce::PlayStation::Core::Device::GetResult(int, int, Sce::PlayStation::Core::Environment::CommonDialogResult *, Sce::PlayStation::Core::Device::PhotoImportDialog/DialogResults *) Unimplemented." << std::endl;
		return 0;
	}
}
