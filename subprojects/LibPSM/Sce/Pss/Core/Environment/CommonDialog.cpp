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

using namespace Shared::Debug;
using namespace Sce::Pss::Core::Services;
using namespace Sce::Pss::Core::System;

namespace Sce::Pss::Core::Environment {
	
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
		
		return Handles::Get<CommonDialog>(handle)->Open(cmdArg);
	}
	int CommonDialog::AbortNative(CommonDialogType type, int handle) {
		Logger::Debug(__FUNCTION__);
		LOCK_GUARD_STATIC();

		if (!Handles::IsValid(handle)) return PSM_ERROR_COMMON_OBJECT_DISPOSED;

		return Handles::Get<CommonDialog>(handle)->Abort();
	}
	int CommonDialog::GetState(CommonDialogType type, int handle, CommonDialogState* state) {
		Logger::Debug(__FUNCTION__);
		LOCK_GUARD_STATIC();
		
		if (state == nullptr) return PSM_ERROR_COMMON_ARGUMENT_NULL;
		if (!Handles::IsValid(handle)) return PSM_ERROR_COMMON_OBJECT_DISPOSED;

		return Handles::Get<CommonDialog>(handle)->State(state);
	}
	int CommonDialog::GetResult(CommonDialogType type, int handle, CommonDialogResult* result, CommonDialogResults* results) {
		Logger::Debug(__FUNCTION__);
		LOCK_GUARD_STATIC();

		if (result == nullptr) return PSM_ERROR_COMMON_ARGUMENT_NULL;
		if (results == nullptr) return PSM_ERROR_COMMON_ARGUMENT_NULL;
		if (!Handles::IsValid(handle)) return PSM_ERROR_COMMON_OBJECT_DISPOSED;
		if (type >= CommonDialogType::PhotoImportDialog) return PSM_ERROR_COMMON_ARGUMENT;

		return Handles::Get<CommonDialog>(handle)->Result(result, results);

	}
}
