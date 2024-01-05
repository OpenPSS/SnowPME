#include "PhotoImportDialog.hpp"

namespace Sce::Pss::Core::Device {
	int PhotoImportDialog::NewNative(int type, int *handle){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PhotoImportDialog::ReleaseNative(int type, int handle){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PhotoImportDialog::OpenNative(int type, int handle, DialogArguments *dialogArguments){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PhotoImportDialog::AbortNative(int type, int handle){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PhotoImportDialog::GetState(int type, int handle, CommonDialogState *commonDialogState){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int PhotoImportDialog::GetResult(int type, int handle, CommonDialogResult *commonDialogState, DialogResults *dialogResults){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
}
