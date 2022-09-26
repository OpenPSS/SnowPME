#ifndef LIB_CXML_FILE_H
#define LIB_CXML_FILE_H 1
#include <cstdint>


#ifdef __cplusplus
extern "C" {
#endif
#define MAGIC_LEN 4
#define APPINFO_MAGIC "PSMA"

	typedef struct CxmlTableBuffer {
		char* buffer;
		size_t length;
	} CxmlTableBuffer;

	typedef struct CxmlTableDeclaration {
		uint32_t tableOffset;
		uint32_t tableSize;
	} CxmlTableDeclaration;

	typedef struct CxmlFileHeader {
		char magic[MAGIC_LEN];
		uint32_t version;

		CxmlTableDeclaration treeTable;
		CxmlTableDeclaration idTable;
		CxmlTableDeclaration hashIDTable;
		CxmlTableDeclaration stringTable;
		CxmlTableDeclaration wstringTable;
		CxmlTableDeclaration hashTable;
		CxmlTableDeclaration intArrayTable;
		CxmlTableDeclaration floatArrayTable;
		CxmlTableDeclaration fileTable;
	} CxmlFileHeader;



#ifdef __cplusplus
}
#endif

#endif