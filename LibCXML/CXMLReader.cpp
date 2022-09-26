#include "CXMLFile.hpp"
#include "CXMLReader.hpp"
#include <fstream>

namespace LibCXML {
	bool CXMLReader::checkMagicNumber() {
		if (strncmp(this->cxmlHeader.magic, APPINFO_MAGIC, MAGIC_LEN) == 0)
			return true;
		else
			return false;
	}

	void CXMLReader::readTable(CxmlTableDeclaration dec, CxmlTableBuffer* buf) {
		buf->buffer = new char[dec.tableSize];
		this->cxmlFile->seekg(dec.tableOffset, std::ios::beg);
		this->cxmlFile->read(buf->buffer, dec.tableSize);
		buf->length = dec.tableSize;
	}

	CXMLReader::CXMLReader(std::string cxmlFilePath) {
		
		this->cxmlFile = new std::fstream(cxmlFilePath, std::ios::in | std::ios::binary);
		this->cxmlFile->read((char*)&(this->cxmlHeader), sizeof(CxmlFileHeader));

		if (!checkMagicNumber())
			throw new std::exception("CXML File is invalid or corrupt");

		readTable(this->cxmlHeader.treeTable,		&this->treeTable);
		readTable(this->cxmlHeader.idTable,			&this->idTable);
		readTable(this->cxmlHeader.hashIDTable,		&this->hashIDTable);
		readTable(this->cxmlHeader.stringTable,		&this->stringTable);
		readTable(this->cxmlHeader.wstringTable,	&this->wstringTable);
		readTable(this->cxmlHeader.hashTable,		&this->hashTable);
		readTable(this->cxmlHeader.intArrayTable,	&this->intArrayTable);
		readTable(this->cxmlHeader.floatArrayTable,	&this->floatArrayTable);
		readTable(this->cxmlHeader.fileTable,		&this->fileTable);

	}
	CXMLReader::~CXMLReader() {
		delete[] this->treeTable.buffer;
		delete[] this->idTable.buffer;
		delete[] this->hashIDTable.buffer;
		delete[] this->stringTable.buffer;
		delete[] this->wstringTable.buffer;
		delete[] this->hashTable.buffer;
		delete[] this->intArrayTable.buffer;
		delete[] this->floatArrayTable.buffer;
		delete[] this->fileTable.buffer;

		this->cxmlFile->close();
		delete this->cxmlFile;
	}

}