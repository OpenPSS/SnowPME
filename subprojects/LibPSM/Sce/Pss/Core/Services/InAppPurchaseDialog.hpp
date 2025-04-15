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
#include <Sce/Pss/Core/Services/InAppPurchaseInventory.hpp>

#include <Sce/Pss/Core/Environment/CommonDialogArguments.hpp>
#include <Sce/Pss/Core/Environment/CommonDialogState.hpp>
#include <Sce/Pss/Core/Environment/CommonDialogResult.hpp>
#include <Sce/Pss/Core/Environment/CommonDialog.hpp>
#include <Sce/Pss/Core/PsmUniqueObject.hpp>

#define MAX_PRODUCT_COUNT (0x100)

namespace Sce::Pss::Core::Services {
	class InAppPurchaseDialog : public Environment::CommonDialog, public PsmUniqueObject<InAppPurchaseDialog> {
	private:
		InAppPurchaseInventory inventory;
		InAppPurchaseCommand command = InAppPurchaseCommand::None;
		InAppPurchaseCommand commandsRun = InAppPurchaseCommand::None;
		
		std::string getDialogConfirmString(const std::string& header, std::vector<int>& productIndicies, bool showPrice);

		int purchaseRequestThread(std::vector<int> productIndicies);
		int consumeRequestThread(std::vector<int> productIndicies);
		int productInfoRequestThread(std::vector<int> productIndicies);
		int ticketInfoRequestThread(std::vector<int> productIndicies);

		int doPurchase(std::vector<int> productIndicies);
		int doConsume(std::vector<int> productIndicies);
		int doGetTicketInfo(std::vector<int> productIndicies);
		int doGetProductInfo(std::vector<int> productIndicies);


	public:
		int Open(Environment::CommonDialogArguments* cmdArg);
		int Result(Environment::CommonDialogResult* result, Environment::CommonDialogResults* results);
	};
}
#endif
