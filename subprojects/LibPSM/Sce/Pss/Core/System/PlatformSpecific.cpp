#include <Sce/Pss/Core/Error.hpp>
#include <Sce/Pss/Core/System/PlatformSpecific.hpp>
#include <mono/mono.h>
#include <LibShared.hpp>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>
#endif

namespace Sce::Pss::Core::System {

    int PlatformSpecific::ChangeFileAttributes(std::string RealFilePath, uint32_t attribute) {
#ifdef _WIN32
        DWORD fileAttributes = 0;

        if ((attribute & SCE_PSS_FILE_FLAG_READONLY) == 0)
            fileAttributes |= FILE_ATTRIBUTE_READONLY;

        if ((attribute & SCE_PSS_FILE_FLAG_HIDDEN) == 0)
            fileAttributes |= FILE_ATTRIBUTE_HIDDEN;

        SetFileAttributesA(RealFilePath.c_str(), fileAttributes);

        return PSM_ERROR_NO_ERROR;  
#elif __linux__
        return PSM_ERROR_NOT_AVAILABLE;
#else
#error platform not supported
#endif
    }

	int PlatformSpecific::ChangeFileTimes(std::string RealFilePath, time_t CreationTime, time_t LastAccessTime, time_t LastWriteTime) {
#ifdef _WIN32
        FILETIME creationTime; 
        FILETIME lastAccessTime;
        FILETIME lastWriteTime;

        // Set filetimes
        *(uint64_t*)&creationTime = UNIX_TO_FILETIME(CreationTime);
        *(uint64_t*)&lastAccessTime = UNIX_TO_FILETIME(LastAccessTime);
        *(uint64_t*)&lastWriteTime = UNIX_TO_FILETIME(LastWriteTime);

        // Open the file .. 
        HANDLE fd = CreateFileA(RealFilePath.c_str(), FILE_WRITE_ATTRIBUTES, NULL, NULL, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS | FILE_ATTRIBUTE_NORMAL | FILE_ATTRIBUTE_DIRECTORY, NULL);
        
        // Set the file times
        SetFileTime(fd, &creationTime, &lastAccessTime, &lastWriteTime);
        
        // Close the file
        CloseHandle(fd);
        return PSM_ERROR_NO_ERROR;
#elif __linux__
        return PSM_ERROR_NOT_AVAILABLE;
#else
#error platform not supported
#endif
	}
    std::string PlatformSpecific::escapeShellArgument(std::string arg) {
        // list of all special shell characters
        std::string specialCharacters = "^&<>|()=;,%\"";

#ifdef _WIN32
        std::string escapeSeq = "^";
#else
        std::string escapeSeq = "\\";
#endif

        // loop over all special shell characters and replace them with escaped version
        for (int i = 0; i < specialCharacters.length(); i++) {
            std::string specialCharacter = std::string(1, specialCharacters.at(i));
            arg = Shared::String::StringUtil::Replace(arg, specialCharacter, escapeSeq + specialCharacter);
        }

        return arg;
    }
    int PlatformSpecific::OpenWebsite(std::string url) {
        // add http:// or https:// to the start of the URL if its not there
        // this prevents passing i.e "calc.exe"
        if (!url.starts_with("https://") && !url.starts_with("http://")) 
            url = "http://" + url;
        
        // escape URL (turn space into %20, newline into %0D and %0A)
        url = Shared::String::StringUtil::Replace(url, " ",  "%20");
        url = Shared::String::StringUtil::Replace(url, "\r", "%0D");
        url = Shared::String::StringUtil::Replace(url, "\n", "%0A");

        // because this is passed as an argument to a shell command ..
        // we must strip unsafe values from the shell command
        url = PlatformSpecific::escapeShellArgument(url);

        // generate the command to start the browser
        // this is dependant on platform
#ifdef _WIN32
        std::string command = "start /B " + url;
#elif __APPLE__
        std::string command = "open " + url;
#elif __linux__
        std::string command = "xdg-open " + url;
#else
#error platform not supported
#endif
        
        // execute the command 
        return system(command.c_str()) != 0 ? PSM_ERROR_ERROR : PSM_ERROR_NO_ERROR;
    }
}