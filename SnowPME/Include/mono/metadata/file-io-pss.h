/*
 * file-io-pss.h: File IO internal calls
 *
 * Authors:
 *  Geoff Norton (geoff_norton@playstation.sony.com)
 *
 * (C) 2012 SCEA, LLC
 */

#ifndef _MONO_METADATA_FILEIO_PSS_H_
#define _MONO_METADATA_FILEIO_PSS_H_
MONO_BEGIN_DECLS

typedef struct ScePssFileInformation
{
	// PSS Platform max file path is 160 chars + terminating null character
	char szName[161];
	uint64_t uFileSize;
	uint64_t tCreationTime;
	uint64_t tLastAccessTime;
	uint64_t tLastWriteTime;
	uint32_t uFlags;
} ScePssFileInformation_t;

typedef enum ScePssFileSeekType
{
	SCE_PSS_FILE_SEEK_TYPE_BEGIN = 0,
	SCE_PSS_FILE_SEEK_TYPE_END = 1,
	SCE_PSS_FILE_SEEK_TYPE_CURRENT = 2
} ScePssFileSeekType_t;

typedef enum ScePssFileOpenFlag
{
	SCE_PSS_FILE_OPEN_FLAG_READ				= 0x00000001,
	SCE_PSS_FILE_OPEN_FLAG_WRITE			= 0x00000002,
	SCE_PSS_FILE_OPEN_FLAG_TEXT				= 0x00000004,
	SCE_PSS_FILE_OPEN_FLAG_BINARY			= 0x00000008,
	SCE_PSS_FILE_OPEN_FLAG_NOTRUNCATE		= 0x00000010,
	SCE_PSS_FILE_OPEN_FLAG_NOREPLACE		= 0x00000020,
	SCE_PSS_FILE_OPEN_FLAG_ALWAYS_CREATE	= 0x00000040,
	SCE_PSS_FILE_OPEN_FLAG_APPEND			= 0x00000080
} ScePssFileOpenFlag_t;

typedef enum ScePssFileFlag
{
	SCE_PSS_FILE_FLAG_READONLY = 1,
	SCE_PSS_FILE_FLAG_DIRECTORY = 2,
	SCE_PSS_FILE_FLAG_HIDDEN = 4,
	SCE_PSS_FILE_FLAG_ENCRYPTED = 8,
	SCE_PSS_FILE_FLAG_COMPRESSED = 16
} ScePssFileFlag_t;

typedef int (*scePssHandleCloseFunc)(uint64_t handle);

typedef int (*scePssDirectoryCreateFunc)(char *pszDirectoryPath);
typedef int (*scePssDirectoryRemoveFunc)(char *pszDirectoryPath);
typedef int (*scePssDirectoryOpenFunc)(const char *pszDirectoryPath, const char *pszFileExtension, uint64_t *pDirectory);
typedef int (*scePssDirectoryReadFunc)(uint64_t directory, ScePssFileInformation_t *pFileInfo);
typedef int (*scePssDirectoryGetWorkingDirectoryFunc)(char *pszDirectoryPath, uint32_t uBufferSize);
typedef int (*scePssDirectorySetWorkingDirectoryFunc)(char *pszDirectoryPath);

typedef int (*scePssFileOpenFunc)(char *pszFileName, uint32_t uOpenFlags, uint64_t *phFile);
typedef int (*scePssFileDeleteFunc)(char *pszFileName);
typedef int (*scePssFileGetInformationFunc)(uint64_t file, ScePssFileInformation_t *pFileInfo);
typedef int (*scePssFileReadFunc)(uint64_t file, void *buffer, uint32_t uBytesToRead, uint32_t *puBytesRead);
typedef int (*scePssFileWriteFunc)(uint64_t file, void *buffer, uint32_t uBytesToWrite, uint32_t *puBytesWritten);
typedef int (*scePssFileSeekFunc)(uint64_t file, int32_t nOffset, ScePssFileSeekType_t seekType);
typedef int (*scePssFileFlushFunc)(uint64_t file);
typedef int (*scePssFileGetSizeFunc)(uint64_t file, uint32_t *puSize);
typedef int (*scePssFileTruncateFunc)(uint64_t file, uint32_t uSize);
typedef int (*scePssFileCopyFunc)(const char* pszOldName, const char* pszNewName, int32_t bMove);
typedef int (*scePssFileSetAttributesFunc)(const char* pszFileName, uint32_t uFlags);
typedef int (*scePssFileSetTimeFunc)(const char* pszFileName, const uint64_t* pCreationTime, const uint64_t* pLastAccessTime, const uint64_t* pLastWriteTime);
typedef int (*scePssFileGetPathInformationFunc)(const char* pszFileName, ScePssFileInformation_t* pFileInfo);


void
pss_io_icall_install_functions (scePssHandleCloseFunc handle_close,
								scePssDirectoryCreateFunc directory_create,
								scePssDirectoryRemoveFunc directory_remove,
								scePssDirectoryOpenFunc directory_open,
								scePssDirectoryReadFunc diretory_read,
								scePssDirectoryGetWorkingDirectoryFunc directory_getcwd,
								scePssDirectorySetWorkingDirectoryFunc directory_setcwd,
								scePssFileOpenFunc file_open,
								scePssFileDeleteFunc file_delete,
								scePssFileGetInformationFunc file_getinfo,
								scePssFileReadFunc file_read,
								scePssFileWriteFunc file_write,
								scePssFileSeekFunc file_seek,
								scePssFileFlushFunc file_flush,
								scePssFileGetSizeFunc file_getsize,
								scePssFileTruncateFunc file_truncate,
								scePssFileCopyFunc file_copy,
								scePssFileSetAttributesFunc file_setattr,
								scePssFileSetTimeFunc file_settime,
								scePssFileGetPathInformationFunc file_getpathinfo);

MONO_END_DECLS
#endif /* _MONO_METADATA_FILEIO_PSS_H_ */
