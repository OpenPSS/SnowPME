#ifndef LIB_CXML_STREAM_H
#define LIB_CXML_STREAM_H 1
#include "CXMLFile.hpp"
#include <cstdint>
#include <string>
namespace LibCXML {
	class CXMLStream {
		char* buffer;
		size_t length;
		size_t pos;
	public:
		CXMLStream(char* srcbuffer, size_t size);
		~CXMLStream();
		size_t Length();
		size_t Read(void* buf, size_t sz);
		int ReadInt();
		float ReadFloat();
		double ReadDouble();
		char* ReadStr();
		wchar* ReadWStr();
		char* ReadStrLen(size_t sz);
		wchar* ReadWStrLen(size_t sz);
		void Seek(size_t pos);
	};
}

#endif