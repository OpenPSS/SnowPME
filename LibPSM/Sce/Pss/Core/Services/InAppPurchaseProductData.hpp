#ifndef LIB_PSS_INAPPPURCHASEPRODUCTDATA_H
#define LIB_PSS_INAPPPURCHASEPRODUCTDATA_H
#include <string>
#include <mono/mono.h>

#include <Sce/Pss/Core/Services/InAppPurchaseTicketType.hpp>

namespace Sce::Pss::Core::Services {
	typedef struct InAppPurchaseProductData {
		MonoString* Label;
		MonoString* Name;
		MonoString* Price;
		int pad;
		InAppPurchaseTicketType TicketType;
		bool TicketIsOK;
		unsigned long TicketIssuedDate;
		unsigned long TicketExpireDate;
		int TicketRemainingCount;
		unsigned int TicketConsumedCount;
	} InAppPurchaseProductData;
}

#endif