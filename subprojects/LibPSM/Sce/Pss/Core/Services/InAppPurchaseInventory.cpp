#include <Sce/Pss/Core/Io/IoCall.hpp>
#include <Sce/Pss/Core/Error.hpp>
#include <Sce/Pss/Core/Services/InAppPurchaseInventory.hpp>
#include <Sce/Pss/Core/Services/InAppPurchaseProduct.hpp>
#include <Sce/Pss/Core/Metadata/AppInfo.hpp>
#include <Sce/Pss/Core/Memory/HeapAllocator.hpp>
#include <Sce/Pss/Core/PsmMutexObject.hpp>
#include <vector>
#include <string>
#include <cstring>

#include <LibShared.hpp>

using namespace Shared::Debug;
using namespace Shared::String;
using namespace Shared;

using namespace Sce::Pss::Core::Metadata;
using namespace Sce::Pss::Core::Io;
using namespace Sce::Pss::Core::Memory;

#define DO_X_W_ITEM(getterFunc, memberFunc) \
LOCK_GUARD(); \
InAppPurchaseProduct* product = this->getterFunc(prodIdentifier); \
if (product != nullptr) { \
	return product->memberFunc(); \
} \
return PSM_ERROR_COMMON_ARGUMENT_NULL;

namespace Sce::Pss::Core::Services {

	// the ticket.dat file is a ASCII file with the following order:
	// SWD001 0 0000000000000000000000 0000000000000000000000 0 0\n
	// (label, haveTicket, issuedDate, expireDate, remainCount, consumedCount)
	// this code is for serializing a InAppPurchaseProduct into such format.

	std::string InAppPurchaseInventory::writeTicketLine(InAppPurchaseProduct* data) {
		std::vector<std::string> serializer;
		char _[0x128] = { 0 };

		serializer.push_back(std::string(data->Label));
		serializer.push_back(std::to_string(data->HaveTicket));

		snprintf(_, sizeof(_)-1, "%llx", data->IssuedDate);
		serializer.push_back(StringUtil::ZFill(std::string(_), '0', 16));
		
		snprintf(_, sizeof(_)-1, "%llx", data->ExpireDate);
		serializer.push_back(StringUtil::ZFill(std::string(_), '0', 16));

		serializer.push_back(std::to_string(data->RemainingCount));
		serializer.push_back(std::to_string(data->ConsumedCount));

		return StringUtil::Join(serializer, " ")+"\n";
	}
	void InAppPurchaseInventory::readTicketLine(std::string line) {
		line = StringUtil::Replace(line, "\r", "");
		char* _;

		std::vector<std::string> deserializer = StringUtil::Split(line, " ");
		if (deserializer.size() < 6) return;
		
		std::string label = deserializer.at(0);
		InAppPurchaseProduct* product = GetItemByLabel(label);

		if (product != nullptr) {
			product->HaveTicket = strtoul(deserializer.at(1).c_str(), &_, 10);
			product->IssuedDate = strtoull(deserializer.at(2).c_str(), &_, 16);
			product->ExpireDate = strtoull(deserializer.at(3).c_str(), &_, 16);
			product->RemainingCount = strtoul(deserializer.at(4).c_str(), &_, 10);
			product->ConsumedCount = strtoul(deserializer.at(5).c_str(), &_, 10);
		}

	}

	bool InAppPurchaseInventory::ticketFileExist() {

		uint64_t handle = 0;
		int err = IoCall::PsmFileOpen(TICKET_INVENTORY_FILE_PATH,  SCE_PSS_FILE_OPEN_FLAG_READ | SCE_PSS_FILE_OPEN_FLAG_BINARY, &handle, true);
		if (err == PSM_ERROR_NO_ERROR) IoCall::PsmClose(handle);

		if (err == PSM_ERROR_NOT_FOUND) return false;
		if (err != PSM_ERROR_NO_ERROR) return false;

		return true;
	}

	// saves the ASCII file "/System/ticket.dat",
	// which is the emulated inventory, (same as in PSM Dev)
	int InAppPurchaseInventory::saveTicketFile() {

		uint64_t handle = 0;
		uint32_t _ = 0;

		int err = IoCall::PsmFileOpen(TICKET_INVENTORY_FILE_PATH, SCE_PSS_FILE_OPEN_FLAG_WRITE | SCE_PSS_FILE_OPEN_FLAG_BINARY | SCE_PSS_FILE_OPEN_FLAG_ALWAYS_CREATE, &handle, true);

		if (err == PSM_ERROR_NO_ERROR) {
			for (InAppPurchaseProduct* prod : this->productList) {
				std::string line = writeTicketLine(prod);

				err = IoCall::PsmFileWrite(handle, (void*)(line.c_str()), strlen(line.c_str()), &_);
				if (err != PSM_ERROR_NO_ERROR) { 
					Logger::Error("Failed to write \"" + line + "\" to " + std::string(TICKET_INVENTORY_FILE_PATH)); 
					break; 
				}
			}

			IoCall::PsmClose(handle);
		}
		else {
			Logger::Error("Failed to open " + std::string(TICKET_INVENTORY_FILE_PATH));
		}

		return err;
	}
	int InAppPurchaseInventory::loadTicketFile() {

		uint64_t handle;
		int err = IoCall::PsmFileOpen(TICKET_INVENTORY_FILE_PATH, SCE_PSS_FILE_FLAG_READONLY | SCE_PSS_FILE_OPEN_FLAG_READ | SCE_PSS_FILE_OPEN_FLAG_NOTRUNCATE | SCE_PSS_FILE_OPEN_FLAG_NOREPLACE | SCE_PSS_FILE_OPEN_FLAG_BINARY, &handle, true);

		if (err == PSM_ERROR_NO_ERROR) {
			uint32_t size = 0;
			uint32_t _ = 0;
			err = IoCall::PsmFileGetSize(handle, &size);
			if (err == PSM_ERROR_NO_ERROR) {
				std::shared_ptr<HeapAllocator> heapAllocator = HeapAllocator::UniqueObject();
				uint8_t* data = heapAllocator->sce_psm_malloc(size);
				if (data != nullptr) {
					err = IoCall::PsmFileRead(handle, data, size, &_);
					if (err == PSM_ERROR_NO_ERROR) {
						std::string ticketData = std::string((char*)data, size);
						std::vector<std::string> lines = StringUtil::Split(ticketData, "\n");
						for (std::string line : lines) {
							InAppPurchaseInventory::readTicketLine(line);
						}
					}
					else {
						Logger::Error("failed to read file " + std::string(TICKET_INVENTORY_FILE_PATH));
					}
					heapAllocator->sce_psm_free(data);
				}
				else {
					Logger::Error("failed to allocate memory for " + std::string(TICKET_INVENTORY_FILE_PATH));
					err = PSM_ERROR_COMMON_OUT_OF_MEMORY;
				}
			}
			else {
				Logger::Error("failed to get size of " + std::string(TICKET_INVENTORY_FILE_PATH));
			}

			IoCall::PsmClose(handle);
		}
		else {
			Logger::Error("failed to open " + std::string(TICKET_INVENTORY_FILE_PATH));
		}

		

		return err;
	}

	int InAppPurchaseInventory::SyncInventoryToDisk() {
		LOCK_GUARD();

		if (!this->loadedTicketFile && this->ticketFileExist()) {
			int err = this->loadTicketFile();
			if (err == PSM_ERROR_NO_ERROR) this->loadedTicketFile = true;
		}
		return this->saveTicketFile();
	}
	InAppPurchaseProduct* InAppPurchaseInventory::GetItemByLabel(std::string label) {

		for (InAppPurchaseProduct* product : this->productList) {
			if (product->Label == label) return product;
		}
		return nullptr;
	}

	InAppPurchaseProduct* InAppPurchaseInventory::GetItemByIndex(int index) {

		if (index > this->GetProductCount()) return nullptr;
		if (index < 0) return nullptr;

		return this->productList.at(index);
	}
	
	int InAppPurchaseInventory::GetProductCount() {
		return static_cast<int>(this->productList.size());
	}


	int InAppPurchaseInventory::PurchaseItemByLabel(std::string prodIdentifier) {
		DO_X_W_ITEM(GetItemByLabel, Purchase);
	}
	int InAppPurchaseInventory::PurchaseItemById(int prodIdentifier) {
		DO_X_W_ITEM(GetItemByIndex, Purchase);
	}

	int InAppPurchaseInventory::ConsumeItemByLabel(std::string prodIdentifier) {
		DO_X_W_ITEM(GetItemByLabel, Consume);
	}
	int InAppPurchaseInventory::ConsumeItemById(int prodIdentifier) {
		DO_X_W_ITEM(GetItemByIndex, Consume);
	}


	InAppPurchaseInventory::InAppPurchaseInventory() {
		std::shared_ptr<AppInfo> appInfo = AppInfo::UniqueObject();

		for (ProductInfo metadata : appInfo->ProductList) {
			InAppPurchaseProduct* product = new InAppPurchaseProduct();

			product->Label = metadata.Label;
			product->Name = metadata.GetName(Config::SystemLanguage);

			if (metadata.Type == "normal") product->TicketType = InAppPurchaseTicketType::Normal;
			if (metadata.Type == "consumable") product->TicketType = InAppPurchaseTicketType::Consumable;

			this->productList.push_back(product);
		}

	}
	InAppPurchaseInventory::~InAppPurchaseInventory() {
		this->SyncInventoryToDisk();

		for (InAppPurchaseProduct* product : this->productList) {
			if (product != nullptr) delete product;
		}
		this->productList.clear();
	}

}