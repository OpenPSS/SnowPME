#include <Sce/Pss/Core/Environment/CommonDialog.hpp>
#include <Sce/Pss/Core/Environment/CommonDialogArguments.hpp>
#include <Sce/Pss/Core/Environment/CommonDialogState.hpp>
#include <Sce/Pss/Core/Environment/CommonDialogResult.hpp>

#include <Sce/Pss/Core/Services/InAppPurchaseDialog.hpp>
#include <Sce/Pss/Core/Services/InAppPurchaseCommand.hpp>
#include <Sce/Pss/Core/Services/InAppPurchaseProductData.hpp>
#include <Sce/Pss/Core/Services/InAppPurchaseTicketType.hpp>
#include <Sce/Pss/Core/Services/InAppPurchaseCommandResults.hpp>
#include <Sce/Pss/Core/Services/InAppPurchaseCommandArguments.hpp>
#include <Sce/Pss/Core/Services/InAppPurchaseTicketInventory.hpp>

#include <Sce/Pss/Core/Metadata/AppInfo.hpp>

#include <LibShared.hpp>

#include <cstring>
#include <cstdint>

using namespace Shared;
using namespace Shared::Debug;
using namespace Sce::Pss::Core::Metadata;
using namespace Sce::Pss::Core::Environment;

namespace Sce::Pss::Core::Services {
	InAppPurchaseDialog::InAppPurchaseDialog() {
		this->SetError(this->GetProductInfo());
	}

	int InAppPurchaseDialog::GetProductInfo() {
		AppInfo* appInfo = AppInfo::GetUniqueObject();
		for (Metadata::ProductInfo product : appInfo->ProductList) {
			InAppPurchaseProductData productData = { 0 };

			std::strncpy(productData.Label, product.Label.c_str(), sizeof(InAppPurchaseProductData::Label)-1);
			std::strncpy(productData.Name, product.GetName(Config::SystemLanguage).c_str(), sizeof(productData.Name)-1);
			std::strncpy(productData.Price, "$0.00", sizeof(InAppPurchaseProductData::Price) - 1);
			productData.TicketType = (product.Type == "normal") ? InAppPurchaseTicketType::Normal : InAppPurchaseTicketType::Consumable;

			this->productList.push_back(productData);
		}

		return PSM_ERROR_NO_ERROR;
	}

	int InAppPurchaseDialog::Open(CommonDialogArguments* cmdArg) {
		Logger::Debug(__FUNCTION__);
		LOCK_GUARD();
		InAppPurchaseCommandArguments* iapArgs = (InAppPurchaseCommandArguments*)cmdArg;

		if (iapArgs->Arguments == nullptr) return PSM_ERROR_COMMON_ARGUMENT_NULL;
		
		InAppPurchaseProductData* pData = (InAppPurchaseProductData*)mono_array_addr_with_size(iapArgs->Arguments, 4, 0);
		uintptr_t pCount = mono_array_length(iapArgs->Arguments);
		
		// initalize the state of this dialog
		this->command = iapArgs->Command;
		this->state = CommonDialogState::Running;
		this->result = CommonDialogResult::OK;

		switch (iapArgs->Command) {
			case InAppPurchaseCommand::GetProductInfo:
				Logger::Debug("InAppPurchaseCommand::GetProductInfo");

				if (pCount <= MAX_PRODUCT_COUNT) {
					this->infoStatus |= (int32_t)InAppPurchaseCommand::GetProductInfo;
					InAppPurchaseTicketInventory::UpdateProductFromInventory(this->productList);
					return PSM_ERROR_NO_ERROR;
				}

				return PSM_ERROR_COMMON_ARGUMENT_OUT_OF_RANGE;
			case InAppPurchaseCommand::GetTicketInfo:
				Logger::Debug("InAppPurchaseCommand::GetTicketInfo");
				InAppPurchaseTicketInventory::UpdateProductFromInventory(this->productList);
				this->infoStatus |= (int32_t)InAppPurchaseCommand::GetTicketInfo;

				return PSM_ERROR_NOT_IMPLEMENTED;
			case InAppPurchaseCommand::Purchase:
				Logger::Debug("InAppPurchaseCommand::Purchase");
				return PSM_ERROR_NOT_IMPLEMENTED;
			case InAppPurchaseCommand::Consume:
				Logger::Debug("InAppPurchaseCommand::Consume");
				return PSM_ERROR_NOT_IMPLEMENTED;
		}

		return PSM_ERROR_NO_ERROR;
	}
}
