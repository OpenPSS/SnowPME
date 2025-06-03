#ifndef LIB_PSS_DIRECTORY_ITERATOR_H
#define LIB_PSS_DIRECTORY_ITERATOR_H 1
#include <vector>
#include <string>
#include <filesystem>
#define MONO_ZERO_LEN_ARRAY 1
#include <mono/mono.h>
#include <Sce/Pss/Core/Io/StackItem.hpp>
#include <Sce/Pss/Core/Io/IUnderlying.hpp>

namespace Sce::Pss::Core::Io {

	class DirectoryIterator : public IUnderlying {
	private:
		std::vector<StackItem> folderStack;
		std::string startFolderSandboxPath = "";
		uint64_t iterPos = 0;
		bool recursive = false;
		bool opened = true;
	public:
		DirectoryIterator(std::string sandboxedFolder, bool recursive);
		~DirectoryIterator();
		uint32_t Read(void* buffer, uint32_t length);
		int Next(ScePssFileInformation_t* pathInfo);
		uint64_t Tell();
		bool IsOpen();
		bool IsDirectory();
		bool IsEncrypted();
		void Close();
	};
}
#endif