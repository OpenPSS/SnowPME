#include <Sce/Pss/Core/Io/PsmFileHandle.hpp>
#include <Sce/Pss/Core/Io/Edata/EdataStream.hpp>

using namespace Sce::Pss::Core::Io::Edata;

namespace Sce::Pss::Core::Io {

	void PsmFileHandle::signalClosed() {
		if (this->underlying != nullptr) this->underlying->Close();
	}

	bool PsmFileHandle::IsOpen() {
		if (this->underlying != nullptr) return this->underlying->IsOpen();
		return false;
	}
	
	bool PsmFileHandle::IsDirectory() {
		if (this->underlying != nullptr) return this->underlying->IsDirectory();
		return false;
	}

	bool PsmFileHandle::IsEncrypted() {
		if (this->underlying != nullptr) return this->underlying->IsEncrypted();
		return false;
	}

	bool PsmFileHandle::IsRewritable() {
		return (((flags & SCE_PSS_FILE_OPEN_FLAG_WRITE) != 0) || ((flags & SCE_PSS_FILE_OPEN_FLAG_ALWAYS_CREATE) != 0) || ((flags & SCE_PSS_FILE_OPEN_FLAG_APPEND) != 0));
	}

	ScePssFileOpenFlag_t PsmFileHandle::PssFlags() {
		return this->flags;
	}

	std::ios_base::openmode PsmFileHandle::OpenMode() {

		std::fstream::ios_base::openmode openmode = static_cast<std::ios::openmode>(0);

		if ((flags & SCE_PSS_FILE_OPEN_FLAG_READ) != 0) {
			openmode |= std::ios::in;
		}

		if ((flags & SCE_PSS_FILE_OPEN_FLAG_WRITE) != 0) {
			openmode |= std::ios::out;
			openmode |= std::ios::trunc;
		}

		if ((flags & SCE_PSS_FILE_OPEN_FLAG_BINARY) != 0) {
			openmode |= std::ios::binary;
		}

		if ((flags & SCE_PSS_FILE_OPEN_FLAG_TEXT) != 0) {
			openmode |= std::ios::binary; // need to open as binary anyway in the case of decrypted files, 
			// on VITA & ANDROID binary and text open are the same anyway.
		}

		if ((flags & SCE_PSS_FILE_OPEN_FLAG_APPEND) != 0) {
			openmode |= std::ios::ate;
		}

		if ((flags & SCE_PSS_FILE_OPEN_FLAG_NOTRUNCATE) != 0) {
			openmode &= ~std::ios::trunc;
		}

		return openmode;
	}

	std::string PsmFileHandle::PathInSandbox() {
		return this->pathInSandbox;
	}
	std::string PsmFileHandle::PathOnDisk() {
		return this->pathOnDisk;
	}

	PsmFileHandle::PsmFileHandle(std::string pathInSandbox, std::string pathOnDisk, ScePssFileOpenFlag_t flags) {
		this->pathInSandbox = pathInSandbox;
		this->pathOnDisk = pathOnDisk;
		this->flags = flags;
	}
	
	PsmFileHandle::PsmFileHandle(std::string pathInSandbox, std::string pathOnDisk, ScePssFileOpenFlag_t flags, IUnderlying* underlying) {
		this->pathInSandbox = pathInSandbox;
		this->pathOnDisk = pathOnDisk;
		this->flags = flags;
		this->underlying = underlying;
	}
	
	IUnderlying* PsmFileHandle::GetUnderlying() {
		return this->underlying;
	}

	int PsmFileHandle::SetUnderyling(IUnderlying* underlying) {
		PASS_ERRORABLE(underlying);
		this->underlying = underlying;
		return PSM_ERROR_NO_ERROR;
	}

	PsmFileHandle::~PsmFileHandle() {
		this->signalClosed();

		if (this->underlying != nullptr) {
			delete this->underlying;
			this->underlying = nullptr;
		}
	}
}
