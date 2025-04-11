#ifndef LIB_PSS_COMMONDIALOGTYPE_H
#define LIB_PSS_COMMONDIALOGTYPE_H

namespace Sce::Pss::Core::Environment {
	enum class CommonDialogType : unsigned int {
		Reserved0 = 0x0,
		TextInput = 0x1,
		InAppPurchaseDialog = 0x101,
		CameraImportDialog = 0x201,
		PhotoImportDialog = 0x301,
	};
}

#endif