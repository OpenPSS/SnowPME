#ifndef LIB_PSS_INAPPPURCHASEPRODUCTDATA_H
#define LIB_PSS_INAPPPURCHASEPRODUCTDATA_H
#include <string>
#include <mono/mono.h>
#include <Sce/Pss/Core/Services/InAppPurchaseTicketType.hpp>

#define MAX_PRODUCT_COUNT (0x100)

namespace Sce::Pss::Core::Services {
	typedef struct InAppPurchaseProductData{
		char Label[0x40];
		char Name[0x100];
		char Price[0x40];
		InAppPurchaseTicketType TicketType;
		bool TicketIsOK;
		unsigned long TicketIssuedDate;
		unsigned long TicketExpireDate;
		int TicketRemainingCount;
		unsigned int TicketConsumedCount;
	} InAppPurchaseProductData;
}

#endif