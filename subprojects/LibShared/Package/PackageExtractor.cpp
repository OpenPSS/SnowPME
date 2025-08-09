/*
* PKG extraction code based on
* Real-PackageExtractor-Installer by LiEnby.
* https://silica.codes/Li/real-PackageExtractor-installer/
*/

#include <Debug/Assert.hpp>
#include <Package/PackageExtractor.hpp>
#include <Package/PackageError.hpp>
#include <filesystem>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <cstring>


namespace Shared::Package {
	static const uint8_t PKG_DECRYPT_KEY_PS3[0x10]		= { 0x2E, 0x7B, 0x71, 0xD7, 0xC9, 0xC9, 0xA1, 0x4E, 0xA3, 0x22, 0x1F, 0x18, 0x88, 0x28, 0xb8, 0xF8 };
	static const uint8_t PKG_DECRYPT_KEY_PSP[0x10]		= { 0x07, 0xF2, 0xC6, 0x82, 0x90, 0xB5, 0x0D, 0x2C, 0x33, 0x81, 0x8D, 0x70, 0x9B, 0x60, 0xE6, 0x2B };
	static const uint8_t PKG_DECRYPT_KEY_VITA[0x10]		= { 0xE3, 0x1A, 0x70, 0xC9, 0xCE, 0x1D, 0xD7, 0x2B, 0xF3, 0xC0, 0x62, 0x29, 0x63, 0xF2, 0xEC, 0xCB };
	static const uint8_t PKG_DECRYPT_KEY_LIVEAREA[0x10] = { 0x42, 0x3A, 0xCA, 0x3A, 0x2B, 0xD5, 0x64, 0x9F, 0x96, 0x86, 0xAB, 0xAD, 0x6F, 0xD8, 0x80, 0x1F };
	static const uint8_t PKG_DECRYPT_KEY_PSM[0x10]		= { 0xAF, 0x07, 0xFD, 0x59, 0x65, 0x25, 0x27, 0xBA, 0xF1, 0x33, 0x89, 0x66, 0x8B, 0x17, 0xD9, 0xEA };


	int PackageExtractor::derivePkgDecryptKey() {

		// because we don't have sceNpDrmPackage 
		// we have to do the decryption part ourselves,
		uint8_t pkgKey[sizeof(this->pkgHeader.pkg_data_iv)];
		memcpy(pkgKey, this->pkgHeader.pkg_data_iv, sizeof(pkgKey));
		aes128_key key;

		switch (this->pkgExtHeader.data_type2 & 0x7) {
		case PKG_KEYID_PS3:
			memcpy(pkgKey, PKG_DECRYPT_KEY_PSP, sizeof(pkgKey));

			aes128_init(&key, PKG_DECRYPT_KEY_PS3);
			aes128_ecb_encrypt(&key, pkgKey, sizeof(pkgKey));
			break;
		case PKG_KEYID_VITA:
			aes128_init(&key, PKG_DECRYPT_KEY_VITA);
			aes128_ecb_encrypt(&key, pkgKey, sizeof(pkgKey));
			break;
		case PKG_KEYID_VITA_LIVEAREA:
			aes128_init(&key, PKG_DECRYPT_KEY_LIVEAREA);
			aes128_ecb_encrypt(&key, pkgKey, sizeof(pkgKey));
			break;
		case PKG_KEYID_PSM:
			aes128_init(&key, PKG_DECRYPT_KEY_PSM);
			aes128_ecb_encrypt(&key, pkgKey, sizeof(pkgKey));
			break;
		default:
			return PKG_ERROR_UNKNOWN_KEY;
		}

		return PKG_ERROR_NO_ERROR;
	}

	int PackageExtractor::readMetadata() {
		pkgSeek(this->pkgHeader.meta_offset, std::ios::beg);

		for (int i = 0; i < this->pkgHeader.meta_count; i++) {
			PKG_METADATA_ENTRY metaEntry;
			CHECK_ERROR(pkgRead(&metaEntry, sizeof(PKG_METADATA_ENTRY)));

			metaEntry.type = __builtin_bswap32(metaEntry.type);
			metaEntry.size = __builtin_bswap32(metaEntry.size);
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
			CHECK_ERROR(rd);

			pkgSeek(metaEntry.size - rd, std::ios::cur);
		}
		this->pkgMetadata.drm_type = __builtin_bswap32(this->pkgMetadata.drm_type);
		this->pkgMetadata.content_type = __builtin_bswap32(this->pkgMetadata.content_type);
		this->pkgMetadata.package_flags = __builtin_bswap32(this->pkgMetadata.package_flags);
		this->pkgMetadata.item_table_offset = __builtin_bswap32(this->pkgMetadata.item_table_offset);
		this->pkgMetadata.item_table_size = __builtin_bswap32(this->pkgMetadata.item_table_size);
		this->pkgMetadata.sfo_offset = __builtin_bswap32(this->pkgMetadata.sfo_offset);
		this->pkgMetadata.sfo_size = __builtin_bswap32(this->pkgMetadata.sfo_size);

		return PKG_ERROR_NO_ERROR;
	}

	int PackageExtractor::pkgDecrypt(uint64_t offset, void* buffer, size_t bufferSize) {
		aes128_ctr_xor(&this->pkgKey, this->pkgHeader.pkg_data_iv, offset / 16, (uint8_t*)buffer, bufferSize);

		return PKG_ERROR_NO_ERROR;
	}

	uint64_t PackageExtractor::pkgSeek(uint64_t whence, std::ios::openmode mode) {
		this->stream.seekg(whence, mode);

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
		uint64_t amtRead = this->stream.read(reinterpret_cast<char*>(buffer), bufferSize).gcount();
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

			item.record.flags = __builtin_bswap32(item.record.flags);
			item.record.filename_offset = __builtin_bswap32(item.record.filename_offset);
			item.record.filename_size = __builtin_bswap32(item.record.filename_size);
			item.record.data_offset = __builtin_bswap64(item.record.data_offset);
			item.record.data_size = __builtin_bswap64(item.record.data_size);

			std::vector<char> buffer = std::vector<char>(item.record.filename_size + 1);
			CHECK_ERROR(this->pkgReadOffset((item.record.data_offset + item.record.filename_offset), buffer.data(), item.record.filename_size));

			item.filename = std::string(buffer.data());
			item.index = index;

			this->pkgItems.push_back(item);

			return PKG_ERROR_NO_ERROR;
		}
	}

	int PackageExtractor::pkgClose() {
		this->stream.close();

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

	int PackageExtractor::pkgOpen(const char* pkg_file) {
		this->size = std::filesystem::file_size(pkg_file);
		this->stream.open(pkg_file, std::ios::in | std::ios::binary);

		if (this->stream.fail()) return PKG_ERROR_OPEN_FAILED;
		if(this->stream.read(reinterpret_cast<char*>(&this->pkgHeader), sizeof(PKG_FILE_HEADER)).gcount() != sizeof(PKG_FILE_HEADER)) return PKG_ERROR_READ_SIZE_NO_MATCH;

		if (strncmp(this->pkgHeader.magic, "\x7f\PKG", sizeof(this->pkgHeader.magic)) != 0) return PKG_ERROR_INVALID_MAGIC;
		this->pkgHeader.revision = __builtin_bswap16(this->pkgHeader.revision);
		this->pkgHeader.type = __builtin_bswap16(this->pkgHeader.type);
		this->pkgHeader.meta_offset = __builtin_bswap32(this->pkgHeader.meta_offset);
		this->pkgHeader.meta_count = __builtin_bswap32(this->pkgHeader.meta_count);
		this->pkgHeader.meta_size = __builtin_bswap32(this->pkgHeader.meta_size);
		this->pkgHeader.item_count = __builtin_bswap32(this->pkgHeader.item_count);
		this->pkgHeader.total_size = __builtin_bswap64(this->pkgHeader.total_size);
		this->pkgHeader.data_offset = __builtin_bswap64(this->pkgHeader.data_offset);
		this->pkgHeader.data_size = __builtin_bswap64(this->pkgHeader.data_size);

		if (this->pkgHeader.type >= 2) {
			if (this->stream.read(reinterpret_cast<char*>(&this->pkgExtHeader), sizeof(PKG_EXT_HEADER)).gcount() != sizeof(PKG_EXT_HEADER)) return PKG_ERROR_READ_SIZE_NO_MATCH;

			if (strncmp(this->pkgExtHeader.magic, "\x7f\ext", sizeof(this->pkgExtHeader.magic)) != 0) return PKG_ERROR_INVALID_EXT_MAGIC;
			this->pkgExtHeader.unknown_01 = __builtin_bswap32(this->pkgExtHeader.unknown_01);
			this->pkgExtHeader.header_size = __builtin_bswap32(this->pkgExtHeader.header_size);
			this->pkgExtHeader.data_size = __builtin_bswap32(this->pkgExtHeader.data_size);
			this->pkgExtHeader.data_offset = __builtin_bswap32(this->pkgExtHeader.data_offset);
			this->pkgExtHeader.data_type = __builtin_bswap32(this->pkgExtHeader.data_type);
			this->pkgExtHeader.pkg_data_size = __builtin_bswap64(this->pkgExtHeader.pkg_data_size);
			this->pkgExtHeader.padding_01 = __builtin_bswap32(this->pkgExtHeader.padding_01);
			this->pkgExtHeader.data_type2 = __builtin_bswap32(this->pkgExtHeader.data_type2);
			this->pkgExtHeader.unknown_02 = __builtin_bswap32(this->pkgExtHeader.unknown_02);
			this->pkgExtHeader.padding_02 = __builtin_bswap32(this->pkgExtHeader.padding_02);
			this->pkgExtHeader.padding_03 = __builtin_bswap64(this->pkgExtHeader.padding_03);
			this->pkgExtHeader.padding_04 = __builtin_bswap64(this->pkgExtHeader.padding_04);
		}
		else {
			return PKG_ERROR_INVALID_PACKAGE_TYPE;
		}

		CHECK_ERROR(readMetadata());
		CHECK_ERROR(derivePkgDecryptKey());
		if (!IS_PSM_CONTENT_TYPE(this->pkgMetadata.content_type))
			return PKG_ERROR_INVALID_CONTENT_TYPE;

		return PKG_ERROR_NO_ERROR;
	}

	int PackageExtractor::extractItem(PKG_ITEM_RECORD* record, const char* outfile) {
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
			if (amtRead != readSize) ERROR(PKG_ERROR_READ_SIZE_NO_MATCH);

			// write decrypted data
			wfd.write(this->workBuffer, amtRead);
			int amtWritten = amtRead;

			totalRead += amtWritten;

		} while (totalRead < record->data_size);

	error:
		wfd.close();
		return ret;
	}


	int PackageExtractor::ExpandPackage(const char* pkg_file, const char* output_folder, void (*progress_callback)(const char*, uint64_t, uint64_t)) {
		if (progress_callback != nullptr) progress_callback(pkg_file, static_cast<uint64_t>(0), static_cast<uint64_t>(100));

		std::filesystem::create_directories(output_folder);
		CHECK_ERROR(this->pkgOpen(pkg_file));

		for (PackageItem item : this->pkgItems) {
			if (progress_callback != nullptr) progress_callback(pkg_file, (uint64_t)item.index, (uint64_t)this->pkgHeader.item_count);

			// create directory that this file/directory is located within;
			std::string outfile = std::filesystem::path(output_folder).append(item.filename).string();
			std::filesystem::create_directories(std::filesystem::path(outfile).parent_path().string());

			switch (item.record.flags & 0x1F) {
			case PKG_TYPE_FILE:
			case PKG_TYPE_SELF:
			case PKG_TYPE_PFS_KEYSTONE:
			case PKG_TYPE_PFS_FILE:
			case PKG_TYPE_PFS_TEMP_BIN:
			case PKG_TYPE_PFS_CLEARSIGN:
			case PKG_TYPE_SCESYS_RIGHT_SUPRX:
			default:
				CHECK_ERROR(this->extractItem(&item.record, outfile.c_str()));
				break;
			case PKG_TYPE_DIR:
			case PKG_TYPE_PFS_DIR:
				std::filesystem::create_directories(outfile);
				break;
			case PKG_TYPE_SCESYS_CERT_BIN:
			case PKG_TYPE_SCESYS_DIGS_BIN:
				// ignore these ..
				break;
			}
		}

		this->pkgClose();
		return PKG_ERROR_NO_ERROR;
	}

}
