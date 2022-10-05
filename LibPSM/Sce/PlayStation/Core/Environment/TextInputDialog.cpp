#include "TextInputDialog.hpp"

namespace Sce::PlayStation::Core::Environment {
	int TextInputDialog::NewNative(CommonDialogType type, int *handle){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int TextInputDialog::ReleaseNative(CommonDialogType type, int handle){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int TextInputDialog::OpenNative(CommonDialogType type, int handle, Arguments *arguments){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int TextInputDialog::AbortNative(CommonDialogType type, int handle){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int TextInputDialog::GetState(CommonDialogType type, int handle, CommonDialogState *state){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
	int TextInputDialog::GetResult(CommonDialogType type, int handle, CommonDialogResult *result, Results *results){
		std::cout << __FUNCTION__ << " Unimplemented" << std::endl;
		return 0;
	}
}
