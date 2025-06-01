#include <Sce/Pss/Core/Metadata/AppInfo.hpp>
#include <LibShared.hpp>
#include <LibCXML.hpp>

using namespace Shared::Debug;

namespace Sce::Pss::Core::Metadata {

	std::string ProductInfo::GetName(std::string locale) {
		for (LocaleInfo Name : Names) {
			if (Name.Locale == locale)
				return Name.Name;
		}

		if (Names.size() > 0)
			return Names.front().Name;

		return "Unknown";
	}

	AppInfo::~AppInfo() {
		LOCK_GUARD();
		delete element;
	}

	bool AppInfo::nextElement() {
		// goto next element

		if (element->HasFirstChild()) {
			element->FirstChild();
			return true;
		}
		else if (element->HasNextSibling()) {
			element->NextSibling();
			return true;
		}

		while (element->HasParentElement()) {
			element->ParentElement();
			if (element->HasNextSibling()) {
				element->NextSibling();
				return true;
			}
		}

		return false;
	}

	std::string AppInfo::GetLocaleValue(std::vector<LocaleInfo>& localeInfos, std::string locale) {
		if (localeInfos.empty()) return "";

		for (LocaleInfo localeInfo : localeInfos) {
			if (localeInfo.Locale == locale) {
				return localeInfo.Name;
			}
		}

		std::string name = AppInfo::GetLocaleValue(localeInfos, this->DefaultLocale);
		if (name.empty()) {
			return localeInfos.at(0).Name;
		}

		return name;
	}

	AppInfo::AppInfo(LibCXML::CXMLElement* elem) {
		LOCK_GUARD();

		this->element = elem;
		std::string parserMode = "";
		ProductInfo* productInfo = nullptr;

		if (this->element != nullptr) {
			do {
				if (parserMode != "product_list" && element->ElementName() == "name") parserMode = element->ElementName();
				else if (element->ElementName() == "short_name") parserMode = element->ElementName();
				else if (element->ElementName() == "unity") parserMode = element->ElementName();
				else if (element->ElementName() == "runtime_config") parserMode = element->ElementName();
				else if (element->ElementName() == "feature_list") parserMode = element->ElementName();
				else if (element->ElementName() == "product_list") parserMode = element->ElementName();
				else if (element->ElementName() == "application") {
					READ_CXML_ATTRIBUTE(std::string, "default_locale", this->DefaultLocale);
					READ_CXML_ATTRIBUTE(std::string, "sdk_version", this->TargetSdkVerison);
					READ_CXML_ATTRIBUTE(std::string, "project_name", this->ProjectName);
					READ_CXML_ATTRIBUTE(std::string, "version", this->AppVersion);
					READ_CXML_ATTRIBUTE(std::string, "runtime_version", this->TargetRuntimeVersion);
				}
				else if (element->ElementName() == "app_xml_format") {
					READ_CXML_ATTRIBUTE(std::string, "sdk_type", this->SdkType);
					READ_CXML_ATTRIBUTE(std::string, "version", this->AltVersion);
				}
				else if (parserMode == "name" && element->ElementName() == "localized_item") {
					LocaleInfo locale;
					READ_CXML_ATTRIBUTE(std::string, "locale", locale.Locale);
					READ_CXML_ATTRIBUTE(std::string, "value", locale.Name);
					Names.push_back(locale);
				}
				else if (parserMode == "short_name" && element->ElementName() == "localized_item") {
					LocaleInfo locale;
					READ_CXML_ATTRIBUTE(std::string, "locale", locale.Locale);
					READ_CXML_ATTRIBUTE(std::string, "value", locale.Name);
					ShortNames.push_back(locale);
				}
				else if (parserMode == "product_list" && element->ElementName() == "localized_item") {
					LocaleInfo locale;
					if (productInfo == nullptr) productInfo = new ProductInfo();

					READ_CXML_ATTRIBUTE(std::string, "locale", locale.Locale);
					READ_CXML_ATTRIBUTE(std::string, "value", locale.Name);
					productInfo->Names.push_back(locale);
				}
				else if (parserMode == "unity" && element->ElementName() == "unity_original_runtime_version") {
					READ_CXML_ATTRIBUTE(std::string, "value", this->UnityRuntimeVersion);
				}
				else if (parserMode == "unity" && element->ElementName() == "app_ver") {
					READ_CXML_ATTRIBUTE(std::string, "value", this->UnityApplicationVer);
				}
				else if (element->ElementName() == "parental_control") {
					READ_CXML_ATTRIBUTE(int, "lock_level", this->LockLevel);
				}
				else if (element->ElementName() == "rating_list") {
					std::string strHasOnlineFeatures;
					std::string strHighesAgeLimit;
					READ_CXML_ATTRIBUTE(std::string, "has_online_features", strHasOnlineFeatures);
					READ_CXML_ATTRIBUTE(int, "highest_age_limit", this->HighestAgeLimit);

					this->HasOnlineFeatures = (strHasOnlineFeatures == "true");
				}
				else if (element->ElementName() == "online_features") {
					std::string strPersonalInfo;
					std::string strUserLocation;
					std::string strExchangeContent;
					std::string strChat;

					READ_CXML_ATTRIBUTE(std::string, "personal_info", strPersonalInfo);
					READ_CXML_ATTRIBUTE(std::string, "user_location", strUserLocation);
					READ_CXML_ATTRIBUTE(std::string, "exchange_content", strExchangeContent);
					READ_CXML_ATTRIBUTE(std::string, "chat", strChat);

					this->PersonalInfo = strPersonalInfo == "true";
					this->UserLocation = strUserLocation == "true";
					this->ExchangeContent = strExchangeContent == "true";
					this->Chat = strChat == "true";
				}
				else if (element->ElementName() == "rating") {
					std::string strAge;
					std::string strValue;

					RatingInfo ratingInfo;
					READ_CXML_ATTRIBUTE(std::string, "code", ratingInfo.Code);
					READ_CXML_ATTRIBUTE(std::string, "type", ratingInfo.Type);

					READ_CXML_ATTRIBUTE(int, "age", ratingInfo.Age);
					READ_CXML_ATTRIBUTE(int, "value", ratingInfo.Value);

					this->RatingList.push_back(ratingInfo);
				}
				else if (element->ElementName() == "images") {
					READ_CXML_ATTRIBUTE(LibCXML::CXMLStream*, "splash_854x480", this->Splash854x480);
					READ_CXML_ATTRIBUTE(LibCXML::CXMLStream*, "icon_128x128", this->Icon128x128);
					READ_CXML_ATTRIBUTE(LibCXML::CXMLStream*, "icon_512x512", this->Icon512x512);
					READ_CXML_ATTRIBUTE(LibCXML::CXMLStream*, "icon_256x256", this->Icon256x256);
				}
				else if (element->ElementName() == "genre") {
					std::string strGenre;
					READ_CXML_ATTRIBUTE(std::string, "value", strGenre);
					this->GenreList.push_back(strGenre);
				}
				else if (element->ElementName() == "website") {
					READ_CXML_ATTRIBUTE(std::string, "href", this->Website);
				}
				else if (element->ElementName() == "copyright") {
					READ_CXML_ATTRIBUTE(LibCXML::CXMLStream*, "text", this->CopyrightText);
					READ_CXML_ATTRIBUTE(std::string, "author", this->Author);
				}
				else if (element->ElementName() == "product" && parserMode == "product_list") {
					if (productInfo != nullptr) {
						this->ProductList.push_back(*productInfo);
						delete productInfo;
						productInfo = nullptr;
					}

					productInfo = new ProductInfo();
					READ_CXML_ATTRIBUTE(std::string, "label", productInfo->Label);
					READ_CXML_ATTRIBUTE(std::string, "type", productInfo->Type);
				}
				else if (element->ElementName() == "memory") {
					READ_CXML_ATTRIBUTE(int, "managed_heap_size", this->ManagedHeapSize);
					READ_CXML_ATTRIBUTE(int, "resource_heap_size", this->ResourceHeapSize);
				}
				else if (element->ElementName() == "display") {
					READ_CXML_ATTRIBUTE(std::string, "max_screen_size", this->MaxScreenSize);
				}
				else if (element->ElementName() == "camera") {
					READ_CXML_ATTRIBUTE(std::string, "max_capture_resolution", this->MaxCaptureResolution);
				}
				else if (element->ElementName() == "feature") {
					std::string featureName;
					READ_CXML_ATTRIBUTE(std::string, "value", featureName);
					this->FeatureList.push_back(featureName);
				}
				else if (element->ElementName() == "name") {
					Logger::Debug("skipping app.info entry: " + element->ElementName());
				}
				else {
					Logger::Warn("app.info contains unknown element name: " + element->ElementName());
				}

			} while (this->nextElement());

		}

		// add remaining product info
		if (productInfo != nullptr) {
			this->ProductList.push_back(*productInfo);
			delete productInfo;
			productInfo = nullptr;
		}
	}
}