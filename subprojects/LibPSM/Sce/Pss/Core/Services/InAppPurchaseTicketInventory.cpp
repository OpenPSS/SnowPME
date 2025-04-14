#include <Sce/Pss/Core/Io/ICall.hpp>
#include <Sce/Pss/Core/Error.hpp>
#include <Sce/Pss/Core/Services/InAppPurchaseTicketInventory.hpp>
#include <Sce/Pss/Core/Services/InAppPurchaseProduct.hpp>
#include <Sce/Pss/Core/Memory/HeapAllocator.hpp>
#include <vector>
#include <string>
#include <cstring>

#include <LibShared.hpp>

using namespace Shared::Debug;
using namespace Shared::String;
using namespace Sce::Pss::Core::Io;
using namespace Sce::Pss::Core::Memory;


namespace Sce::Pss::Core::Services {

	std::string InAppPurchaseTicketInventory::writeTicketLine(InAppPurchaseProduct data) {
		std::vector<std::string> serializer;
		char _[0x128] = { 0 };

		serializer.push_back(std::string(data.Label));
		serializer.push_back(std::to_string(data.HaveTicket));

		snprintf(_, sizeof(_)-1, "%llx", data.IssuedDate);
		serializer.push_back(StringUtil::ZFill(std::string(_), '0', 0x16));
		
		snprintf(_, sizeof(_)-1, "%llx", data.ExpireDate);
		serializer.push_back(StringUtil::ZFill(std::string(_), '0', 0x16));

		serializer.push_back(std::to_string(data.RemainingCount));
		serializer.push_back(std::to_string(data.ConsumedCount));

		return StringUtil::Join(serializer, " ")+"\n";
	}
	void InAppPurchaseTicketInventory::readTicketLine(std::vector<InAppPurchaseProduct>&list, std::string line) {
		line = StringUtil::Replace(line, "\r", "");
		char* _;

		std::vector<std::string> deserializer = StringUtil::Split(line, " ");
		if (deserializer.size() < 6) return;
		
		std::string label = deserializer.at(0);
		for (size_t i = 0; i < list.size(); i++) {
			InAppPurchaseProduct productData = list.at(i);

			// if it is the label for the entry specified here;
			// then we update the data in the list.

			if (productData.Label == label) {
				productData.HaveTicket = strtoul(deserializer.at(1).c_str(), &_, 10);
				productData.IssuedDate = strtoull(deserializer.at(2).c_str(), &_, 16);
				productData.ExpireDate = strtoull(deserializer.at(3).c_str(), &_, 16);
				productData.RemainingCount = strtoul(deserializer.at(4).c_str(), &_, 10);
				productData.ConsumedCount = strtoul(deserializer.at(5).c_str(), &_, 10);
				list[i] = productData;
				break;
			}
		}

	}

	bool InAppPurchaseTicketInventory::ticketFileExist() {
		uint64_t handle = 0;
		int err = ICall::PsmFileOpenSystem(TICKET_INVENTORY_FILE_PATH,  SCE_PSS_FILE_OPEN_FLAG_READ | SCE_PSS_FILE_OPEN_FLAG_BINARY, &handle, true);
		if (err == PSM_ERROR_NO_ERROR) ICall::PsmClose(handle);

		if (err == PSM_ERROR_NOT_FOUND) return false;
		if (err != PSM_ERROR_NO_ERROR) return false;

		return true;
	}
	void InAppPurchaseTicketInventory::saveTicketFile(std::vector<InAppPurchaseProduct> list) {
		uint64_t handle = 0;
		int err = ICall::PsmFileOpenSystem(TICKET_INVENTORY_FILE_PATH, SCE_PSS_FILE_OPEN_FLAG_WRITE | SCE_PSS_FILE_OPEN_FLAG_BINARY | SCE_PSS_FILE_OPEN_FLAG_ALWAYS_CREATE, &handle, true);

		if (err == PSM_ERROR_NO_ERROR) {
			for (InAppPurchaseProduct prod : list) {
				std::string ticketLine = writeTicketLine(prod);
				uint32_t _ = 0;

				err = ICall::PsmFileWrite(handle, (void*)(ticketLine.c_str()), strlen(ticketLine.c_str()), &_);
				if (err != PSM_ERROR_NO_ERROR) break;
			}

			ICall::PsmClose(handle);
		}

	}
	void InAppPurchaseTicketInventory::loadTicketFile(std::vector<InAppPurchaseProduct>& list) {
		uint64_t handle;
		int err = ICall::PsmFileOpenSystem(TICKET_INVENTORY_FILE_PATH, SCE_PSS_FILE_FLAG_READONLY | SCE_PSS_FILE_OPEN_FLAG_READ | SCE_PSS_FILE_OPEN_FLAG_NOTRUNCATE | SCE_PSS_FILE_OPEN_FLAG_NOREPLACE | SCE_PSS_FILE_OPEN_FLAG_BINARY, &handle, true);

		if (err == PSM_ERROR_NO_ERROR) {
			uint32_t size = 0;
			uint32_t _ = 0;
			err = ICall::PsmFileGetSize(handle, &size);
			if (err == PSM_ERROR_NO_ERROR) {
				HeapAllocator* heapAllocator = HeapAllocator::GetResourceHeapAllocator();
				uint8_t* data = heapAllocator->sce_psm_malloc(size);
				if (data != nullptr) {
					err = ICall::PsmFileRead(handle, data, size, &_);
					if (err == PSM_ERROR_NO_ERROR) {
						std::string ticketData = std::string((char*)data, size);
						std::vector<std::string> lines = StringUtil::Split(ticketData, "\n");
						for (std::string line : lines) {
							InAppPurchaseTicketInventory::readTicketLine(list, line);
						}
					}
					else {
						Logger::Error("failed to read file " + std::string(TICKET_INVENTORY_FILE_PATH));
					}
					heapAllocator->sce_psm_free(data);
				}
				else {
					Logger::Error("failed to allocate memory for " + std::string(TICKET_INVENTORY_FILE_PATH));
				}
			}
			else {
				Logger::Error("failed to get size of " + std::string(TICKET_INVENTORY_FILE_PATH));
			}

			ICall::PsmClose(handle);
		}
		else {
			Logger::Error("failed to open " + std::string(TICKET_INVENTORY_FILE_PATH));
		}
		
	}
	void InAppPurchaseTicketInventory::UpdateProductFromInventory(std::vector<InAppPurchaseProduct>& list) {
		Logger::Debug(__FUNCTION__);
		if (InAppPurchaseTicketInventory::ticketFileExist()) {
			InAppPurchaseTicketInventory::loadTicketFile(list);
		}
		InAppPurchaseTicketInventory::saveTicketFile(list);
	}
}