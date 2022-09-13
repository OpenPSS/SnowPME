#ifndef LIB_PSM_INAPPPURCHASEPRODUCTDATA_H
#define LIB_PSM_INAPPPURCHASEPRODUCTDATA_H
#include <string>
using namespace std;

namespace Sce::PlayStation::Core::Services {
	typedef struct InAppPurchaseProductData {
		string Label;
		string Name;
		string Price;
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