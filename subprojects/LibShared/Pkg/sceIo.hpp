#ifdef __cplusplus
extern "C" {
#endif

#ifndef SCEIO_H 
#define SCEIO_H 1

#include "sceTypes.hpp"

	/* Note: Not all of these sceIoOpen() flags are not compatible with the
	   open() flags found in sys/unistd.h. */
	typedef enum SceIoMode {
		SCE_O_RDONLY = 0x0001,                         //!< Read-only
		SCE_O_WRONLY = 0x0002,                         //!< Write-only
		SCE_O_RDWR = (SCE_O_RDONLY | SCE_O_WRONLY),  //!< Read/Write
		SCE_O_NBLOCK = 0x0004,                         //!< Non blocking
		SCE_O_DIROPEN = 0x0008,                         //!< Internal use for ::sceIoDopen
		SCE_O_RDLOCK = 0x0010,                         //!< Read locked (non-shared)
		SCE_O_WRLOCK = 0x0020,                         //!< Write locked (non-shared)
		SCE_O_APPEND = 0x0100,                         //!< Append
		SCE_O_CREAT = 0x0200,                         //!< Create
		SCE_O_TRUNC = 0x0400,                         //!< Truncate
		SCE_O_EXCL = 0x0800,                         //!< Exclusive create
		SCE_O_SCAN = 0x1000,                         //!< Scan type
		SCE_O_RCOM = 0x2000,                         //!< Remote command entry
		SCE_O_NOBUF = 0x4000,                         //!< Number device buffer
		SCE_O_NOWAIT = 0x8000,                         //!< Asynchronous I/O
		SCE_O_FDEXCL = 0x01000000,                     //!< Exclusive access
		SCE_O_PWLOCK = 0x02000000,                     //!< Power control lock
		SCE_O_FGAMEDATA = 0x40000000                      //!< Gamedata access
	} SceIoMode;

	typedef enum SceIoSeekMode {
		SCE_SEEK_SET,   //!< Starts from the begin of the file
		SCE_SEEK_CUR,   //!< Starts from current position
		SCE_SEEK_END    //!< Starts from the end of the file
	} SceIoSeekMode;



	/**
	 * Reposition read/write file descriptor offset
	 *
	 * @par Example:
	 * @code
	 * pos = sceIoLseek(fd, -10, SCE_SEEK_END);
	 * @endcode
	 *
	 * @param fd - Opened file descriptor with which to seek
	 * @param offset - Relative offset from the start position given by whence
	 * @param whence - One of ::SceIoSeekMode.
	 *
	 * @return The position in the file after the seek.
	 */
	SceOff sceIoLseek(SceUID fd, SceOff offset, int whence);

	/**
	 * Open or create a file for reading or writing
	 *
	 * @par Example1: Open a file for reading
	 * @code
	 * if((fd = sceIoOpen("device:/path/to/file", SCE_O_RDONLY, 0777) < 0) {
	 * // error code in fd, for example no open filehandle left (0x80010018)
	 * }
	 * @endcode
	 * @par Example2: Open a file for writing, creating it if it doesn't exist
	 * @code
	 * if((fd = sceIoOpen("device:/path/to/file", SCE_O_WRONLY|SCE_O_CREAT, 0777) < 0) {
	 * // error code in fd, for example no open filehandle left (0x80010018)
	 * }
	 * @endcode
	 *
	 * @param file - Pointer to a string holding the name of the file to open.
	 * @param flags - Libc styled flags that are or'ed together (One or more ::SceIoMode).
	 * @param mode - One or more ::SceIoAccessMode flags or'ed together. Can also use Unix absolute permissions.
	 * @return > 0 is a valid file handle, < 0 on error.
	 */
	SceUID sceIoOpen(const char* file, int flags, SceMode mode);

	/**
	 * Delete a descriptor
	 *
	 * @code
	 * sceIoClose(fd);
	 * @endcode
	 *
	 * @param fd - File descriptor to close
	 * @return < 0 on error
	 */
	int sceIoClose(SceUID fd);

	/**
	 * Read input
	 *
	 * @par Example:
	 * @code
	 * bytes_read = sceIoRead(fd, data, 100);
	 * @endcode
	 *
	 * @param fd    - Opened file descriptor to read from
	 * @param buf   - Pointer to the buffer where the read data will be placed
	 * @param nbyte - Size of the read in bytes
	 *
	 * @return The number of bytes read
	 */
	SceSSize sceIoRead(SceUID fd, void* buf, SceSize nbyte);

	/**
	 * Write output
	 *
	 * @par Example:
	 * @code
	 * bytes_written = sceIoWrite(fd, data, 100);
	 * @endcode
	 *
	 * @param fd    - Opened file descriptor to write to
	 * @param buf   - Pointer to the data to write
	 * @param nbyte - Size of data to write
	 *
	 * @return The number of bytes written
	 */
	SceSSize sceIoWrite(SceUID fd, const void* buf, SceSize nbyte);

#endif

#ifdef __cplusplus
}
#endif