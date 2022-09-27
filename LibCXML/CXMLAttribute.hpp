#ifndef LIB_CXML_ATTRIBUTE_H
#define LIB_CXML_ATTRIBUTE_H 1
#include "CXMLFile.hpp"
#include "CXMLReader.hpp"
#include "CXMLAttributeBase.hpp"

#include <string>

namespace LibCXML {

	template <typename T> class CXMLAttribute : public CXMLAttributeBase {
	private:
		T attributeValue;
	public:
		CXMLAttribute(std::string cxmlAttributeName, T cxnlAttributeValue) {
			this->attributeName = cxmlAttributeName;
			this->attributeValue = cxnlAttributeValue;
		}
		~CXMLAttribute();
		T AttributeValue() {
			return attributeValue;
		}
	};
}

#endif