#ifndef LIB_PSS_INAPPPURCHASEPRODUCT_H
#define LIB_PSS_INAPPPURCHASEPRODUCT_H
#include <string>
#include <mono/mono.h>
#include <Sce/Pss/Core/Services/InAppPurchaseTicketType.hpp>
#include <Sce/Pss/Core/Services/InAppPurchaseProductMonoData.hpp>

#define MAX_PRODUCT_COUNT (0x100)

namespace Sce::Pss::Core::Services {
	class InAppPurchaseProduct{
	public:
		std::string Label = "";
		std::string Name = "";
		std::string Price = "";
		InAppPurchaseTicketType TicketType = InAppPurchaseTicketType::Normal;
		bool HaveTicket = false;
		uint64_t IssuedDate = 0;
		uint64_t ExpireDate = 0;
		int RemainingCount = 0;
		uint32_t ConsumedCount = 0;
		InAppPurchaseProduct();
		~InAppPurchaseProduct();
		int FillInMonoData(InAppPurchaseProductMonoData* data);
	};
}

#endif