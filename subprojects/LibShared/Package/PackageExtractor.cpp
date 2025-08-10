/*
* PKG extraction code based on
* Real-PackageExtractor-Installer by LiEnby.
* https://silica.codes/Li/real-PackageExtractor-installer/
*/

#include <Debug/Logger.hpp>
#include <Debug/Assert.hpp>
#include <String/Path.hpp>
#include <String/Format.hpp>
#include <Package/PackageExtractor.hpp>
#include <Package/PackageError.hpp>
#include <CompilerCompat.hpp>
#include <filesystem>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <cstring>

using namespace Shared::String;
using namespace Shared::Debug;
using namespace Shared::String;
using namespace Shared::Threading;

namespace Shared::Package {
	static const uint8_t PKG_DECRYPT_KEY_PS3[0x10]		= { 0x2E, 0x7B, 0x71, 0xD7, 0xC9, 0xC9, 0xA1, 0x4E, 0xA3, 0x22, 0x1F, 0x18, 0x88, 0x28, 0xb8, 0xF8 };
	static const uint8_t PKG_DECRYPT_KEY_PSP[0x10]		= { 0x07, 0xF2, 0xC6, 0x82, 0x90, 0xB5, 0x0D, 0x2C, 0x33, 0x81, 0x8D, 0x70, 0x9B, 0x60, 0xE6, 0x2B };
	static const uint8_t PKG_DECRYPT_KEY_VITA[0x10]		= { 0xE3, 0x1A, 0x70, 0xC9, 0xCE, 0x1D, 0xD7, 0x2B, 0xF3, 0xC0, 0x62, 0x29, 0x63, 0xF2, 0xEC, 0xCB };
	static const uint8_t PKG_DECRYPT_KEY_LIVEAREA[0x10] = { 0x42, 0x3A, 0xCA, 0x3A, 0x2B, 0xD5, 0x64, 0x9F, 0x96, 0x86, 0xAB, 0xAD, 0x6F, 0xD8, 0x80, 0x1F };
	static const uint8_t PKG_DECRYPT_KEY_PSM[0x10]		= { 0xAF, 0x07, 0xFD, 0x59, 0x65, 0x25, 0x27, 0xBA, 0xF1, 0x33, 0x89, 0x66, 0x8B, 0x17, 0xD9, 0xEA };


	#define PKG_ERROR(x) { ret = x; Logger::Error("[PkgErr] ERROR = " + Format::Hex(x)); goto error; }

	#define PKG_CHECK_ERROR(x) \
	do { \
		int ret = (int)(x);\
		if(ret < 0) { \
			Logger::Error("[PkgErr] CHECK_ERROR = " + Format::Hex(x)); \
			return ret; \
		} \
	} while(0);

	std::string PackageExtractor::GetErrorMessage() {
		return GetErrorMessage(this->initError);
	}

	std::string PackageExtractor::GetErrorMessage(int err) {
		switch(err) {
		case PKG_ERROR_NO_ERROR:
			return "";
		case PKG_ERROR_INVALID_CONTENT_TYPE:
			return "Package appears to be a PS3, PSP or Vita package, not a PlayStation Mobile package.";
		case PKG_ERROR_UNKNOWN_KEY:
			return "Package could not be decrypted.";
		case PKG_ERROR_INVALID_MAGIC:
			return "Package has an invalid Header.";
		case PKG_ERROR_INVALID_EXT_MAGIC:
			return "Package has an invalid Extended Header";
		case PKG_ERROR_OPEN_FAILED:
			return "The file could not be opened for reading.";
		case PKG_ERROR_READ_SIZE_NO_MATCH:
			return "The size of the Pacakge File is not what was expected.";
		case PKG_ERROR_FILE_NOT_FOUND:
			return "The file could not be found within the Package File.";
		default:
			return "Faiiled to extract package: " + Format::Hex(err);
		}
	}

	PackageExtractor::PackageExtractor(const std::string& pkgFile) {
		this->pkgFile = pkgFile;
		this->initError = this->pkgOpen(pkgFile);
	}

	PackageExtractor::PackageExtractor(const char* pkgFile) {
		this->pkgFile = std::string(pkgFile);
		this->initError = this->pkgOpen(this->pkgFile);
	}

	PackageExtractor::~PackageExtractor() {
		this->pkgClose();
	}


	bool PackageExtractor::isPkgOpened() {
		if (this->stream == nullptr) return false;
		if (!this->stream->is_open()) return false;
		return true;
	}

	int PackageExtractor::derivePkgDecryptKey() {
		// because we don't have sceNpDrmPackage 
		// we have to do the decryption part ourselves,
		uint8_t pkgDecryptKey[sizeof(this->pkgHeader.pkg_data_iv)];
		memcpy(pkgDecryptKey, this->pkgHeader.pkg_data_iv, sizeof(pkgDecryptKey));
		aes128_key key;

		Logger::Debug("[PkgDebug] Deriving PKG Decryption Key");

		switch (this->pkgExtHeader.data_type2 & 0x7) {
		case PKG_KEYID_PS3:
			Logger::Debug("[PkgDebug] PKG_KEYID_PS3");
			memcpy(pkgDecryptKey, PKG_DECRYPT_KEY_PSP, sizeof(pkgDecryptKey));

			aes128_init(&key, PKG_DECRYPT_KEY_PS3);
			aes128_ecb_encrypt(&key, pkgDecryptKey, sizeof(pkgDecryptKey));
			break;
		case PKG_KEYID_VITA:
			Logger::Debug("[PkgDebug] PKG_KEYID_VITA");

			aes128_init(&key, PKG_DECRYPT_KEY_VITA);
			aes128_ecb_encrypt(&key, pkgDecryptKey, sizeof(pkgDecryptKey));
			break;
		case PKG_KEYID_VITA_LIVEAREA:
			Logger::Debug("[PkgDebug] PKG_KEYID_VITA_LIVEAREA");

			aes128_init(&key, PKG_DECRYPT_KEY_LIVEAREA);
			aes128_ecb_encrypt(&key, pkgDecryptKey, sizeof(pkgDecryptKey));
			break;
		case PKG_KEYID_PSM:
			Logger::Debug("[PkgDebug] PKG_KEYID_PSM");

			aes128_init(&key, PKG_DECRYPT_KEY_PSM);
			aes128_ecb_encrypt(&key, pkgDecryptKey, sizeof(pkgDecryptKey));
			break;
		default:
			Logger::Error("[PkgErr] Unknown Decryption Key");
			return PKG_ERROR_UNKNOWN_KEY;
		}

		aes128_init(&this->pkgKey, pkgDecryptKey);
		return PKG_ERROR_NO_ERROR;
	}

	int PackageExtractor::readMetadata() {
		pkgSeek(this->pkgHeader.meta_offset, std::ios::beg);

		for (int i = 0; i < this->pkgHeader.meta_count; i++) {
			PKG_METADATA_ENTRY metaEntry;
			PKG_CHECK_ERROR(pkgRead(&metaEntry, sizeof(PKG_METADATA_ENTRY)));

			metaEntry.type = swap32(metaEntry.type);
			metaEntry.size = swap32(metaEntry.size);
			int rd = 0;

			switch (metaEntry.type) {
			case PKG_META_DRM_TYPE:
				rd += pkgRead(&this->pkgMetadata.drm_type, sizeof(uint32_t));
				break;
			case PKG_META_CONTENT_TYPE:
				rd += pkgRead(&this->pkgMetadata.content_type, sizeof(uint32_t));
				break;
			case PKG_META_PACKAGE_FLAGS:
				rd += pkgRead(&this->pkgMetadata.package_flags, sizeof(uint32_t));
				break;
			case PKG_META_FILE_ITEM_INFO:
				rd += pkgRead(&this->pkgMetadata.item_table_offset, sizeof(uint32_t));
				rd += pkgRead(&this->pkgMetadata.item_table_size, sizeof(uint32_t));
				break;
			case PKG_META_SFO:
				rd += pkgRead(&this->pkgMetadata.sfo_offset, sizeof(uint32_t));
				rd += pkgRead(&this->pkgMetadata.sfo_size, sizeof(uint32_t));
				break;
			default:
				break;
			}
			PKG_CHECK_ERROR(rd);

			pkgSeek(metaEntry.size - rd, std::ios::cur);
		}
		this->pkgMetadata.drm_type = swap32(this->pkgMetadata.drm_type);
		this->pkgMetadata.content_type = swap32(this->pkgMetadata.content_type);
		this->pkgMetadata.package_flags = swap32(this->pkgMetadata.package_flags);
		this->pkgMetadata.item_table_offset = swap32(this->pkgMetadata.item_table_offset);
		this->pkgMetadata.item_table_size = swap32(this->pkgMetadata.item_table_size);
		this->pkgMetadata.sfo_offset = swap32(this->pkgMetadata.sfo_offset);
		this->pkgMetadata.sfo_size = swap32(this->pkgMetadata.sfo_size);

		return PKG_ERROR_NO_ERROR;
	}

	int PackageExtractor::pkgDecrypt(uint64_t offset, void* buffer, size_t bufferSize) {
		aes128_ctr_xor(&this->pkgKey, this->pkgHeader.pkg_data_iv, offset / 16, (uint8_t*)buffer, bufferSize);

		return PKG_ERROR_NO_ERROR;
	}

	uint64_t PackageExtractor::pkgSeek(uint64_t whence, std::ios::seekdir mode) {
		ASSERT(this->stream != nullptr);
		this->stream->seekg(whence, mode);

		switch (mode) {
		case std::ios::beg:
			this->offset = whence;
			break;
		case std::ios::cur:
			this->offset += whence;
			break;
		case std::ios::end:
			this->offset = (this->size - whence);
			break;
		}

		return this->offset;
	}

	uint64_t PackageExtractor::pkgRead(void* buffer, size_t bufferSize) {
		ASSERT(this->stream != nullptr);

		uint64_t amtRead = this->stream->read(reinterpret_cast<char*>(buffer), bufferSize).gcount();
		if (amtRead != bufferSize) return PKG_ERROR_READ_SIZE_NO_MATCH;

		if (this->offset >= this->pkgHeader.data_offset) {
			uint64_t relOffset = (this->offset - this->pkgHeader.data_offset);
			pkgDecrypt(relOffset, buffer, bufferSize);
		}

		this->offset += amtRead;
		return amtRead;
	}

	uint64_t PackageExtractor::pkgReadOffset(uint32_t offset, void* buffer, size_t bufferSize) {
		pkgSeek(offset, std::ios::beg);
		return pkgRead(buffer, bufferSize);
	}

	int PackageExtractor::readItems() {
		for (int index = 0; index < this->pkgHeader.item_count; index++)
		{
			// read item record entry
			PackageItem item;

			this->pkgReadOffset(((this->pkgHeader.data_offset + this->pkgMetadata.item_table_offset) + (index * sizeof(PKG_ITEM_RECORD))), &item.record, sizeof(PKG_ITEM_RECORD));

			item.record.flags = swap32(item.record.flags);
			item.record.filename_offset = swap32(item.record.filename_offset);
			item.record.filename_size = swap32(item.record.filename_size);
			item.record.data_offset = swap64(item.record.data_offset);
			item.record.data_size = swap64(item.record.data_size);

			std::vector<char> buffer = std::vector<char>(item.record.filename_size + 1);
			PKG_CHECK_ERROR(this->pkgReadOffset((this->pkgHeader.data_offset + item.record.filename_offset), buffer.data(), item.record.filename_size));

			item.filename = std::string(buffer.data());
			item.index = index;

			this->pkgItems.emplace_back(std::move(item));

		}
		return PKG_ERROR_NO_ERROR;

	}

	int PackageExtractor::pkgClose() {
		
		if(this->stream != nullptr) this->stream->close();
		this->stream = nullptr;

		// clear current pkg variables
		this->offset = 0;
		this->size = 0;
		this->pkgItems.clear();

		memset(&this->pkgHeader, 0, sizeof(PKG_FILE_HEADER));
		memset(&this->pkgExtHeader, 0, sizeof(PKG_EXT_HEADER));
		memset(&this->pkgMetadata, 0, sizeof(PKG_METADATA));
		memset(&this->pkgKey, 0, sizeof(aes128_key));
		memset(this->workBuffer, 0, sizeof(this->workBuffer));
		
		return 0;
	}

	int PackageExtractor::pkgOpen(const std::string& pkgFile) {
		this->size = std::filesystem::file_size(pkgFile);

		errno = 0;
		this->stream = std::make_unique<std::fstream>(pkgFile, std::ios::in | std::ios::binary);

		if (this->stream->fail() || !this->stream->is_open()) { 
			Logger::Error("[PkgErr] Could not open file: " + pkgFile + " (" + std::to_string(errno) + ") " + strerror(errno));
			return PKG_ERROR_OPEN_FAILED; 
		}
		if (this->stream->read(reinterpret_cast<char*>(&this->pkgHeader), sizeof(PKG_FILE_HEADER)).gcount() != sizeof(PKG_FILE_HEADER)) {
			Logger::Error("[PkgErr] Size is wrong."); 
			return PKG_ERROR_READ_SIZE_NO_MATCH;
		}

		if (strncmp(this->pkgHeader.magic, "\x7f""PKG", sizeof(this->pkgHeader.magic)) != 0)  {
			Logger::Error("[PkgErr] Invalid Header Magic.");
			return PKG_ERROR_INVALID_MAGIC;
		}
		
		this->pkgHeader.revision = swap16(this->pkgHeader.revision);
		this->pkgHeader.type = swap16(this->pkgHeader.type);
		this->pkgHeader.meta_offset = swap32(this->pkgHeader.meta_offset);
		this->pkgHeader.meta_count = swap32(this->pkgHeader.meta_count);
		this->pkgHeader.meta_size = swap32(this->pkgHeader.meta_size);
		this->pkgHeader.item_count = swap32(this->pkgHeader.item_count);
		this->pkgHeader.total_size = swap64(this->pkgHeader.total_size);
		this->pkgHeader.data_offset = swap64(this->pkgHeader.data_offset);
		this->pkgHeader.data_size = swap64(this->pkgHeader.data_size);

		if (this->pkgHeader.type >= 2) {
			if (this->stream->read(reinterpret_cast<char*>(&this->pkgExtHeader), sizeof(PKG_EXT_HEADER)).gcount() != sizeof(PKG_EXT_HEADER)) {
				Logger::Error("[PkgErr] Size is wrong.");
				return PKG_ERROR_READ_SIZE_NO_MATCH;
			}

			if (strncmp(this->pkgExtHeader.magic, "\x7f""ext", sizeof(this->pkgExtHeader.magic)) != 0) return PKG_ERROR_INVALID_EXT_MAGIC;
			this->pkgExtHeader.unknown_01 = swap32(this->pkgExtHeader.unknown_01);
			this->pkgExtHeader.header_size = swap32(this->pkgExtHeader.header_size);
			this->pkgExtHeader.data_size = swap32(this->pkgExtHeader.data_size);
			this->pkgExtHeader.data_offset = swap32(this->pkgExtHeader.data_offset);
			this->pkgExtHeader.data_type = swap32(this->pkgExtHeader.data_type);
			this->pkgExtHeader.pkg_data_size = swap64(this->pkgExtHeader.pkg_data_size);
			this->pkgExtHeader.padding_01 = swap32(this->pkgExtHeader.padding_01);
			this->pkgExtHeader.data_type2 = swap32(this->pkgExtHeader.data_type2);
			this->pkgExtHeader.unknown_02 = swap32(this->pkgExtHeader.unknown_02);
			this->pkgExtHeader.padding_02 = swap32(this->pkgExtHeader.padding_02);
			this->pkgExtHeader.padding_03 = swap64(this->pkgExtHeader.padding_03);
			this->pkgExtHeader.padding_04 = swap64(this->pkgExtHeader.padding_04);
		}
		else {
			Logger::Error("[PkgErr] Invalid Package Type.");
			return PKG_ERROR_INVALID_PACKAGE_TYPE;
		}

		PKG_CHECK_ERROR(derivePkgDecryptKey());
		PKG_CHECK_ERROR(readMetadata());
		PKG_CHECK_ERROR(readItems());
		if (!IS_PSM_CONTENT_TYPE(this->pkgMetadata.content_type)) {
			Logger::Error("[PkgErr] Valid package, but not PSM content type, is (" + Format::Hex(this->pkgMetadata.content_type) + ")");
			return PKG_ERROR_INVALID_CONTENT_TYPE;
		}

		return PKG_ERROR_NO_ERROR;
	}

	int PackageExtractor::extractItem(PKG_ITEM_RECORD* record, const std::string& outfile) {
		this->pkgSeek(this->pkgHeader.data_offset + record->data_offset, std::ios::beg);
		std::fstream wfd(outfile, std::ios::out | std::ios::binary);
		if (wfd.fail()) return PKG_ERROR_OPEN_FAILED;

		int ret = 0;
		int totalRead = 0;

		do {
			// get amount of data to read
			int readSize = (sizeof(this->workBuffer) < (record->data_size - totalRead)) ? sizeof(this->workBuffer) : (record->data_size - totalRead);

			// read the data
			int amtRead = this->pkgRead(this->workBuffer, readSize);
			if (amtRead != readSize) PKG_ERROR(PKG_ERROR_READ_SIZE_NO_MATCH);

			// write decrypted data
			wfd.write(this->workBuffer, amtRead);
			int amtWritten = amtRead;

			totalRead += amtWritten;

		} while (totalRead < record->data_size);

	error:
		wfd.close();
		return ret;
	}

	std::string PackageExtractor::ContentId() {
		if (this->isPkgOpened()) {
			return std::string(this->pkgHeader.content_id);
		}
		return "";
	}

	std::string PackageExtractor::TitleId() {
		std::string contentId = this->ContentId();
		if (contentId.length() >= 16) {
			return contentId.substr(7, 9);
		}
		return "";
	}


	int PackageExtractor::ExtractFolder(const std::string& folderPathInPkg, const std::string& outputFolderPath, ProgressTracker* progress) {
		if (this->initError != PKG_ERROR_NO_ERROR) return this->initError;
		if (!this->isPkgOpened()) return PKG_ERROR_OPEN_FAILED;
		if(progress != nullptr) progress->Reset(this->pkgHeader.item_count);
		if(progress != nullptr) progress->SetShowProgress(true);

		for (PackageItem item : this->pkgItems) {
			if(progress != nullptr) progress->Increment();
			int type = item.record.flags & 0x1F;
			if (type == PKG_TYPE_DIR || type == PKG_TYPE_PFS_DIR) continue;

			if (Format::ToLower(Path::ChangeSlashesToPsmStyle(item.filename)).starts_with(Format::ToLower(Path::ChangeSlashesToPsmStyle(folderPathInPkg)))) {
				std::string nameStripped = item.filename.substr(folderPathInPkg.length());
				if (!nameStripped.empty() && (Path::ChangeSlashesToPsmStyle(nameStripped)[0] == '/')) nameStripped = nameStripped.substr(1);
				std::string outputFile = Path::ChangeSlashesToNativeStyle(std::filesystem::path(outputFolderPath).append(nameStripped).string());
				std::filesystem::create_directories(std::filesystem::path(outputFile).parent_path());

				Logger::Debug("[PkgDebug] Extracting: " + item.filename + " -> " + outputFile);
				PKG_CHECK_ERROR(this->extractItem(&item.record, outputFile));
			}

		}

		return PKG_ERROR_NO_ERROR;
	}


	int PackageExtractor::ExtractFile(const std::string& filePathInPkg, const std::string& outputFilePath) {
		if (this->initError != PKG_ERROR_NO_ERROR) return this->initError;
		if (!this->isPkgOpened()) return PKG_ERROR_OPEN_FAILED;

		std::filesystem::create_directories(std::filesystem::path(outputFilePath).parent_path().string());

		for (PackageItem item : this->pkgItems) {
			int type = item.record.flags & 0x1F;
			if (type == PKG_TYPE_DIR || type == PKG_TYPE_PFS_DIR) continue;

			if (Format::ToLower(Path::ChangeSlashesToPsmStyle(item.filename)) == Format::ToLower(Path::ChangeSlashesToPsmStyle(filePathInPkg))) {
				
				Logger::Debug("[PkgDebug] Extracting: " + item.filename + " -> " + outputFilePath);

				PKG_CHECK_ERROR(this->extractItem(&item.record, outputFilePath));
				return PKG_ERROR_NO_ERROR;
			}
		}
		return PKG_ERROR_FILE_NOT_FOUND;
	}

	int PackageExtractor::ExpandPackage(const std::string& outputFolderPath, ProgressTracker* progress) {
		if (this->initError != PKG_ERROR_NO_ERROR) return this->initError;
		if (!this->isPkgOpened()) return PKG_ERROR_OPEN_FAILED;
		if(progress != nullptr) progress->Reset(this->pkgHeader.item_count);
		if(progress != nullptr) progress->SetShowProgress(true);

		std::filesystem::create_directories(outputFolderPath);

		for (PackageItem item : this->pkgItems) {
			if (progress != nullptr) progress->Increment();

			// create directory that this file/directory is located within;
			std::string outfile = std::filesystem::path(outputFolderPath).append(item.filename).string();
			std::filesystem::create_directories(std::filesystem::path(outfile).parent_path().string());

			switch (item.record.flags & 0x1F) {
			case PKG_TYPE_FILE:
			case PKG_TYPE_SELF:
			case PKG_TYPE_PFS_KEYSTONE:
			case PKG_TYPE_PFS_FILE:
			case PKG_TYPE_PFS_TEMP_BIN:
			case PKG_TYPE_PFS_CLEARSIGN:
			case PKG_TYPE_SCESYS_RIGHT_SUPRX:
			case PKG_TYPE_SCESYS_CERT_BIN:
			case PKG_TYPE_SCESYS_DIGS_BIN:
			default:
				Logger::Debug("[PkgDebug] extracting file: " + item.filename + " -> " + outfile);
				PKG_CHECK_ERROR(this->extractItem(&item.record, outfile));
				break;
			case PKG_TYPE_DIR:
			case PKG_TYPE_PFS_DIR:
				Logger::Debug("[PkgDebug] creating directory: " + item.filename + " -> " + outfile);
				std::filesystem::create_directories(outfile);
				break;
			}
		}

		return PKG_ERROR_NO_ERROR;
	}

	int PackageExtractor::ExpandPackage(const char* outputFolder) {
		return this->ExpandPackage(std::string(outputFolder));
	}
}
