#include <LibShared.hpp>
#include <Sce/Pss/Core/Error.hpp>

#include <Sce/Pss/Core/Environment/CommonDialogType.hpp>
#include <Sce/Pss/Core/Environment/CommonDialogArguments.hpp>
#include <Sce/Pss/Core/Environment/CommonDialogResults.hpp>
#include <Sce/Pss/Core/Environment/CommonDialogResult.hpp>
#include <Sce/Pss/Core/Environment/CommonDialogState.hpp>
#include <Sce/Pss/Core/Environment/CommonDialog.hpp>

#include <Sce/Pss/Core/Services/InAppPurchaseDialog.hpp>
#include <Sce/Pss/Core/Services/InAppPurchaseCommandArguments.hpp>
#include <Sce/Pss/Core/Services/InAppPurchaseCommandResults.hpp>

#include <Sce/Pss/Core/ExceptionInfo.hpp>
#include <Sce/Pss/Core/System/Handles.hpp>
#include <Sce/Pss/Core/Threading/Thread.hpp>

using namespace Shared::Debug;
using namespace Sce::Pss::Core::Services;
using namespace Sce::Pss::Core::System;
using namespace Sce::Pss::Core::Threading;

namespace Sce::Pss::Core::Environment {
	
	int CommonDialog::CheckOpen() {
		if (!Thread::IsMainThread()) return PSM_ERROR_COMMON_INVALID_OPERATION;
		if (this->state.load() == CommonDialogState::Running) return PSM_ERROR_COMMON_INVALID_OPERATION;

		return PSM_ERROR_NO_ERROR;
	}
	
	int CommonDialog::CheckResult() {
		if (!Thread::IsMainThread()) return PSM_ERROR_COMMON_INVALID_OPERATION;

		return PSM_ERROR_NO_ERROR;
	}

	int CommonDialog::CheckAbort() {
		if (!Thread::IsMainThread()) return PSM_ERROR_COMMON_INVALID_OPERATION;

		return PSM_ERROR_NO_ERROR;
	}

	int CommonDialog::CheckState() {
		if (!Thread::IsMainThread()) return PSM_ERROR_COMMON_INVALID_OPERATION;

		return PSM_ERROR_NO_ERROR;
	}

	int CommonDialog::Abort() {
		Logger::Debug(__FUNCTION__);
		LOCK_GUARD();

		this->result.store(CommonDialogResult::Aborted);
		return PSM_ERROR_NO_ERROR;
	}
	int CommonDialog::Result(CommonDialogResult* result, CommonDialogResults* results) {
		Logger::Debug(__FUNCTION__);
		LOCK_GUARD();

		Logger::Warn("Using default CommonDialog::Result implemenation.");
		Logger::Warn("This is most likely incorrect, this common dialog might not be fully implemented?");

		if (result != nullptr) {
			*result = this->result.load();
		}


		return PSM_ERROR_NO_ERROR;
	}

	int CommonDialog::State(CommonDialogState* state) {
		Logger::Debug(__FUNCTION__);
		LOCK_GUARD();

		if (state == nullptr) return PSM_ERROR_COMMON_ARGUMENT_NULL;
		*state = this->state.load();
		return PSM_ERROR_NO_ERROR;
	}

	int CommonDialog::NewNative(CommonDialogType type, int* handle) {
		Logger::Debug(__FUNCTION__);
		LOCK_GUARD_STATIC();
		if (type >= CommonDialogType::PhotoImportDialog) return PSM_ERROR_COMMON_ARGUMENT;
		if (handle == nullptr) return PSM_ERROR_COMMON_ARGUMENT_NULL; 

		switch (type) {
			case CommonDialogType::Reserved0:
				Logger::Error("CommonDialogType::Reserved0 Unimplemented");
				return PSM_ERROR_NOT_IMPLEMENTED;
			case CommonDialogType::TextInput:
				Logger::Error("CommonDialogType::TextInput Unimplemented");
				return PSM_ERROR_NOT_IMPLEMENTED;
			case CommonDialogType::InAppPurchaseDialog:
			{
				Logger::Debug("CommonDialogType::InAppPurchaseDialog");

				// check an in app purchase dialog has not already been created.
				if (InAppPurchaseDialog::GetUniqueObject() != nullptr) {
					ExceptionInfo::AddMessage("InAppPurchaseDialog can have one instance at same time");
					return PSM_ERROR_COMMON_INVALID_OPERATION;
				}

				// create in app purchase common dialog,
				InAppPurchaseDialog* commonIapDialog = new InAppPurchaseDialog();
				ReturnErrorable(commonIapDialog);

				// set handle to the new in app purchase
				*handle = commonIapDialog->Handle;

				return PSM_ERROR_NO_ERROR;
			}
			case CommonDialogType::CameraImportDialog:
				Logger::Error("CommonDialogType::CameraImportDialog Unimplemented");
				return PSM_ERROR_NOT_IMPLEMENTED;
			case CommonDialogType::PhotoImportDialog:
				Logger::Error("CommonDialogType::PhotoImportDialog Unimplemented");
				return PSM_ERROR_NOT_IMPLEMENTED;
		}

		return PSM_ERROR_NO_ERROR;
	}
	int CommonDialog::ReleaseNative(CommonDialogType type, int handle) {
		Logger::Debug(__FUNCTION__);
		LOCK_GUARD_STATIC();

		if (!Handles::IsValid(handle)) return PSM_ERROR_COMMON_OBJECT_DISPOSED;
		delete Handles::Get<CommonDialog>(handle);

		return PSM_ERROR_NO_ERROR;
	}
	int CommonDialog::OpenNative(CommonDialogType type, int handle, CommonDialogArguments* cmdArg) {
		Logger::Debug(__FUNCTION__);
		LOCK_GUARD_STATIC();

		if (type >= CommonDialogType::PhotoImportDialog) return PSM_ERROR_COMMON_ARGUMENT; 
		if (cmdArg == nullptr) return PSM_ERROR_COMMON_ARGUMENT_NULL;
		if (!Handles::IsValid(handle)) return PSM_ERROR_COMMON_OBJECT_DISPOSED;

		CommonDialog* cDialog = Handles::Get<CommonDialog>(handle);

		if (cDialog == nullptr) return PSM_ERROR_COMMON_OBJECT_DISPOSED;

		// I think this is actually a bit inaccurate for some InAppPurchaseDialog commands ...
		// i beleive the "Already Purchased" error is meant to be checked before the
		// "already running something" one, atleast, on the windows psm.exe implementation ..
		// todo: figure out if this is true on android/vita too;
		// 
		// no games actually call it while its already running, but thats possibly worth noting/fixing.

		int err = cDialog->CheckOpen();
		if (err != PSM_ERROR_NO_ERROR) {
			return err;
		}

		return cDialog->Open(cmdArg);
	}
	int CommonDialog::AbortNative(CommonDialogType type, int handle) {
		Logger::Debug(__FUNCTION__);
		LOCK_GUARD_STATIC();

		if (!Handles::IsValid(handle)) return PSM_ERROR_COMMON_OBJECT_DISPOSED;

		// get common dialog object, and check if it is valid
		CommonDialog* cDialog = Handles::Get<CommonDialog>(handle);
		if (cDialog == nullptr) return PSM_ERROR_COMMON_OBJECT_DISPOSED;

		int err = cDialog->CheckAbort();
		if (err != PSM_ERROR_NO_ERROR) {
			return err;
		}

		return cDialog->Abort();
	}
	int CommonDialog::GetState(CommonDialogType type, int handle, CommonDialogState* state) {
		Logger::Debug(__FUNCTION__);
		LOCK_GUARD_STATIC();
		
		if (state == nullptr) return PSM_ERROR_COMMON_ARGUMENT_NULL;
		if (!Handles::IsValid(handle)) return PSM_ERROR_COMMON_OBJECT_DISPOSED;
		
		// get common dialog object, and check if it is valid
		CommonDialog* cDialog = Handles::Get<CommonDialog>(handle);
		if (cDialog == nullptr) return PSM_ERROR_COMMON_OBJECT_DISPOSED;

		int err = cDialog->CheckState();
		if (err != PSM_ERROR_NO_ERROR) {
			return err;
		}

		return cDialog->State(state);
	}
	int CommonDialog::GetResult(CommonDialogType type, int handle, CommonDialogResult* result, CommonDialogResults* results) {
		Logger::Debug(__FUNCTION__);
		LOCK_GUARD_STATIC();

		if (result == nullptr) return PSM_ERROR_COMMON_ARGUMENT_NULL;
		if (results == nullptr) return PSM_ERROR_COMMON_ARGUMENT_NULL;
		if (!Handles::IsValid(handle)) return PSM_ERROR_COMMON_OBJECT_DISPOSED;
		if (type >= CommonDialogType::PhotoImportDialog) return PSM_ERROR_COMMON_ARGUMENT;
		
		// get common dialog object, and check if it is valid
		CommonDialog* cDialog = Handles::Get<CommonDialog>(handle);
		if (cDialog == nullptr) return PSM_ERROR_COMMON_INVALID_OPERATION;

		int err = cDialog->CheckResult();
		if (err != PSM_ERROR_NO_ERROR) {
			return err;
		}

		return cDialog->Result(result, results);

	}
}
