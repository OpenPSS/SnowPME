#ifndef LIB_PSS_INAPPPURCHASETICKETINVENTORY_H
#define LIB_PSS_INAPPPURCHASETICKETINVENTORY_H
#include <Sce/Pss/Core/Services/InAppPurchaseProductData.hpp>
#include <vector>

#define TICKET_INVENTORY_FILE_PATH (char*)("/System/ticket.dat")

namespace Sce::Pss::Core::Services {
	class InAppPurchaseTicketInventory {
	private:
	    static std::string writeTicketLine(InAppPurchaseProductData data);
		static void readTicketLine(std::vector<InAppPurchaseProductData>& data, std::string line);
		static bool ticketFileExist();
		static void saveTicketFile(std::vector<InAppPurchaseProductData> list);
		static void loadTicketFile(std::vector<InAppPurchaseProductData>& list);
	public:
		static void UpdateProductFromInventory(std::vector<InAppPurchaseProductData>& list);
	};
}
#endif