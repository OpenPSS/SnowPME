#ifndef LIB_CXML_READER_H
#define LIB_CXML_READER_H 1
#include <string>
#include <fstream>
#include <filesystem>
#include "CXMLFile.hpp"
#include "CXMLStream.hpp"

namespace LibCXML {
	class CXMLReader {
	private: 
		bool checkMagicNumber();
		CXMLStream* readTable(CxmlTableDeclaration dec);
		std::fstream* cxmlFile;
		CxmlFileHeader cxmlHeader;
	public:

		CXMLStream* TreeTable;
		CXMLStream* IdTable;
		CXMLStream* HashIdTable;
		CXMLStream* StringTable;
		CXMLStream* WStringTable;
		CXMLStream* HashTable;
		CXMLStream* IntArrayTable;
		CXMLStream* FloatArrayTable;
		CXMLStream* FileTable;

		CXMLReader(std::string cxmlFilePath);
		~CXMLReader();
	};

}

#endif