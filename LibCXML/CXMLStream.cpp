#include "CXMLFile.hpp"
#include "CXMLStream.hpp"
#include <cstring>
#include <string>

namespace LibCXML {
	CXMLStream::CXMLStream(char* srcbuffer, size_t length) {

		this->buffer = new char[length];
		memcpy(this->buffer, srcbuffer, length);
		this->length = length;
		this->pos = 0;
	}

	CXMLStream::~CXMLStream() {
		delete[] this->buffer;
	}

	size_t CXMLStream::Length() {
		return this->length;
	}

	void CXMLStream::Seek(size_t pos) {
		this->pos = pos;
	}

	char* CXMLStream::ReadStrLen(size_t sz) {
		char* str = this->buffer + this->pos;
		pos += sz * sizeof(char);
		return str;
	}

	wchar* CXMLStream::ReadWStrLen(size_t sz) {
		wchar* str = (wchar*)(this->buffer + this->pos);
		pos += sz * sizeof(wchar);
		return str;
	}

	char* CXMLStream::ReadStr() {
		char* str = this->buffer + this->pos;
		pos += (strlen(str)) + (sizeof(char));
		return str;
	}

	wchar* CXMLStream::ReadWStr() {
		wchar* str = (wchar*)(this->buffer + this->pos);
		pos += (wcslen(str)) + (sizeof(wchar));
		return str;
	}

	float CXMLStream::ReadFloat() {
		float val;
		this->Read(&val, sizeof(float));
		return val;
	}

	double CXMLStream::ReadDouble() {
		double val;
		this->Read(&val, sizeof(double));
		return val;
	}

	int CXMLStream::ReadInt() {
		int val;
		this->Read(&val, sizeof(int));
		return val;
	}

	size_t CXMLStream::Read(void* buf, size_t sz) {
		size_t realsz = sz;
		if ((this->pos + realsz) > this->length)
			realsz = (this->length - this->pos);

		memcpy(buf, this->buffer + this->pos, realsz);

		this->pos += realsz;

		return realsz;
	}

}