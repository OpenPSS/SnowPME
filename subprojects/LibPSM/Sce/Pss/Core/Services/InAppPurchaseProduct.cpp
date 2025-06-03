#include <Sce/Pss/Core/Services/InAppPurchaseCommand.hpp>
#include <Sce/Pss/Core/Services/InAppPurchaseProduct.hpp>
#include <Sce/Pss/Core/Mono/MonoUtil.hpp>
#include <Sce/Pss/Core/Error.hpp>
#include <Sce/Pss/Core/Timing/Time.hpp>
#include <cstring>

#include <LibShared.hpp>
#define MONO_ZERO_LEN_ARRAY 1
#include <mono/mono.h>

using namespace Shared;
using namespace Shared::Debug;
using namespace Sce::Pss::Core::Timing;
using namespace Sce::Pss::Core::Mono;

namespace Sce::Pss::Core::Services {

	InAppPurchaseProduct::InAppPurchaseProduct() {
	}

	InAppPurchaseProduct::InAppPurchaseProduct(InAppPurchaseProductMonoData monoProductData) {
		this->SetError(this->ImportMonoData(monoProductData));
	}

	int InAppPurchaseProduct::Purchase() {
		switch (this->TicketType) {
		case InAppPurchaseTicketType::Normal:
			if (!this->HaveTicket) {
				this->ExpireDate = 0x0000000000000000ull;
	
				if (Config::TargetImplementation == RuntimeImplementation::Windows)
					this->IssuedDate = 0x0000000000000000ull;
				else 
					this->IssuedDate = Time::scePssTimeGetMicroTickCount();
				
				this->HaveTicket = true;
				return PSM_ERROR_NO_ERROR;
			}
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		case InAppPurchaseTicketType::Consumable:
			this->RemainingCount++;
			return PSM_ERROR_NO_ERROR;
		default:
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}
	}
	int InAppPurchaseProduct::Consume() {
		if (this->TicketType == InAppPurchaseTicketType::Consumable) {
			this->RemainingCount--;
			this->ConsumedCount++;
			return PSM_ERROR_NO_ERROR;
		}

		return PSM_ERROR_COMMON_INVALID_OPERATION;
	}
	int InAppPurchaseProduct::Reset() {
		this->IssuedDate = 0;
		this->ExpireDate = 0;

		this->ConsumedCount = 0;
		this->RemainingCount = 0;

		this->HaveTicket = false;

		return PSM_ERROR_NO_ERROR;
	}

	int InAppPurchaseProduct::ImportMonoData(InAppPurchaseProductMonoData data) {
		int res = MonoUtil::MonoStringToStdString(data.Label, this->Label);
		if (res != PSM_ERROR_NO_ERROR) return res;

		res = MonoUtil::MonoStringToStdString(data.Name, this->Name);
		if (res != PSM_ERROR_NO_ERROR) return res;

		res = MonoUtil::MonoStringToStdString(data.Price, this->Price);
		if (res != PSM_ERROR_NO_ERROR) return res;
		
		this->TicketType = data.TicketType;
		this->HaveTicket = (data.TicketIsOK == 0x1);
		this->IssuedDate = data.TicketIssuedDate;
		this->ExpireDate = data.TicketExpireDate;
		this->RemainingCount = data.TicketRemainingCount;
		this->ConsumedCount = data.TicketConsumedCount;

		return PSM_ERROR_NO_ERROR;
	}

	int InAppPurchaseProduct::ExportMonoData(InAppPurchaseProductMonoData* data) {
		memset(data, 0x00, sizeof(InAppPurchaseProductMonoData));
		
		data->Label = MonoUtil::StdStringToMonoString(this->Label);
		if (data->Label == nullptr) return PSM_ERROR_COMMON_OUT_OF_MEMORY;

		data->Name = MonoUtil::StdStringToMonoString(this->Name);
		if (data->Name == nullptr) return PSM_ERROR_COMMON_OUT_OF_MEMORY;

		data->Price = MonoUtil::StdStringToMonoString(this->Price);
		if (data->Price == nullptr) return PSM_ERROR_COMMON_OUT_OF_MEMORY;

		data->TicketType = this->TicketType;
		data->TicketIsOK = this->HaveTicket ? 0x1 : 0x0;
		data->TicketIssuedDate = this->IssuedDate;
		data->TicketExpireDate = this->ExpireDate;
		data->TicketRemainingCount = this->RemainingCount;
		data->TicketConsumedCount = this->ConsumedCount;

		return PSM_ERROR_NO_ERROR;
	}
}