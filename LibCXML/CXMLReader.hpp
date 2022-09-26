#ifndef LIB_CXML_READER_H
#define LIB_CXML_READER_H 1
#include <string>
#include <fstream>
#include <filesystem>


namespace LibCXML {

	class CXMLReader {
	private: 
		bool checkMagicNumber();
		void readTable(CxmlTableDeclaration dec, CxmlTableBuffer* buf);

		std::fstream* cxmlFile;
		CxmlFileHeader cxmlHeader;

		CxmlTableBuffer treeTable;
		CxmlTableBuffer idTable;
		CxmlTableBuffer hashIDTable;
		CxmlTableBuffer stringTable;
		CxmlTableBuffer wstringTable;
		CxmlTableBuffer hashTable;
		CxmlTableBuffer intArrayTable;
		CxmlTableBuffer floatArrayTable;
		CxmlTableBuffer fileTable;
	public:
		CXMLReader(std::string cxmlFilePath);
		~CXMLReader();
	};

}

#endif