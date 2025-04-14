#ifndef LIB_PSS_INAPPPURCHASEDIALOG_H
#define LIB_PSS_INAPPPURCHASEDIALOG_H 1
#include <cstdint>
#include <string>
#include <iostream>

#include <Sce/Pss/Core/Services/InAppPurchaseCommand.hpp>
#include <Sce/Pss/Core/Services/InAppPurchaseProductData.hpp>
#include <Sce/Pss/Core/Services/InAppPurchaseTicketType.hpp>
#include <Sce/Pss/Core/Services/InAppPurchaseCommandResults.hpp>
#include <Sce/Pss/Core/Services/InAppPurchaseCommandArguments.hpp>

#include <Sce/Pss/Core/Environment/CommonDialogArguments.hpp>
#include <Sce/Pss/Core/Environment/CommonDialogState.hpp>
#include <Sce/Pss/Core/Environment/CommonDialogResult.hpp>
#include <Sce/Pss/Core/Environment/CommonDialog.hpp>
#include <Sce/Pss/Core/PsmUniqueObject.hpp>

#include <vector>

namespace Sce::Pss::Core::Services {
	class InAppPurchaseDialog : public Environment::CommonDialog, public PsmUniqueObject<InAppPurchaseDialog> {
	private:
		std::vector<InAppPurchaseProductData> productList;
		InAppPurchaseCommand command = InAppPurchaseCommand::None;
		int infoStatus = 0;
	public:
		InAppPurchaseDialog();
		int GetProductInfo();
		int Open(Environment::CommonDialogArguments* cmdArg);
	};
}
#endif
