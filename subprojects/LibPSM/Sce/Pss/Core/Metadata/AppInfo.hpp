#ifndef LIB_PSS_APPINFO_H
#define LIB_PSS_APPINFO_H 1
#include <map>
#include <string>
#include <vector>
#include <LibCXML.hpp>

#include <Sce/Pss/Core/PsmObject.hpp>
#include <Sce/Pss/Core/PsmUniqueObject.hpp>

#define READ_CXML_ATTRIBUTE(TYPE, VALUE, SET) { \
		LibCXML::CXMLAttribute<TYPE>* attribute = element->GetAttribute<LibCXML::CXMLAttribute<TYPE>*>(VALUE); \
		if (attribute != nullptr) { \
			SET = attribute->AttributeValue(); \
		} \
	}

namespace Sce::Pss::Core::Metadata {
	typedef struct LocaleInfo {
		std::string Locale;
		std::string Name;
	} LocaleInfo;

	typedef struct ProductInfo {
		std::string Type;
		std::string Label;
		std::vector<LocaleInfo> Names;

		std::string GetName(std::string locale); 
	} ProductInfo;


	typedef struct RatingInfo {
		int Age;
		std::string Code;
		std::string Type;
		int Value;
	} RatingInfo;

	class AppInfo : public PsmObject<AppInfo>, public PsmUniqueObject<AppInfo> {
	private:
		LibCXML::CXMLElement* element;
		bool nextElement();
	public:
		AppInfo(LibCXML::CXMLElement* elem);
		~AppInfo();
		std::string GetLocaleValue(std::vector<LocaleInfo>& localeInfos, std::string locale);

		// <application>
		std::string DefaultLocale;
		std::string TargetSdkVerison;
		std::string ProjectName;
		std::string AppVersion;
		std::string TargetRuntimeVersion;

		// <app_xml_format>
		std::string SdkType;
		std::string AltVersion;

		// <name>
		std::vector<LocaleInfo> Names;

		// <short_name>
		std::vector<LocaleInfo> ShortNames;

		// <parental_control>
		int LockLevel = 0;

		// <rating_list>
		bool HasOnlineFeatures = false;
		int HighestAgeLimit = 0;

		bool PersonalInfo = false;
		bool UserLocation = false;
		bool ExchangeContent = false;
		bool Chat = false;

		std::vector<RatingInfo> RatingList;

		// <images>
		LibCXML::CXMLStream* Splash854x480 = nullptr;
		LibCXML::CXMLStream* Icon128x128 = nullptr;
		LibCXML::CXMLStream* Icon512x512 = nullptr;
		LibCXML::CXMLStream* Icon256x256 = nullptr;

		// <genre_list>
		std::vector<std::string> GenreList;

		// <developer>
		std::vector<std::string> DeveloperList;
		std::string Website;

		// <copyright> 
		LibCXML::CXMLStream* CopyrightText = nullptr;
		std::string Author;

		// <purchase>
		// <product_list>
		std::vector<ProductInfo> ProductList;

		// <runtime_config>
		int ManagedHeapSize = 0x2000000;
		int ResourceHeapSize = 0x4000000;

		std::string MaxScreenSize;
		std::string MaxCaptureResolution = "800x600";

		// <feature_list>
		// feature_flag = 0x0x10101011;

		std::vector<std::string> FeatureList;

		// <unity>
		std::string UnityRuntimeVersion;
		std::string UnityApplicationVer;
	};
}

#endif