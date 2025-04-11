#ifndef LIB_PSS_INAPPPURCHASETICKETYPE_H
#define LIB_PSS_INAPPPURCHASETICKETYPE_H
namespace Sce::Pss::Core::Services {

	enum class InAppPurchaseTicketType : unsigned int {
		Normal = 0,
		Consumable = 1
	};

}
#endif