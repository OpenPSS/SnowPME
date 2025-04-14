#ifndef LIB_PSS_INAPPPURCHASETICKETINVENTORY_H
#define LIB_PSS_INAPPPURCHASETICKETINVENTORY_H
#include <Sce/Pss/Core/Services/InAppPurchaseProduct.hpp>
#include <Sce/Pss/Core/Services/InAppPurchaseProductMonoData.hpp>
#include <vector>

#define TICKET_INVENTORY_FILE_PATH (char*)("/System/ticket.dat")

namespace Sce::Pss::Core::Services {
	class InAppPurchaseTicketInventory {
	private:
	    static std::string writeTicketLine(InAppPurchaseProduct data);
		static void readTicketLine(std::vector<InAppPurchaseProduct>& data, std::string line);
		static bool ticketFileExist();
		static void saveTicketFile(std::vector<InAppPurchaseProduct> list);
		static void loadTicketFile(std::vector<InAppPurchaseProduct>& list);
	public:
		static void UpdateProductFromInventory(std::vector<InAppPurchaseProduct>& list);
	};
}
#endif