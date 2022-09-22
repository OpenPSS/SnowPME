#ifndef SNOW_PME_DIRECTORY_ITERATOR_H
#define SNOW_PME_DIRECTORY_ITERATOR_H 1
#include <vector>
#include <string>
#include <filesystem>
#include <mono/mono.h>
namespace SnowPME::IO {
	typedef struct StackItem {
		std::filesystem::directory_iterator* iterator = NULL;
		int positionInFolder = 0;

		std::string sandboxPath;
		std::string realPath;
		std::string relativePath = "";
	} StackItem;

	class DirectoryIterator {
	private:
		std::vector<StackItem*> folderStack;
		std::string startFolderSandboxPath;
		int iterPos;
		bool recursive;
	public:
		DirectoryIterator(std::string sandboxedFolder, bool recursive);
		~DirectoryIterator();
		int Next(ScePssFileInformation_t* pathInfo);
	};
}
#endif