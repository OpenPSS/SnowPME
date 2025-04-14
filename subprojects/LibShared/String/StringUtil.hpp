#ifndef SHARED_STRING_UTIL_H
#define SHARED_STRING_UTIL_H 1

#include <string>
#include <vector>
#include <iostream>

namespace Shared::String {
	class StringUtil {
	public: 
		static std::string ZFill(std::string val, char pad, size_t fillSize);
		static std::string Join(const std::vector<std::string> parts, const std::string& delimiter);
		static std::vector<std::string> Split(const std::string& str, const std::string& delimiter);
		static std::string Replace(const std::string& str, const std::string& find, const std::string& replace);
		static std::string ToLower(const std::string& str);
		static std::string ToUpper(const std::string& str);
		static std::string Reverse(const std::string& str);
		static std::string CreateRandomString(int length);
	};
}
#endif