#include "CXMLAttribute.hpp"
#include "CXMLStream.hpp"

#include <vector>
namespace LibCXML {
	template<> CXMLAttribute<std::vector<int>*>::~CXMLAttribute() {
		attributeValue->clear();
		delete attributeValue;
	}

	template<> CXMLAttribute<std::vector<float>*>::~CXMLAttribute() {
		attributeValue->clear();
		delete attributeValue;
	}

	template<> CXMLAttribute<CXMLStream*>::~CXMLAttribute() {
		delete attributeValue;
	}

}
