#include "CXMLFile.hpp"
#include "CXMLReader.hpp"
#include "CXMLElement.hpp"
#include <fstream>

namespace LibCXML {
	bool CXMLReader::checkMagicNumber(const char* magic) {
		if (strncmp(this->cxmlHeader.magic, magic, MAGIC_LEN) == 0)
			return true;
		else
			return false;
	}

	CXMLStream* CXMLReader::readTable(CxmlTableDeclaration dec) {
		char* tableBuffer = new char[dec.tableSize];
		
		this->cxmlFile->seekg(dec.tableOffset);
		this->cxmlFile->read(tableBuffer, dec.tableSize);

		CXMLStream* stream = new CXMLStream(tableBuffer, dec.tableSize);
		delete[] tableBuffer;
		return stream;
	}


	CXMLReader::CXMLReader(std::string cxmlFilePath, const char* magic) {
		
		this->cxmlFile = new std::fstream(cxmlFilePath, std::ios::in | std::ios::binary);
		this->cxmlFile->read((char*)&this->cxmlHeader, sizeof(CxmlFileHeader));

		if (!checkMagicNumber(magic))
			throw new std::exception("CXML File is invalid or corrupt");

		this->TreeTable			= readTable(this->cxmlHeader.treeTable);
		this->IdTable			= readTable(this->cxmlHeader.idTable);
		this->HashIdTable		= readTable(this->cxmlHeader.hashIdTable);
		this->StringTable		= readTable(this->cxmlHeader.stringTable);
		this->WStringTable		= readTable(this->cxmlHeader.wstringTable);
		this->HashTable			= readTable(this->cxmlHeader.hashTable);
		this->IntArrayTable		= readTable(this->cxmlHeader.intArrayTable);
		this->FloatArrayTable	= readTable(this->cxmlHeader.floatArrayTable);
		this->FileTable			= readTable(this->cxmlHeader.fileTable);
	}


	CXMLReader::~CXMLReader() {
		delete this->TreeTable;
		delete this->IdTable;
		delete this->HashIdTable;
		delete this->StringTable;
		delete this->WStringTable;
		delete this->HashTable;
		delete this->IntArrayTable;
		delete this->FloatArrayTable;
		delete this->FileTable;

		this->cxmlFile->close();
		delete this->cxmlFile;
	}

}