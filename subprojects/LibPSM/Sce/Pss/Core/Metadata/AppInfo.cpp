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

	std::string* AppInfo::GetLocaleValue(std::vector<LocaleInfo>& localeInfos, std::string locale) {
		for (LocaleInfo localeInfo : localeInfos) {
			if (localeInfo.Locale == locale) {
				return &localeInfo.Name;
			}
		}
		return nullptr;
	}

	AppInfo::AppInfo(LibCXML::CXMLElement* elem) {
		LOCK_GUARD();

		this->element = elem;
		std::string parserMode = "";
		ProductInfo* productInfo = nullptr;

		if (elem != nullptr) {
			do {
				if (parserMode != "product_list" && element->ElementName() == "name") parserMode = element->ElementName();
				else if (element->ElementName() == "short_name") parserMode = element->ElementName();
				else if (element->ElementName() == "unity") parserMode = element->ElementName();
				else if (element->ElementName() == "runtime_config") parserMode = element->ElementName();
				else if (element->ElementName() == "feature_list") parserMode = element->ElementName();
				else if (element->ElementName() == "product_list") parserMode = element->ElementName();
				else if (element->ElementName() == "application") {
					READATTRIBUTE(std::string, "default_locale", this->DefaultLocale);
					READATTRIBUTE(std::string, "sdk_version", this->TargetSdkVerison);
					READATTRIBUTE(std::string, "project_name", this->ProjectName);
					READATTRIBUTE(std::string, "version", this->AppVersion);
					READATTRIBUTE(std::string, "runtime_version", this->TargetRuntimeVersion);
				}
				else if (element->ElementName() == "app_xml_format") {
					READATTRIBUTE(std::string, "sdk_type", this->SdkType);
					READATTRIBUTE(std::string, "version", this->AltVersion);
				}
				else if (parserMode == "name" && element->ElementName() == "localized_item") {
					LocaleInfo locale;
					READATTRIBUTE(std::string, "locale", locale.Locale);
					READATTRIBUTE(std::string, "value", locale.Name);
					Names.push_back(locale);
				}
				else if (parserMode == "short_name" && element->ElementName() == "localized_item") {
					LocaleInfo locale;
					READATTRIBUTE(std::string, "locale", locale.Locale);
					READATTRIBUTE(std::string, "value", locale.Name);
					ShortNames.push_back(locale);
				}
				else if (parserMode == "product_list" && element->ElementName() == "localized_item") {
					LocaleInfo locale;
					if (productInfo == nullptr) productInfo = new ProductInfo();

					READATTRIBUTE(std::string, "locale", locale.Locale);
					READATTRIBUTE(std::string, "value", locale.Name);
					productInfo->Names.push_back(locale);
				}
				else if (parserMode == "unity" && element->ElementName() == "unity_original_runtime_version") {
					READATTRIBUTE(std::string, "value", this->UnityRuntimeVersion);
				}
				else if (parserMode == "unity" && element->ElementName() == "app_ver") {
					READATTRIBUTE(std::string, "value", this->UnityApplicationVer);
				}
				else if (element->ElementName() == "parental_control") {
					READATTRIBUTE(int, "lock_level", this->LockLevel);
				}
				else if (element->ElementName() == "rating_list") {
					std::string strHasOnlineFeatures;
					std::string strHighesAgeLimit;
					READATTRIBUTE(std::string, "has_online_features", strHasOnlineFeatures);
					READATTRIBUTE(int, "highest_age_limit", this->HighestAgeLimit);

					this->HasOnlineFeatures = (strHasOnlineFeatures == "true");
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

					this->PersonalInfo = strPersonalInfo == "true";
					this->UserLocation = strUserLocation == "true";
					this->ExchangeContent = strExchangeContent == "true";
					this->Chat = strChat == "true";
				}
				else if (element->ElementName() == "rating") {
					std::string strAge;
					std::string strValue;

					RatingInfo ratingInfo;
					READATTRIBUTE(std::string, "code", ratingInfo.Code);
					READATTRIBUTE(std::string, "type", ratingInfo.Type);

					READATTRIBUTE(int, "age", ratingInfo.Age);
					READATTRIBUTE(int, "value", ratingInfo.Value);

					this->RatingList.push_back(ratingInfo);
				}
				else if (element->ElementName() == "images") {
					READATTRIBUTE(LibCXML::CXMLStream*, "splash_854x480", this->Splash854x480);
					READATTRIBUTE(LibCXML::CXMLStream*, "icon_128x128", this->Icon128x128);
					READATTRIBUTE(LibCXML::CXMLStream*, "icon_512x512", this->Icon512x512);
					READATTRIBUTE(LibCXML::CXMLStream*, "icon_256x256", this->Icon256x256);
				}
				else if (element->ElementName() == "genre") {
					std::string strGenre;
					READATTRIBUTE(std::string, "value", strGenre);
					this->GenreList.push_back(strGenre);
				}
				else if (element->ElementName() == "website") {
					READATTRIBUTE(std::string, "href", this->Website);
				}
				else if (element->ElementName() == "copyright") {
					READATTRIBUTE(LibCXML::CXMLStream*, "text", this->CopyrightText);
					READATTRIBUTE(std::string, "author", this->Author);
				}
				else if (element->ElementName() == "product" && parserMode == "product_list") {
					if (productInfo != nullptr) {
						this->ProductList.push_back(*productInfo);
						delete productInfo;
						productInfo = nullptr;
					}

					productInfo = new ProductInfo();
					READATTRIBUTE(std::string, "label", productInfo->Label);
					READATTRIBUTE(std::string, "type", productInfo->Type);
				}
				else if (element->ElementName() == "memory") {
					READATTRIBUTE(int, "managed_heap_size", this->ManagedHeapSize);
					READATTRIBUTE(int, "resource_heap_size", this->ResourceHeapSize);
				}
				else if (element->ElementName() == "display") {
					READATTRIBUTE(std::string, "max_screen_size", this->MaxScreenSize);
				}
				else if (element->ElementName() == "camera") {
					READATTRIBUTE(std::string, "max_capture_resolution", this->MaxCaptureResolution);
				}
				else if (element->ElementName() == "feature") {
					std::string featureName;
					READATTRIBUTE(std::string, "value", featureName);
					this->FeatureList.push_back(featureName);
				}
				else if (element->ElementName() == "name") {
					Logger::Debug("skipping app.info entry: " + element->ElementName());
				}
				else {
					Logger::Warn("app.info contains unknown element name: " + element->ElementName());
				}

			}while (this->nextElement());

		}

		// add remaining product info
		if (productInfo != nullptr) {
			this->ProductList.push_back(*productInfo);
			delete productInfo;
			productInfo = nullptr;
		}
	}
}