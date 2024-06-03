#include <LibShared.hpp>
#include <Sce/Pss/Core/Error.hpp>

#include <Sce/Pss/Core/Environment/CommonDialogType.hpp>
#include <Sce/Pss/Core/Environment/CommonDialogArguments.hpp>
#include <Sce/Pss/Core/Environment/CommonDialogResults.hpp>
#include <Sce/Pss/Core/Environment/CommonDialogResult.hpp>
#include <Sce/Pss/Core/Environment/CommonDialogState.hpp>
#include <Sce/Pss/Core/Environment/CommonDialog.hpp>
using namespace Shared::Debug;

namespace Sce::Pss::Core::Environment {
	int CommonDialog::NewNative(CommonDialogType type, int* handle) {
		Logger::Debug(__FUNCTION__);

		switch (type) {
			case CommonDialogType::Reserved0:
				Logger::Error("CommonDialogType::Reserved0 Unimplemented");
				return PSM_ERROR_NOT_IMPLEMENTED;
			case CommonDialogType::TextInput:
				Logger::Error("CommonDialogType::TextInput Unimplemented");
				return PSM_ERROR_NOT_IMPLEMENTED;
			case CommonDialogType::InAppPurchaseDialog:
				Logger::Error("CommonDialogType::InAppPurchaseDialog Unimplemented");
				return PSM_ERROR_NOT_IMPLEMENTED;
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

		switch (type) {
		case CommonDialogType::Reserved0:
			Logger::Error("CommonDialogType::Reserved0 Unimplemented");
			return PSM_ERROR_NOT_IMPLEMENTED;
		case CommonDialogType::TextInput:
			Logger::Error("CommonDialogType::TextInput Unimplemented");
			return PSM_ERROR_NOT_IMPLEMENTED;
		case CommonDialogType::InAppPurchaseDialog:
			Logger::Error("CommonDialogType::InAppPurchaseDialog Unimplemented");
			return PSM_ERROR_NOT_IMPLEMENTED;
		case CommonDialogType::CameraImportDialog:
			Logger::Error("CommonDialogType::CameraImportDialog Unimplemented");
			return PSM_ERROR_NOT_IMPLEMENTED;
		case CommonDialogType::PhotoImportDialog:
			Logger::Error("CommonDialogType::PhotoImportDialog Unimplemented");
			return PSM_ERROR_NOT_IMPLEMENTED;
		}

		return PSM_ERROR_NO_ERROR;
	}
	int CommonDialog::OpenNative(CommonDialogType type, int handle, CommonDialogArguments* cmdArg) {
		Logger::Debug(__FUNCTION__);

		switch (type) {
		case CommonDialogType::Reserved0:
			Logger::Error("CommonDialogType::Reserved0 Unimplemented");
			return PSM_ERROR_NOT_IMPLEMENTED;
		case CommonDialogType::TextInput:
			Logger::Error("CommonDialogType::TextInput Unimplemented");
			return PSM_ERROR_NOT_IMPLEMENTED;
		case CommonDialogType::InAppPurchaseDialog:
			Logger::Error("CommonDialogType::InAppPurchaseDialog Unimplemented");
			return PSM_ERROR_NOT_IMPLEMENTED;
		case CommonDialogType::CameraImportDialog:
			Logger::Error("CommonDialogType::CameraImportDialog Unimplemented");
			return PSM_ERROR_NOT_IMPLEMENTED;
		case CommonDialogType::PhotoImportDialog:
			Logger::Error("CommonDialogType::PhotoImportDialog Unimplemented");
			return PSM_ERROR_NOT_IMPLEMENTED;
		}

		return PSM_ERROR_NO_ERROR;
	}
	int CommonDialog::AbortNative(CommonDialogType type, int handle) {
		Logger::Debug(__FUNCTION__);

		switch (type) {
		case CommonDialogType::Reserved0:
			Logger::Error("CommonDialogType::Reserved0 Unimplemented");
			return PSM_ERROR_NOT_IMPLEMENTED;
		case CommonDialogType::TextInput:
			Logger::Error("CommonDialogType::TextInput Unimplemented");
			return PSM_ERROR_NOT_IMPLEMENTED;
		case CommonDialogType::InAppPurchaseDialog:
			Logger::Error("CommonDialogType::InAppPurchaseDialog Unimplemented");
			return PSM_ERROR_NOT_IMPLEMENTED;
		case CommonDialogType::CameraImportDialog:
			Logger::Error("CommonDialogType::CameraImportDialog Unimplemented");
			return PSM_ERROR_NOT_IMPLEMENTED;
		case CommonDialogType::PhotoImportDialog:
			Logger::Error("CommonDialogType::PhotoImportDialog Unimplemented");
			return PSM_ERROR_NOT_IMPLEMENTED;
		}

		return PSM_ERROR_NO_ERROR;
	}
	int CommonDialog::GetState(CommonDialogType type, int handle, CommonDialogState* state) {
		Logger::Debug(__FUNCTION__);

		switch (type) {
		case CommonDialogType::Reserved0:
			Logger::Error("CommonDialogType::Reserved0 Unimplemented");
			return PSM_ERROR_NOT_IMPLEMENTED;
		case CommonDialogType::TextInput:
			Logger::Error("CommonDialogType::TextInput Unimplemented");
			return PSM_ERROR_NOT_IMPLEMENTED;
		case CommonDialogType::InAppPurchaseDialog:
			Logger::Error("CommonDialogType::InAppPurchaseDialog Unimplemented");
			return PSM_ERROR_NOT_IMPLEMENTED;
		case CommonDialogType::CameraImportDialog:
			Logger::Error("CommonDialogType::CameraImportDialog Unimplemented");
			return PSM_ERROR_NOT_IMPLEMENTED;
		case CommonDialogType::PhotoImportDialog:
			Logger::Error("CommonDialogType::PhotoImportDialog Unimplemented");
			return PSM_ERROR_NOT_IMPLEMENTED;
		}

		return PSM_ERROR_NO_ERROR;
	}
	int CommonDialog::GetResult(CommonDialogType type, int handle, CommonDialogResult* result, CommonDialogResults* results) {
		Logger::Debug(__FUNCTION__);

		switch (type) {
		case CommonDialogType::Reserved0:
			Logger::Error("CommonDialogType::Reserved0 Unimplemented");
			return PSM_ERROR_NOT_IMPLEMENTED;
		case CommonDialogType::TextInput:
			Logger::Error("CommonDialogType::TextInput Unimplemented");
			return PSM_ERROR_NOT_IMPLEMENTED;
		case CommonDialogType::InAppPurchaseDialog:
			Logger::Error("CommonDialogType::InAppPurchaseDialog Unimplemented");
			return PSM_ERROR_NOT_IMPLEMENTED;
		case CommonDialogType::CameraImportDialog:
			Logger::Error("CommonDialogType::CameraImportDialog Unimplemented");
			return PSM_ERROR_NOT_IMPLEMENTED;
		case CommonDialogType::PhotoImportDialog:
			Logger::Error("CommonDialogType::PhotoImportDialog Unimplemented");
			return PSM_ERROR_NOT_IMPLEMENTED;
		}

		return PSM_ERROR_NO_ERROR;
	}
}
