#include "sceIo.hpp"
#include <filesystem>
#include <fstream>

SceUID sceIoOpen(const char* file, int flags, SceMode mode) {
	std::fstream::ios_base::openmode openMode = static_cast<std::ios::openmode>(0);

	openMode |= std::ios::binary;

	if ((flags & SCE_O_TRUNC) != 0) {
		openMode |= std::ios::trunc;
	}

	if ((flags & SCE_O_WRONLY) != 0) {
		openMode |= std::ios::out;
	}

	if ((flags & SCE_O_RDONLY) != 0) {
		openMode |= std::ios::in;
	}

	std::fstream* stream = new std::fstream(file, openMode);

	if (stream->fail()) {
		delete stream;
		return -1;
	}
	
	return reinterpret_cast<SceUID>(stream);
}
int sceIoClose(SceUID fd) {
	delete reinterpret_cast<std::fstream*>(fd);
	return 0;
}
SceSSize sceIoRead(SceUID fd, void* buf, SceSize nbyte) {
	return reinterpret_cast<std::fstream*>(fd)->read(reinterpret_cast<char*>(buf), nbyte).gcount();
}
SceSSize sceIoWrite(SceUID fd, const void* buf, SceSize nbyte) {
	reinterpret_cast<std::fstream*>(fd)->write(reinterpret_cast<const char*>(buf), nbyte);
	return nbyte;
}

SceOff sceIoLseek(SceUID fd, SceOff offset, int whence) {
	switch (whence) {
	case SCE_SEEK_SET:
		reinterpret_cast<std::fstream*>(fd)->seekg(offset, std::ios::beg);
		break;
	case SCE_SEEK_END:
		reinterpret_cast<std::fstream*>(fd)->seekg(offset, std::ios::end);
		break;
	case SCE_SEEK_CUR:
		reinterpret_cast<std::fstream*>(fd)->seekg(offset, std::ios::cur);
		break;
	}

	return reinterpret_cast<std::fstream*>(fd)->tellg();
}