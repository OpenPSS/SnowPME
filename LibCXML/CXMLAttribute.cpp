#include "CXMLAttribute.hpp"
#include "CXMLStream.hpp"

#include <vector>
namespace LibCXML {
	CXMLAttribute<std::vector<int>*>::~CXMLAttribute() {
		attributeValue->clear();
		delete attributeValue;
	}

	CXMLAttribute<std::vector<float>*>::~CXMLAttribute() {
		attributeValue->clear();
		delete attributeValue;
	}

	CXMLAttribute<CXMLStream*>::~CXMLAttribute() {
		delete attributeValue;
	}

}