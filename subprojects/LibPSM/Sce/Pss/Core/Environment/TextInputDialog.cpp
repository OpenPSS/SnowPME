#include <Sce/Pss/Core/Environment/TextInputDialog.hpp>
#include <Sce/Pss/Core/Error.hpp>

namespace Sce::Pss::Core::Environment {
	int TextInputDialog::NewNative(CommonDialogType type, int *handle){
		Unimplemented();
	}
	int TextInputDialog::ReleaseNative(CommonDialogType type, int handle){
		Unimplemented();
	}
	int TextInputDialog::OpenNative(CommonDialogType type, int handle, Arguments *arguments){
		Unimplemented();
	}
	int TextInputDialog::AbortNative(CommonDialogType type, int handle){
		Unimplemented();
	}
	int TextInputDialog::GetState(CommonDialogType type, int handle, CommonDialogState *state){
		Unimplemented();
	}
	int TextInputDialog::GetResult(CommonDialogType type, int handle, CommonDialogResult *result, Results *results){
		Unimplemented();
	}
}
