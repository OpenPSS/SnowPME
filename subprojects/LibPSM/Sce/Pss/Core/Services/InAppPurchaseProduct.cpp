#include <Sce/Pss/Core/Services/InAppPurchaseCommand.hpp>
#include <Sce/Pss/Core/Services/InAppPurchaseProduct.hpp>
#include <Sce/Pss/Core/Mono/MonoUtil.hpp>
#include <Sce/Pss/Core/Error.hpp>
#include <mono/mono.h>

using namespace Sce::Pss::Core::Mono;

namespace Sce::Pss::Core::Services {
	InAppPurchaseProduct::InAppPurchaseProduct() {
		
	}
	InAppPurchaseProduct::~InAppPurchaseProduct() {

	}

	int InAppPurchaseProduct::FillInMonoData(InAppPurchaseProductMonoData* data) {
		memset(data, 0x00, sizeof(InAppPurchaseProductMonoData));
		
		data->Label = MonoUtil::StdStringToMonoString(this->Label);
		if (data->Label == nullptr) return PSM_ERROR_COMMON_OUT_OF_MEMORY;

		data->Name = MonoUtil::StdStringToMonoString(this->Name);
		if (data->Name == nullptr) return PSM_ERROR_COMMON_OUT_OF_MEMORY;

		data->Price = MonoUtil::StdStringToMonoString(this->Price);
		if (data->Price == nullptr) return PSM_ERROR_COMMON_OUT_OF_MEMORY;

		data->TicketType = this->TicketType;
		data->TicketIsOK = (int)this->HaveTicket;
		data->TicketIssuedDate = this->IssuedDate;
		data->TicketExpireDate = this->ExpireDate;
		data->TicketRemainingCount = this->RemainingCount;
		data->TicketConsumedCount = this->ConsumedCount;

		return PSM_ERROR_NO_ERROR;
	}
}