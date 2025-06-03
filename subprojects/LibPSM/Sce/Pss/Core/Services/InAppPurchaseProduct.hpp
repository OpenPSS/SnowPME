#ifndef LIB_PSS_INAPPPURCHASEPRODUCT_H
#define LIB_PSS_INAPPPURCHASEPRODUCT_H
#include <string>
#define MONO_ZERO_LEN_ARRAY 1
#include <mono/mono.h>
#include <Sce/Pss/Core/Services/InAppPurchaseTicketType.hpp>
#include <Sce/Pss/Core/Services/InAppPurchaseProductMonoData.hpp>
#include <Sce/Pss/Core/Errorable.hpp>


namespace Sce::Pss::Core::Services {
	class InAppPurchaseProduct : public Errorable {
	public:
		std::string Label = "";
		std::string Name = "";
		std::string Price = "$0.00";
		InAppPurchaseTicketType TicketType = InAppPurchaseTicketType::Normal;
		bool HaveTicket = false;
		uint64_t IssuedDate = 0;
		uint64_t ExpireDate = 0;
		int RemainingCount = 0;
		uint32_t ConsumedCount = 0;

		InAppPurchaseProduct();
		InAppPurchaseProduct(InAppPurchaseProductMonoData monoProductData);

		int Purchase();
		int Consume();
		int Reset();

		int ImportMonoData(InAppPurchaseProductMonoData data);
		int ExportMonoData(InAppPurchaseProductMonoData* data);
	};
}

#endif