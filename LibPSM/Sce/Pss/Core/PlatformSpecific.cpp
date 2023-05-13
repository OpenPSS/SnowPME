#include <Sce/PlayStation/Core/Error.hpp>
#include <Sce/Pss/Core/PlatformSpecific.hpp>
#include <mono/mono.h>

#ifdef _WIN32
#include <windows.h>
#endif

namespace Sce::Pss::Core {
    uint64_t PlatformSpecific::CurrentThreadId() {
#ifdef _WIN32
        return (uint64_t)GetCurrentThreadId();
#else
        reeturn PSM_ERROR_NOT_SUPPORTED;
#endif
    }

    int PlatformSpecific::ChangeFileAttributes(std::string RealFilePath, uint32_t attribute) {
#ifdef _WIN32
        DWORD fileAttributes = 0;

        if ((attribute & SCE_PSS_FILE_FLAG_READONLY) == 0)
            fileAttributes |= FILE_ATTRIBUTE_READONLY;

        if ((attribute & SCE_PSS_FILE_FLAG_HIDDEN) == 0)
            fileAttributes |= FILE_ATTRIBUTE_HIDDEN;

        SetFileAttributesA(RealFilePath.c_str(), fileAttributes);

        return PSM_ERROR_NO_ERROR;
#else
        return PSM_ERROR_NOT_SUPPORTED;
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
#else
		return PSM_ERROR_NOT_SUPPORTED;
#endif
	}
}