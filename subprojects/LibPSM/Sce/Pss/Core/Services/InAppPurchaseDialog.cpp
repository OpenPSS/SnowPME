#include <Sce/Pss/Core/Environment/CommonDialog.hpp>
#include <Sce/Pss/Core/Environment/CommonDialogArguments.hpp>
#include <Sce/Pss/Core/Environment/CommonDialogState.hpp>
#include <Sce/Pss/Core/Environment/CommonDialogResult.hpp>

#include <Sce/Pss/Core/Services/InAppPurchaseDialog.hpp>
#include <Sce/Pss/Core/Services/InAppPurchaseCommand.hpp>
#include <Sce/Pss/Core/Services/InAppPurchaseProduct.hpp>
#include <Sce/Pss/Core/Services/InAppPurchaseProductMonoData.hpp>
#include <Sce/Pss/Core/Services/InAppPurchaseTicketType.hpp>
#include <Sce/Pss/Core/Services/InAppPurchaseCommandResults.hpp>
#include <Sce/Pss/Core/Services/InAppPurchaseCommandArguments.hpp>
#include <Sce/Pss/Core/Services/InAppPurchaseInventory.hpp>

#include <Sce/Pss/Core/Metadata/AppInfo.hpp>
#include <Sce/Pss/Core/Mono/MonoUtil.hpp>
#include <Sce/Pss/Core/ExceptionInfo.hpp>
#include <Sce/Pss/Core/Callback/WindowCallbacks.hpp>
#include <Sce/Pss/Core/Threading/Thread.hpp>

#include <LibShared.hpp>
#include <cstring>
#include <cstdint>
#include <thread>

using namespace Shared;
using namespace Shared::Debug;

using namespace Sce::Pss::Core::Callback;
using namespace Sce::Pss::Core::Mono;
using namespace Sce::Pss::Core::Metadata;
using namespace Sce::Pss::Core::Environment;
using namespace Sce::Pss::Core::Threading;

namespace Sce::Pss::Core::Services {

	std::string InAppPurchaseDialog::getDialogConfirmString(const std::string& header, std::vector<int>& productIndicies, bool showPrice) {
		std::string msg = header;
		for (int idx : productIndicies) {
			InAppPurchaseProduct* prod = this->inventory.GetItemByIndex(idx);
			if (prod == nullptr) continue;
			msg += "\n("+prod->Label + ")\t"+prod->Name;
			if (showPrice == true) msg += "\t (" + prod->Price + ")";
		}
		Logger::Debug(msg);
		return msg;
	}

	int InAppPurchaseDialog::purchaseRequestThread(std::vector<int> productIndicies) {
		CommonDialogResult res;

		// prompt yes or no dialog box,
		if (WindowCallbacks::YesNoDialog(getDialogConfirmString("Do you want to purchase the following item?", productIndicies, true), "Purchase Item?")) {

			InAppPurchaseProduct* prod = this->inventory.GetItemByIndex(productIndicies.front());
			if (prod == nullptr) res = CommonDialogResult::Error;

			// purchase item
			if (prod->Purchase() != PSM_ERROR_NO_ERROR) res = CommonDialogResult::Error;

			// save inventory cache.
			if (this->inventory.SyncInventoryToDisk() != PSM_ERROR_NO_ERROR) res = CommonDialogResult::Error;


			res = CommonDialogResult::OK;

		}
		else {
			res = CommonDialogResult::Canceled;
		}

		if (this->result.load() != CommonDialogResult::Aborted) {
			this->result.store(res);
		}

		this->state.store(CommonDialogState::Finished);

		return PSM_ERROR_NO_ERROR;
	}
	int InAppPurchaseDialog::consumeRequestThread(std::vector<int> productIndicies) {
		CommonDialogResult res;

		// prompt yes or no dialog box,
		if (WindowCallbacks::YesNoDialog(getDialogConfirmString("Do you want to consume the following item?", productIndicies, false), "Consume Item?")) {
			// get first argument.
			InAppPurchaseProduct* prod = this->inventory.GetItemByIndex(productIndicies.front());
			if (prod == nullptr) res = CommonDialogResult::Error;

			// consume item
			if(prod->Consume() != PSM_ERROR_NO_ERROR) res = CommonDialogResult::Error;

			// save inventory cache.
			if(this->inventory.SyncInventoryToDisk() != PSM_ERROR_NO_ERROR) res = CommonDialogResult::Error;

			res = CommonDialogResult::OK;

		}
		else {
			res = CommonDialogResult::Canceled;
		}

		if (this->result.load() != CommonDialogResult::Aborted) {
			this->result.store(res);
		}

		this->state.store(CommonDialogState::Finished);

		return PSM_ERROR_NO_ERROR;
	}
	int InAppPurchaseDialog::productInfoRequestThread(std::vector<int> productIndicies) {
		CommonDialogResult res;

		// prompt user for confirmation w yes or no dialog box,
		if (WindowCallbacks::YesNoDialog(getDialogConfirmString("Get product information for the following items?", productIndicies, false), "Get Product information?")) {
			this->commandsRun |= InAppPurchaseCommand::GetProductInfo;
			res = CommonDialogResult::OK;
		}
		else {
			res = CommonDialogResult::Canceled;
		}

		if (this->result.load() != CommonDialogResult::Aborted) {
			this->result.store(res);
		}

		this->state.store(CommonDialogState::Finished);

		return PSM_ERROR_NO_ERROR;
	}
	int InAppPurchaseDialog::ticketInfoRequestThread(std::vector<int> productIndicies) {
		CommonDialogResult res;

		// prompt user for confirmation w yes or no dialog box,
		if (WindowCallbacks::YesNoDialog(getDialogConfirmString("Get Ticket Information?", productIndicies, false), "Get ticket information?")) {
			if (this->inventory.SyncInventoryToDisk() == PSM_ERROR_NO_ERROR) {
				this->commandsRun |= InAppPurchaseCommand::GetTicketInfo;
				res = CommonDialogResult::OK;
			}
			else {
				res = CommonDialogResult::Error;
			}
		}
		else {
			res = CommonDialogResult::Canceled;
		}
		
		if (this->result.load() != CommonDialogResult::Aborted) {
			this->result.store(res);
		}

		this->state.store(CommonDialogState::Finished);

		return PSM_ERROR_NO_ERROR;
	}

	int InAppPurchaseDialog::doPurchase(std::vector<int> productIndicies) {
		
		// only ever purchase one item at a time ...
		if (productIndicies.size() != 1) return PSM_ERROR_COMMON_ARGUMENT_OUT_OF_RANGE;
		InAppPurchaseProduct* product = this->inventory.GetItemByIndex(productIndicies.front());

		// check GetProductInfo was run
		if ((this->commandsRun & InAppPurchaseCommand::GetProductInfo) == InAppPurchaseCommand::None) {
			ExceptionInfo::AddMessage("Product information is invalid or not retrieved\n");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}
		// check GetTicketInfo was run
		if ((this->commandsRun & InAppPurchaseCommand::GetTicketInfo) == InAppPurchaseCommand::None) {
			ExceptionInfo::AddMessage("Ticket information is invalid or not retrieved\n");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}

		// check product not already owned.
		if (product->TicketType == InAppPurchaseTicketType::Normal && product->HaveTicket) {
			ExceptionInfo::AddMessage("Product is already purchased\n");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}

		this->state.store(CommonDialogState::Running);
		std::thread(&InAppPurchaseDialog::purchaseRequestThread, this, productIndicies).detach(); // start purchase thread

		return PSM_ERROR_NO_ERROR;
	}
	int InAppPurchaseDialog::doConsume(std::vector<int> productIndicies) {

		// only ever consume one item at a time ...
		if (productIndicies.size() != 1) return PSM_ERROR_COMMON_ARGUMENT_OUT_OF_RANGE;
		InAppPurchaseProduct* product = this->inventory.GetItemByIndex(productIndicies.front());

		if ((this->commandsRun & InAppPurchaseCommand::GetTicketInfo) == InAppPurchaseCommand::None) {
			ExceptionInfo::AddMessage("Ticket information is invalid or not retrieved\n");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}

		if (product->TicketType != InAppPurchaseTicketType::Consumable) {
			ExceptionInfo::AddMessage("Ticket type is not consumable\n");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}

		if (product->RemainingCount <= 0) {
			ExceptionInfo::AddMessage("Ticket is already consumed or not purchased\n");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}
		
		this->state.store(CommonDialogState::Running);
		std::thread(&InAppPurchaseDialog::consumeRequestThread, this, productIndicies).detach(); // start purchase thread

		return PSM_ERROR_NO_ERROR;
	}
	int InAppPurchaseDialog::doGetTicketInfo(std::vector<int> productIndicies) {

		this->state.store(CommonDialogState::Running);
		std::thread(&InAppPurchaseDialog::ticketInfoRequestThread, this, productIndicies).detach(); // start ticket info thread

		return PSM_ERROR_NO_ERROR;
	}
	int InAppPurchaseDialog::doGetProductInfo(std::vector<int> productIndicies) {

		if (productIndicies.size() <= MAX_PRODUCT_COUNT) {
			this->state.store(CommonDialogState::Running);
			std::thread(&InAppPurchaseDialog::productInfoRequestThread, this, productIndicies).detach(); // start product info thread
			return PSM_ERROR_NO_ERROR;
		}

		return PSM_ERROR_COMMON_ARGUMENT_OUT_OF_RANGE;

	}

	int InAppPurchaseDialog::Result(CommonDialogResult* result, CommonDialogResults* results) {
		LOCK_GUARD();
		InAppPurchaseCommandResults* iapResults = (InAppPurchaseCommandResults*)results;
		if (result == nullptr) return PSM_ERROR_COMMON_ARGUMENT_NULL;

		if (this->result.load() != CommonDialogResult::OK) {
			*result = this->result.load();
			return PSM_ERROR_NO_ERROR;
		}

		if (iapResults != nullptr) {
			iapResults->Command = this->command;
			iapResults->InfoStatus = (int)this->commandsRun;
			iapResults->Count = this->inventory.GetProductCount();

			if (iapResults->Results != nullptr) {
				size_t sz = MonoUtil::MonoArrayBytesLength(iapResults->Results);
				size_t expectedSz = (iapResults->Count * sizeof(InAppPurchaseProductMonoData));

				if (sz != expectedSz) {
					return PSM_ERROR_COMMON_INVALID_OPERATION;
				}

				InAppPurchaseProductMonoData* purchaseMonoData = (InAppPurchaseProductMonoData*)mono_array_addr_with_size(iapResults->Results, sizeof(InAppPurchaseProductMonoData), 0);
				memset(purchaseMonoData, 0x00, sz);
				
				for (int i = 0; i < this->inventory.GetProductCount(); i++) {
					int err = this->inventory.GetItemByIndex(i)->ExportMonoData(&purchaseMonoData[i]);
					if (err != PSM_ERROR_NO_ERROR) return err;
				}

				return PSM_ERROR_NO_ERROR;
			}
			return PSM_ERROR_NO_ERROR;
		}
		return PSM_ERROR_COMMON_ARGUMENT_NULL;
	}
	int InAppPurchaseDialog::Open(CommonDialogArguments* cmdArg) {
		LOCK_GUARD();
		InAppPurchaseCommandArguments* iapArgs = (InAppPurchaseCommandArguments*)cmdArg;

		if (iapArgs == nullptr) return PSM_ERROR_COMMON_ARGUMENT_NULL;

		std::vector<int> argVector;

		// if arguments value is set; then read in arguments
		if (iapArgs->Arguments != nullptr) {
			int* argv = (int*)mono_array_addr_with_size(iapArgs->Arguments, 4, 0);
			size_t argc = mono_array_length(iapArgs->Arguments);

			argVector = std::vector<int>(argv, &argv[argc]);
		}

		// initalize the state of this dialog
		this->command = iapArgs->Command;
		this->result.store(CommonDialogResult::OK);

		switch (iapArgs->Command) {
			case InAppPurchaseCommand::GetProductInfo:
				Logger::Debug("iapArgs->Command = InAppPurchaseCommand::GetProductInfo");
				return this->doGetProductInfo(argVector);
			case InAppPurchaseCommand::GetTicketInfo:
				Logger::Debug("iapArgs->Command = InAppPurchaseCommand::GetTicketInfo");
				return this->doGetTicketInfo(argVector);
			case InAppPurchaseCommand::Purchase:
				Logger::Debug("iapArgs->Command = InAppPurchaseCommand::Purchase");
				return this->doPurchase(argVector);
			case InAppPurchaseCommand::Consume:
				Logger::Debug("iapArgs->Command = InAppPurchaseCommand::Consume");
				return this->doConsume(argVector);
			default:
				return PSM_ERROR_COMMON_ARGUMENT;
		}



		return PSM_ERROR_NO_ERROR;
	}
}
