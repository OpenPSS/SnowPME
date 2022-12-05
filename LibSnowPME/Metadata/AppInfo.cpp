#include <Debug/Logger.hpp>
#include <Metadata/AppInfo.hpp>
using namespace SnowPME::Debug;

namespace SnowPME::Metadata {

	#define READATTRIBUTE(TYPE, VALUE, SET) { \
		CXMLAttribute<TYPE>* attribute = element->GetAttribute<CXMLAttribute<TYPE>*>(VALUE); \
		if (attribute != NULL) { \
			SET = attribute->AttributeValue(); \
		} \
	}
	AppInfo::~AppInfo() {
		delete element;
	}
	int AppInfo::ManagedHeapSize() {
		return this->managedHeapSize;
	}
	int AppInfo::ResourceHeapSize() {
		return this->resourceHeapSize;
	}
	AppInfo::AppInfo(CXMLElement* elem) {
		element = elem;
		std::string parserMode = "";
		ProductInfo productInfo = ProductInfo();

		while(true) {
			if (element->ElementName() == "name") parserMode = element->ElementName();
			if (element->ElementName() == "short_name") parserMode = element->ElementName();
			if (element->ElementName() == "product") parserMode = element->ElementName();

			if (element->ElementName() == "application") {
				READATTRIBUTE(std::string, "default_locale", this->defaultLocale);
				READATTRIBUTE(std::string, "sdk_version", this->targetSdkVerison);
				READATTRIBUTE(std::string, "project_name", this->projectName);
				READATTRIBUTE(std::string, "version", this->appVersion);
				READATTRIBUTE(std::string, "runtime_version", this->targetRuntimeVersion);
			}
			else if (parserMode == "name" && element->ElementName() == "localized_item") {
				LocaleInfo locale;
				READATTRIBUTE(std::string, "locale", locale.Locale);
				READATTRIBUTE(std::string, "value", locale.Name);
				names.push_back(locale);
			}
			else if (parserMode == "short_name" && element->ElementName() == "localized_item") {
				LocaleInfo locale;
				READATTRIBUTE(std::string, "locale", locale.Locale);
				READATTRIBUTE(std::string, "value", locale.Name);
				shortNames.push_back(locale);
			}
			else if (parserMode == "product" && element->ElementName() == "localized_item") {
				LocaleInfo locale;
				READATTRIBUTE(std::string, "locale", locale.Locale);
				READATTRIBUTE(std::string, "value", locale.Name);
				productInfo.Names.push_back(locale);
			}
			else if (element->ElementName() == "parental_control") {
				READATTRIBUTE(int, "lock_level", this->lockLevel);
			}
			else if (element->ElementName() == "rating_list") {
				std::string strHasOnlineFeatures;
				std::string strHighesAgeLimit;
				READATTRIBUTE(std::string, "has_online_features", strHasOnlineFeatures);
				READATTRIBUTE(int, "highest_age_limit", this->highestAgeLimit);

				this->hasOnlineFeatures = (strHasOnlineFeatures == "true");
			}
			else if (element->ElementName() == "online_features") {
				std::string strPersonalInfo;
				std::string strUserLocation;
				std::string strExchangeContent;
				std::string strChat;

				READATTRIBUTE(std::string, "personal_info", strPersonalInfo);
				READATTRIBUTE(std::string, "user_location", strUserLocation);
				READATTRIBUTE(std::string, "exchange_content", strExchangeContent);
				READATTRIBUTE(std::string, "chat", strChat);

				this->personalInfo = strPersonalInfo == "true";
				this->userLocation = strUserLocation == "true";
				this->exchangeContent = strExchangeContent == "true";
				this->chat = strChat == "true";
			}
			else if (element->ElementName() == "rating") {
				std::string strAge;
				std::string strValue;

				RatingInfo ratingInfo;
				READATTRIBUTE(std::string, "code", ratingInfo.Code);
				READATTRIBUTE(std::string, "type", ratingInfo.Type);

				READATTRIBUTE(int, "age", ratingInfo.Age);
				READATTRIBUTE(int, "value", ratingInfo.Value);

				this->ratingList.push_back(ratingInfo);
			}
			else if (element->ElementName() == "images") {
				READATTRIBUTE(LibCXML::CXMLStream*, "splash_854x480", this->splash854x480);
				READATTRIBUTE(LibCXML::CXMLStream*, "icon_128x128", this->icon128x128);
				READATTRIBUTE(LibCXML::CXMLStream*, "icon_512x512", this->icon512x512);
				READATTRIBUTE(LibCXML::CXMLStream*, "icon_256x256", this->icon256x256);
			}
			else if (element->ElementName() == "genre") {
				std::string strGenre;
				READATTRIBUTE(std::string, "value", strGenre);
				this->genreList.push_back(strGenre);
			}
			else if (element->ElementName() == "website") {
				READATTRIBUTE(std::string, "href", this->website);
			}
			else if (element->ElementName() == "copyright") {
				READATTRIBUTE(LibCXML::CXMLStream*, "text", this->copyrightText);
				READATTRIBUTE(std::string, "author", this->author);
			}
			else if (element->ElementName() == "product") {
				if(!productInfo.Label.empty())
					this->productList.push_back(productInfo);
				productInfo = ProductInfo();
				READATTRIBUTE(std::string, "label", productInfo.Label);
				READATTRIBUTE(std::string, "type", productInfo.Type);
			}
			else if (element->ElementName() == "memory") {
				READATTRIBUTE(int, "managed_heap_size", this->managedHeapSize);
				READATTRIBUTE(int, "resource_heap_size", this->resourceHeapSize);
			}
			else if (element->ElementName() == "display") {
				READATTRIBUTE(std::string, "max_screen_size", this->maxScreenSize);
			}
			else if (element->ElementName() == "camera") {
				READATTRIBUTE(std::string, "max_capture_resolution", this->maxCaptureResolution);
			}
			if (element->ElementName() == "feature") {
				std::string featureName;
				READATTRIBUTE(std::string, "value", featureName);
				this->featureList.push_back(featureName);
			}
			else if (element->ElementName() == "runtime_config" || element->ElementName() == "feature_list") {
				Logger::Debug("Skipping reading: " + element->ElementName());
			}
			else {
				Logger::Warn("app.info contains unknown element name: " + element->ElementName());
			}
			// goto next element

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

		}


	}
}