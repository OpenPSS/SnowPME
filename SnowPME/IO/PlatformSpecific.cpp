#include <IO/PlatformSpecific.hpp>
#include <LibPSM.hpp>
#include <Runtime/AppGlobals.hpp>

#ifdef _WIN32
#include <windows.h>
#endif

namespace SnowPME::IO {
#ifdef _WIN32
    void UnixTimeToFileTime(time_t t, LPFILETIME pft)
    {
        LONGLONG ll;

        ll = Int32x32To64(t, FILETIME_TICK) + UNIX_EPOCH;
        pft->dwLowDateTime = (DWORD)ll;
        pft->dwHighDateTime = ll >> 32;
    }
#endif
	int PlatformSpecific::ChangeFileTimes(std::string RealFilePath, time_t CreationTime, time_t LastAccessTime, time_t LastWriteTime) {
#ifdef _WIN32
        FILETIME creationTime;
        FILETIME lastAccessTime;
        FILETIME lastWriteTime;

        // Convert times to FILETIME
        UnixTimeToFileTime(CreationTime, &creationTime);
        UnixTimeToFileTime(LastAccessTime, &lastAccessTime);
        UnixTimeToFileTime(LastWriteTime, &lastWriteTime);

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