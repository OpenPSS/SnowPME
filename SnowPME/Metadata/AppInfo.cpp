#include <Debug/Logger.hpp>
#include <Metadata/AppInfo.hpp>

#define GETATTRIB(TYPE, VALUE, SETTO) CXMLAttribute<TYPE>* attrib = element->GetAttribute<TYPE>(VALUE); \
										if (attrib == NULL){ \
											SETTO = attrib->AttributeValue(); \
										} 
										

using namespace SnowPME::Debug;

namespace SnowPME::Metadata {
	AppInfo::AppInfo(CXMLElement* elem) {
		element = elem;

		do {
			Logger::Debug(element->ElementName());

			if (element->HasFirstChild()) {
				element->FirstChild();
			}
			else if (element->HasNextSibling()) {
				element->NextSibling();
			}
			else if (element->HasParentElement()) {
				element->ParentElement();
				if (element->HasNextSibling()) {
					element->NextSibling();
				}
				else {
					break;
				}
			}

			if (element->ElementName() == "application") {
			}



		} while (true);


	}
}