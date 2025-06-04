#ifndef LIB_PSS_INAPPPURCHASEPRODUCTMONODATA_H
#define LIB_PSS_INAPPPURCHASEPRODUCTMONODATA_H
#include <string>

#include <mono/mono.h>
#include <Sce/Pss/Core/Services/InAppPurchaseTicketType.hpp>

namespace Sce::Pss::Core::Services {
	typedef struct InAppPurchaseProductMonoData {
		MonoString* Label;
		MonoString* Name;
		MonoString* Price;
		int pad;
		InAppPurchaseTicketType TicketType;
		int TicketIsOK;
		uint64_t TicketIssuedDate;
		uint64_t TicketExpireDate;
		int TicketRemainingCount;
		uint32_t TicketConsumedCount;
	} InAppPurchaseProductMonoData;
}

#endif