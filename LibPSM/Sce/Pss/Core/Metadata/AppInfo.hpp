#ifndef LIB_PSS_APPINFO_H
#define LIB_PSS_APPINFO_H 1
#include <map>
#include <string>
#include <vector>
#include <LibCXML.hpp>
using namespace LibCXML;
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
		CXMLElement* element;

		// <application>
		std::string defaultLocale;
		std::string targetSdkVerison;
		std::string projectName;
		std::string appVersion;
		std::string targetRuntimeVersion;
		
		// <app_xml_format>
		std::string sdkType;
		std::string altVersion;

		// <name>
		std::vector<LocaleInfo> names;

		// <short_name>
		std::vector<LocaleInfo> shortNames;

		// <parental_control>
		int lockLevel = 0;

		// <rating_list>
		bool hasOnlineFeatures = false;
		int highestAgeLimit = 0;

		bool personalInfo = false;
		bool userLocation = false;
		bool exchangeContent = false; 
		bool chat = false;

		std::vector<RatingInfo> ratingList;

		// <images>
		LibCXML::CXMLStream* splash854x480 = NULL;
		LibCXML::CXMLStream* icon128x128 = NULL;
		LibCXML::CXMLStream* icon512x512 = NULL;
		LibCXML::CXMLStream* icon256x256 = NULL;

		// <genre_list>
		std::vector<std::string> genreList;
		
		// <developer>
		std::vector<std::string> developerList;
		std::string website;
		
		// <copyright> 
		LibCXML::CXMLStream* copyrightText = NULL;
		std::string author;

		// <purchase>
		// <product_list>
		std::vector<ProductInfo> productList;

		// <runtime_config>
		int managedHeapSize = 0;
		int resourceHeapSize = 0;
		std::string maxScreenSize;
		std::string maxCaptureResolution;

		// <feature_list>
		std::vector<std::string> featureList;

		// <unity>
		std::string runtimeVersion;
		std::string unityApplicationVer;

	public:
		AppInfo(CXMLElement* elem);
		~AppInfo();
		int ManagedHeapSize();
		int ResourceHeapSize();
	};
}

#endif