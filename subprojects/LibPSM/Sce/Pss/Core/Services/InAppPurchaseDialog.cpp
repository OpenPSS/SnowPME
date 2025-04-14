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
#include <Sce/Pss/Core/Services/InAppPurchaseTicketInventory.hpp>

#include <Sce/Pss/Core/Metadata/AppInfo.hpp>
#include <Sce/Pss/Core/Mono/MonoUtil.hpp>

#include <LibShared.hpp>

#include <cstring>
#include <cstdint>

using namespace Shared;
using namespace Shared::Debug;

using namespace Sce::Pss::Core::Mono;
using namespace Sce::Pss::Core::Metadata;
using namespace Sce::Pss::Core::Environment;


namespace Sce::Pss::Core::Services {
	InAppPurchaseDialog::InAppPurchaseDialog() {
		this->SetError(this->GetProductInfo());
	}

	int InAppPurchaseDialog::GetProductInfo() {
		AppInfo* appInfo = AppInfo::GetUniqueObject();
		for (ProductInfo productMetadata : appInfo->ProductList) {
			InAppPurchaseProduct productData;

			productData.Label = productMetadata.Label;
			productData.Name = productMetadata.GetName(Config::SystemLanguage);
			productData.Price = "$0.00";
			productData.TicketType = (productMetadata.Type == "normal") ? InAppPurchaseTicketType::Normal : InAppPurchaseTicketType::Consumable;

			this->productList.push_back(productData);
		}

		return PSM_ERROR_NO_ERROR;
	}

	int InAppPurchaseDialog::Result(CommonDialogResult* result, CommonDialogResults* results) {
		Logger::Debug(__FUNCTION__);
		LOCK_GUARD();
		InAppPurchaseCommandResults* iapResults = (InAppPurchaseCommandResults*)results;
		if (result == nullptr) return PSM_ERROR_COMMON_ARGUMENT_NULL;

		if (this->result != CommonDialogResult::OK) {
			*result = this->result;
			return PSM_ERROR_NO_ERROR;
		}

		switch (iapResults->Command) {
			case InAppPurchaseCommand::GetProductInfo:
				if (this->result == CommonDialogResult::OK) {
					this->GetProductInfo();
				}
			case InAppPurchaseCommand::GetTicketInfo:
				if (this->result == CommonDialogResult::OK) {
					InAppPurchaseTicketInventory::UpdateProductFromInventory(this->productList);
				}
				break;
			case InAppPurchaseCommand::Purchase:
			case InAppPurchaseCommand::Consume:
				if (this->result != CommonDialogResult::Canceled) {
					// TODO: figure out what this part is for
				}
				break;
		}


		if (iapResults != nullptr) {
			iapResults->Command = this->command;
			iapResults->InfoStatus = this->infoStatus;
			iapResults->Count = this->productList.size();
			if (iapResults->Results != nullptr) {
				size_t sz = MonoUtil::MonoArrayLength(iapResults->Results);
				size_t expectedSz = (iapResults->Count * sizeof(InAppPurchaseProductMonoData));

				if (sz != expectedSz) {
					return PSM_ERROR_COMMON_INVALID_OPERATION;
				}
				InAppPurchaseProductMonoData* purchaseMonoData = (InAppPurchaseProductMonoData*)mono_array_addr_with_size(iapResults->Results, sizeof(InAppPurchaseProductMonoData), 0);
				memset(purchaseMonoData, 0x00, sz);
				
				for (int i = 0; i < iapResults->Count; i++) {
					int res = this->productList.at(i).FillInMonoData(&purchaseMonoData[i]);
					if (res != PSM_ERROR_NO_ERROR) return res;
				}

				return PSM_ERROR_NO_ERROR;
			}
			return PSM_ERROR_NO_ERROR;
		}
		return PSM_ERROR_COMMON_ARGUMENT_NULL;
	}

	int InAppPurchaseDialog::Open(CommonDialogArguments* cmdArg) {
		Logger::Debug(__FUNCTION__);
		LOCK_GUARD();
		InAppPurchaseCommandArguments* iapArgs = (InAppPurchaseCommandArguments*)cmdArg;

		if (iapArgs->Arguments == nullptr) return PSM_ERROR_COMMON_ARGUMENT_NULL;
		
		InAppPurchaseProduct* pData = (InAppPurchaseProduct*)mono_array_addr_with_size(iapArgs->Arguments, 4, 0);
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
					return PSM_ERROR_NO_ERROR;
				}

				return PSM_ERROR_COMMON_ARGUMENT_OUT_OF_RANGE;
			case InAppPurchaseCommand::GetTicketInfo:
				Logger::Debug("InAppPurchaseCommand::GetTicketInfo");
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
