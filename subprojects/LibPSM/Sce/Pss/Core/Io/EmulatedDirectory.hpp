#ifndef LIB_PSS_EMULATED_DIRECTORY_H
#define LIB_PSS_EMULATED_DIRECTORY_H 1
#include <Sce/Pss/Core/Io/IUnderlying.hpp>
#include <vector>
#include <string>
namespace Sce::Pss::Core::Io {

	typedef struct EmulatedDirectoryEntry {
		std::string name;
		bool readonly = false;
		bool file = false;
		uint64_t size = 0;
	} EmulatedDirectoryEntry;

	class EmulatedDirectory : public IUnderlying {
	private:
		std::string directoryName = "/";
		std::vector<EmulatedDirectoryEntry> subdirectories;
		uint64_t position = 0;

		bool opened = true;
	public:
		uint64_t Tell();
		void Close();
		uint32_t Read(void* buffer, uint32_t length);
		
		int Next(ScePssFileInformation_t* pathInfo);

		bool IsRewritable();
		bool IsDirectory();
		bool IsEncrypted();
		bool IsOpen();

		EmulatedDirectory(std::string rootDirectoryName, std::vector<EmulatedDirectoryEntry>& subDirectories);
		~EmulatedDirectory();
	};
}
#endif