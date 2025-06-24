#ifndef LIB_PSS_STACKITEM_H
#define LIB_PSS_STACKITEM_H 1
#include <string>
#include <filesystem>
#include <memory>

namespace Sce::Pss::Core::Io {
	typedef struct StackItem {
		std::filesystem::directory_iterator iterator;
		int positionInFolder = 0;

		std::string pathInSandbox = "";
		std::string pathOnDisk = "";
		std::string relativePath = "";
	} StackItem;
}

#endif