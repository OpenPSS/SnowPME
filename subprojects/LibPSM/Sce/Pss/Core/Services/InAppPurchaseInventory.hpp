#ifndef LIB_PSS_INAPPPURCHASEINVENTORY_H
#define LIB_PSS_INAPPPURCHASEINVENTORY_H
#include <Sce/Pss/Core/Services/InAppPurchaseProduct.hpp>
#include <Sce/Pss/Core/Services/InAppPurchaseProductMonoData.hpp>
#include <Sce/Pss/Core/PsmMutexObject.hpp>
#include <vector>
#include <string>
#include <cstdint>

#define TICKET_INVENTORY_FILE_PATH (char*)("/System/ticket.dat")

namespace Sce::Pss::Core::Services {
	class InAppPurchaseInventory : public PsmMutexObject<InAppPurchaseInventory> {
	private:
		std::vector<InAppPurchaseProduct*> productList;
		bool loadedTicketFile = false;

	    std::string writeTicketLine(InAppPurchaseProduct* data);
		void readTicketLine(std::string line);
		bool ticketFileExist();
		int saveTicketFile();
		int loadTicketFile();
	public:
		InAppPurchaseProduct* GetItemByLabel(std::string label);
		InAppPurchaseProduct* GetItemByIndex(int index);
		size_t GetProductCount();

		int PurchaseItemByLabel(std::string label);
		int PurchaseItemById(int index);

		int ConsumeItemByLabel(std::string label);
		int ConsumeItemById(int index);

		int SyncInventoryToDisk();

		InAppPurchaseInventory();
		~InAppPurchaseInventory();
	};
}
#endif