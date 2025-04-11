#ifndef LIB_PSS_INAPPPURCHASEDIALOG_H
#define LIB_PSS_INAPPPURCHASEDIALOG_H 1
#include <cstdint>

#include <string>
#include <iostream>
#include <Sce/Pss/Core/Services/InAppPurchaseCommand.hpp>
#include <Sce/Pss/Core/Services/InAppPurchaseProductData.hpp>
#include <Sce/Pss/Core/Services/CommandResults.hpp>
#include <Sce/Pss/Core/Services/CommandArguments.hpp>
#include <Sce/Pss/Core/Environment/CommonDialogState.hpp>
#include <Sce/Pss/Core/Environment/CommonDialogResult.hpp>


namespace Sce::Pss::Core::Services {
	class InAppPurchaseDialog {
	public:
		static int NewNative(int type, int *handle);
		static int ReleaseNative(int type, int handle);
		static int OpenNative(int type, int handle, CommandArguments *cmdArg);
		static int AbortNative(int type, int handle);
		static int GetState(int type, int handle, Sce::Pss::Core::Environment::CommonDialogState *state);
		static int GetResult(int type, int handle, Sce::Pss::Core::Environment::CommonDialogResult *result, CommandResults *results);
	};
}
#endif
