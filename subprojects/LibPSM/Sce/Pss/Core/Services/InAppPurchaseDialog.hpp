#ifndef LIB_PSS_INAPPPURCHASEDIALOG_H
#define LIB_PSS_INAPPPURCHASEDIALOG_H 1
#include <cstdint>
#include <string>
#include <iostream>
#include <vector>

#include <Sce/Pss/Core/Services/InAppPurchaseCommand.hpp>
#include <Sce/Pss/Core/Services/InAppPurchaseProduct.hpp>
#include <Sce/Pss/Core/Services/InAppPurchaseProductMonoData.hpp>
#include <Sce/Pss/Core/Services/InAppPurchaseTicketType.hpp>
#include <Sce/Pss/Core/Services/InAppPurchaseCommandResults.hpp>
#include <Sce/Pss/Core/Services/InAppPurchaseCommandArguments.hpp>

#include <Sce/Pss/Core/Environment/CommonDialogArguments.hpp>
#include <Sce/Pss/Core/Environment/CommonDialogState.hpp>
#include <Sce/Pss/Core/Environment/CommonDialogResult.hpp>
#include <Sce/Pss/Core/Environment/CommonDialog.hpp>
#include <Sce/Pss/Core/PsmUniqueObject.hpp>



namespace Sce::Pss::Core::Services {
	class InAppPurchaseDialog : public Environment::CommonDialog, public PsmUniqueObject<InAppPurchaseDialog> {
	private:
		std::vector<InAppPurchaseProduct> productList;
		InAppPurchaseCommand command = InAppPurchaseCommand::None;
		int infoStatus = 0;
	public:
		InAppPurchaseDialog();
		int GetProductInfo();
		int Open(Environment::CommonDialogArguments* cmdArg);
		int Result(Environment::CommonDialogResult* result, Environment::CommonDialogResults* results);
	};
}
#endif
