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
#include <Threading/ProgressTracker.hpp>
#include <Crypto/Algorithms.hpp>
#include <Package/PackageFile.hpp>
#include <fstream>
#include <list>
#include <string>
#include <memory>

namespace Shared::Package {
	typedef struct PackageItem {
		PKG_ITEM_RECORD record;
		std::string filename;
		int index;
	} PackageItem;

	class PackageExtractor {
	private:
		int initError = 0;

		char workBuffer[0x8000];
		std::unique_ptr<std::fstream> stream = nullptr;
		uint64_t offset = 0;
		uint64_t size = 0;

		std::string pkgFile;
		aes128_key pkgKey = { 0 };
		PKG_FILE_HEADER pkgHeader;
		PKG_EXT_HEADER pkgExtHeader;
		PKG_METADATA pkgMetadata;
		std::list<PackageItem> pkgItems;
		int readMetadata();
		int readItems();

		int extractItem(PKG_ITEM_RECORD* record, const std::string& outfile);
		int derivePkgDecryptKey();

		bool isPkgOpened();

		int pkgOpen(const std::string& pkgFile);
		int pkgClose();
		uint64_t pkgRead(void* buffer, size_t bufferSize);
		uint64_t pkgSeek(uint64_t whence, std::ios::seekdir mode);
		int pkgDecrypt(uint64_t offset, void* buffer, size_t bufferSize);
		uint64_t pkgReadOffset(uint32_t offset, void* buffer, size_t bufferSize);


	public:
		std::string GetErrorMessage();
		static std::string GetErrorMessage(int err);

		~PackageExtractor();
		PackageExtractor(const char* pkgFile);
		PackageExtractor(const std::string& pkgFile);

		std::string ContentId();
		std::string TitleId();

		int ExtractFolder(const std::string& folderPathInPkg, const std::string& outputFolderPath, Shared::Threading::ProgressTracker* progress = nullptr);
		int ExtractFile(const std::string& filePathInPkg, const std::string& outputFilePath);
		int ExpandPackage(const std::string& outputFolder, Shared::Threading::ProgressTracker* progress = nullptr);
		int ExpandPackage(const char* outputFolder);
	};


}

#endif
