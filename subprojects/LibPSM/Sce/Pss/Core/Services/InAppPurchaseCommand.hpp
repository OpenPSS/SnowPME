#ifndef LIB_PSS_INAPPPURCHSAECOMMAND_H
#define LIB_PSS_INAPPPURCHSAECOMMAND_H

namespace Sce::Pss::Core::Services {
	enum class InAppPurchaseCommand : unsigned int {
		None = 0,
		GetProductInfo = 1,
		GetTicketInfo = 2,
		Purchase = 3,
		Consume = 4
	};
}

#endif