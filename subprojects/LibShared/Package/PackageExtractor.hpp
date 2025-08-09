/*
* PKG extraction code based on
* Real-PackageExtractor-Installer by LiEnby.
* https://silica.codes/Li/real-PackageExtractor-installer/
*/


#ifndef SHARED_PACKAGE_EXTRACTOR_H 
#define SHARED_PACKAGE_EXTRACTOR_H 1

#include <cstdint>
#include <cstdio>
#include <cstring>
#include <Crypto/Algorithms.hpp>
#include <Package/PackageFile.hpp>
#include <fstream>
#include <list>

namespace Shared::Package {
	typedef struct PackageItem {
		PKG_ITEM_RECORD record;
		std::string filename;
		int index;
	} PackageItem;

	class PackageExtractor {
	private:
		char workBuffer[0x8000];
		std::fstream stream;
		uint64_t offset = 0;
		uint64_t size = 0;
		aes128_key pkgKey = { 0 };
		PKG_FILE_HEADER pkgHeader;
		PKG_EXT_HEADER pkgExtHeader;
		PKG_METADATA pkgMetadata;
		std::list<PackageItem> pkgItems;
		int readMetadata();
		int readItems();

		int extractItem(PKG_ITEM_RECORD* record, const char* outfile);
		int derivePkgDecryptKey();

		int pkgOpen(const char* pkgFile);
		int pkgClose();
		uint64_t pkgRead(void* buffer, size_t bufferSize);
		uint64_t pkgSeek(uint64_t whence, std::ios::openmode mode);
		int pkgDecrypt(uint64_t offset, void* buffer, size_t bufferSize);
		uint64_t pkgReadOffset(uint32_t offset, void* buffer, size_t bufferSize);
		
	public:
		int ExpandPackage(const char* pkgFile, const char* outputFolder, void (*progressCallback)(const char*, uint64_t, uint64_t));
	};


}

#endif
