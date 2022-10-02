#ifndef SNOW_PME_APPINFO_H
#define SNOW_PME_APPINFO_H 1
#include <map>
#include <string>
#include <vector>
#include <LibCXML.hpp>
namespace SnowPME::Metadata {

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
		// <application>
		std::string defaultLocale;
		std::string targetSdkVerison;
		std::string projectName;
		std::string appVersion;
		std::string targetRuntimeVersion;
		
		// <name>
		std::vector<LocaleInfo> names;

		// <short_name>
		std::vector<LocaleInfo> shortNames;

		// <rating_list>
		bool personalInfo;
		bool userLocation;
		bool exchangeContent;
		bool chat;
		std::vector<RatingInfo> ratingList;

		// <images>
		LibCXML::CXMLStream* splash854x480;
		LibCXML::CXMLStream* icon128x128;
		LibCXML::CXMLStream* icon512x512;
		LibCXML::CXMLStream* icon256x256;

		// <genre_list>
		std::vector<std::string> genreList;
		
		// <developer>
		std::vector<std::string> developerList;
		std::string website;
		
		// <copyright> 
		LibCXML::CXMLStream* copyrightText;
		std::string author;

		// <purchase>
		// <product_list>
		std::vector<ProductInfo> productList;

		// <runtime_config>
		uint32_t managedHeapSize;
		uint32_t resourceHeapSize;
		std::string maxScreenSize;
		std::string maxCaptureResolution;

		// <feature_list>
		std::vector<std::string> featureList;
	};
}

#endif