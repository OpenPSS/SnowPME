#ifndef LIB_PSM_INAPPPURCHSAECOMMAND_H
#define LIB_PSM_INAPPPURCHSAECOMMAND_H

namespace Sce::PlayStation::Core::Services {
	enum class InAppPurchaseCommand : unsigned int {
		None = 0,
		GetProductInfo = 1,
		GetTicketInfo = 2,
		Purchase = 3,
		Consume = 4
	};
}

#endif