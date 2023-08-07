#ifndef LIB_PSS_APPINFO_H
#define LIB_PSS_APPINFO_H 1
#include <map>
#include <string>
#include <vector>
#include <LibCXML.hpp>
namespace Sce::Pss::Core::Metadata {

	typedef struct LocaleInfo {
		std::string Locale;
		std::string Name;
	} LocaleInfo;

	typedef struct ProductInfo {
		std::string Type;
		std::string Label;
		std::vector<LocaleInfo> Names;
	} ProductInfo;


	typedef struct RatingInfo {
		int Age;
		std::string Code;
		std::string Type;
		int Value;
	} RatingInfo;

	class AppInfo {
	private:
		LibCXML::CXMLElement* element;

		

	public:
		static AppInfo* ApplicationInfo;
		AppInfo(LibCXML::CXMLElement* elem);
		~AppInfo();
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
		LibCXML::CXMLStream* Splash854x480 = NULL;
		LibCXML::CXMLStream* Icon128x128 = NULL;
		LibCXML::CXMLStream* Icon512x512 = NULL;
		LibCXML::CXMLStream* Icon256x256 = NULL;

		// <genre_list>
		std::vector<std::string> GenreList;

		// <developer>
		std::vector<std::string> DeveloperList;
		std::string Website;

		// <copyright> 
		LibCXML::CXMLStream* CopyrightText = NULL;
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
		std::string RuntimeVersion;
		std::string UnityApplicationVer;
	};
}

#endif