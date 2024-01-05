#ifndef SHARED_STRING_UTIL_H
#define SHARED_STRING_UTIL_H 1

#include <string>
#include <vector>
#include <iostream>

namespace Shared::String {
	class StringUtil {
	public: 
		static std::string Join(std::vector<std::string> parts, std::string delimiter);
		static std::vector<std::string> Split(std::string str, std::string delimiter);
		static std::string Replace(std::string str, std::string find, std::string replace);
		static std::string ToLower(std::string str);
		static std::string ToUpper(std::string str);
		static std::string Reverse(std::string str);
	};
}
#endif