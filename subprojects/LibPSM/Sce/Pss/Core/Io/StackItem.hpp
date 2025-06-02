#ifndef LIB_PSS_STACKITEM_H
#define LIB_PSS_STACKITEM_H 1
#include <string>
#include <filesystem>

namespace Sce::Pss::Core::Io {
	typedef struct StackItem {
		std::filesystem::directory_iterator* iterator = nullptr;
		int positionInFolder = 0;

		std::string pathInSandbox;
		std::string pathOnDisk;
		std::string relativePath = "";
	} StackItem;
}

#endif