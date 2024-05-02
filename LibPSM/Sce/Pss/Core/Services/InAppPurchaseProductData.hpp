#ifndef LIB_PSS_INAPPPURCHASEPRODUCTDATA_H
#define LIB_PSS_INAPPPURCHASEPRODUCTDATA_H
#include <string>

namespace Sce::Pss::Core::Services {
	typedef struct InAppPurchaseProductData {
		char* Label;
		char* Name;
		char* Price;
		int pad;
		unsigned int TicketType;
		bool TicketIsOK;
		unsigned long TicketIssuedDate;
		unsigned long TicketExpireDate;
		int TicketRemainingCount;
		unsigned int TicketConsumedCount;
	} InAppPurchaseProductData;
}

#endif