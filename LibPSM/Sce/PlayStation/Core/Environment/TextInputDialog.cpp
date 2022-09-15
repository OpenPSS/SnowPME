#include "TextInputDialog.hpp"

namespace Sce::PlayStation::Core::Environment {
	int TextInputDialog::NewNative(CommonDialogType type, int *handle){
		std::cout << "Sce::PlayStation::Core::Environment::NewNative(Sce::PlayStation::Core::Environment::CommonDialogType, int *) Unimplemented." << std::endl;
		return 0;
	}
	int TextInputDialog::ReleaseNative(CommonDialogType type, int handle){
		std::cout << "Sce::PlayStation::Core::Environment::ReleaseNative(Sce::PlayStation::Core::Environment::CommonDialogType, int) Unimplemented." << std::endl;
		return 0;
	}
	int TextInputDialog::OpenNative(CommonDialogType type, int handle, Arguments *arguments){
		std::cout << "Sce::PlayStation::Core::Environment::OpenNative(Sce::PlayStation::Core::Environment::CommonDialogType, int, Sce::PlayStation::Core::Environment::TextInputDialog/Arguments *) Unimplemented." << std::endl;
		return 0;
	}
	int TextInputDialog::AbortNative(CommonDialogType type, int handle){
		std::cout << "Sce::PlayStation::Core::Environment::AbortNative(Sce::PlayStation::Core::Environment::CommonDialogType, int) Unimplemented." << std::endl;
		return 0;
	}
	int TextInputDialog::GetState(CommonDialogType type, int handle, CommonDialogState *state){
		std::cout << "Sce::PlayStation::Core::Environment::GetState(Sce::PlayStation::Core::Environment::CommonDialogType, int, Sce::PlayStation::Core::Environment::CommonDialogState *) Unimplemented." << std::endl;
		return 0;
	}
	int TextInputDialog::GetResult(CommonDialogType type, int handle, CommonDialogResult *result, Results *results){
		std::cout << "Sce::PlayStation::Core::Environment::GetResult(Sce::PlayStation::Core::Environment::CommonDialogType, int, Sce::PlayStation::Core::Environment::CommonDialogResult *, Sce::PlayStation::Core::Environment::TextInputDialog/Results *) Unimplemented." << std::endl;
		return 0;
	}
}
