#ifndef LIB_CXML_ATTRIBUTE_BASE_H
#define LIB_CXML_ATTRIBUTE_BASE_H 1
#include "CXMLFile.hpp"
#include <string>

namespace LibCXML {

	class CXMLAttributeBase {
	protected:
		std::string attributeName;
	public:
		std::string AttributeName();
	};

}

#endif