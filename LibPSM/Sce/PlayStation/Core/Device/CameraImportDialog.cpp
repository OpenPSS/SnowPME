#include "CameraImportDialog.hpp"

namespace Sce::PlayStation::Core::Device {
	int CameraImportDialog::NewNative(int type, int *handle){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int CameraImportDialog::ReleaseNative(int type, int handle){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int CameraImportDialog::OpenNative(int type, int handle, DialogArguments *dialogArguments){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int CameraImportDialog::AbortNative(int type, int handle){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int CameraImportDialog::GetState(int type, int handle, CommonDialogState* commonDialogState){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int CameraImportDialog::GetResult(int type, int handle, CommonDialogResult* commonDialogResult, DialogResults* dialogResults){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
}
