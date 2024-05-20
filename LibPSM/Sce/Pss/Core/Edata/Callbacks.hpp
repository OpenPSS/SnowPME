#ifndef LIB_PSS_EDATA_HEADER_H
#define LIB_PSS_EDATA_HEADER_H 1

namespace Sce::Pss::Core::Edata {
	class Callbacks {
	public:
		static int EdataOpen(const char* path, int flags, int mode, int* handle, int* type);
		static int EdataRead(int handle, void* buffer, int toRead, int* totalRead);
		static int EdataSeek(int handle, long offset, int whence, long* totalSeeked);
		static void EdataClose(int handle);
	};
}
#endif