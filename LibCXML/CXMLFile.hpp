#ifndef LIB_CXML_FILE_H
#define LIB_CXML_FILE_H 1
#include <cstdint>


#ifdef __cplusplus
extern "C" {
#endif

#ifdef _MSC_VER
	typedef wchar_t wchar;
#endif

#define MAGIC_LEN 4

	typedef enum CxmlAttributeType : uint32_t
	{
		TYPE_NONE = 0,
		TYPE_INT = 1,
		TYPE_FLOAT = 2,
		TYPE_STRING = 3,
		TYPE_WSTRING = 4,
		TYPE_HASH = 5,
		TYPE_INTEGER_ARRAY = 6,
		TYPE_FLOAT_ARRAY = 7,
		TYPE_FILE = 8,
		TYPE_ID_REF = 9,
		TYPE_ID = 10,
		TYPE_ID_HASH_REF = 11,
		TYPE_ID_HASH = 12
	} CxmlAttributeType;
	
	typedef struct CxmlAttributeRefId {
		uint32_t ref;
		uint32_t id;
	} CxmlAttributeValueSz;

	typedef struct CxmlAttributeHeader {
		uint32_t name;
		CxmlAttributeType type;
		uint32_t value;
		uint32_t sz;
	} CxmlAttributeHeader;

	typedef struct CxmlElementHeader {
		uint32_t elementName;
		uint32_t numAttributes;
		
		uint32_t parentElement;
		uint32_t prevSibling;
		uint32_t nextSibling;

		uint32_t firstChild;
		uint32_t lastChild;
	} CxmlElementHeader;

	typedef struct CxmlTableDeclaration {
		uint32_t tableOffset;
		uint32_t tableSize;
	} CxmlTableDeclaration;

	typedef struct CxmlFileHeader {
		char magic[MAGIC_LEN];
		uint32_t version;

		CxmlTableDeclaration treeTable;
		CxmlTableDeclaration idTable;
		CxmlTableDeclaration hashIdTable;
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