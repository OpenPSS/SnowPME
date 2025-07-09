#include <String/StringUtil.hpp>
#include <sstream>
#include <iomanip>
#include <cstdint>

namespace Shared::String {

	std::string Format::Hex(int val) {
		return Format::Hex(static_cast<uint64_t>(val));
	}
	
	std::string Format::Hex(uintptr_t val) {
		return Format::Hex(static_cast<uint64_t>(val));
	}

	std::string Format::Hex(uint64_t val) {
		std::stringstream hexStream;
		hexStream << std::hex << val;
		return hexStream.str();
	}

	std::string Format::ZFill(std::string val, char pad, size_t fillSize) {
		// add remaining pad bytes to the original string,
		for (size_t i = val.length(); i < fillSize; i++)
			val = std::string(&pad, 1) + val;
		return val;
	}

	std::string Format::Reverse(const std::string& str) {
		std::string littleEndainStr = str;
		std::string bigEndianStr = "";

		// Read string in reverse order
		for (int i = littleEndainStr.length(); i >= 0; i--)
			bigEndianStr += littleEndainStr.substr(i, 1);

		return bigEndianStr;
	}

	std::string Format::ToLower(const std::string& str) {
		// dont modify the original string
		std::string strcopy = str;
		
		//iterate over the entire string
		for (size_t i = 0; i < strcopy.length(); i++) {
			strcopy[i] = std::tolower(strcopy[i]); // change character to lowercase
		}

		return strcopy;
	}

	std::string Format::ToUpper(const std::string& str) {
		// dont modify the original string
		std::string strcopy = str;

		//iterate over the entire string
		for (size_t i = 0; i < strcopy.length(); i++) {
			strcopy[i] = std::toupper(strcopy[i]); // change character to uppercase
		}

		return strcopy;
	}

	std::string Format::Join(const std::vector<std::string> parts, const std::string& delimiter) {
		std::string str = "";
		for (size_t i = 0; i < parts.size(); i++) {
			str += parts.at(i);
			if (i + 1 < parts.size())
				str += delimiter;
		}
		return str;
	}

	std::vector<std::string> Format::Split(const std::string& str, const std::string& delimiter) {
		std::vector<std::string> strs;

		// Dont modify the original string
		std::string strcopy = str;

		// Iterate over all instances of the delimiter
		size_t pos = 0;
		std::string token;
		while ((pos = strcopy.find(delimiter)) != std::string::npos) {
			token = strcopy.substr(0, pos);
			strs.push_back(token); // Add it to the vector
			strcopy.erase(0, pos + delimiter.length()); // Remove token just found from the string
		}

		// Add the last one to the vector as well
		strs.push_back(strcopy);
		return strs;
	}

	std::string Format::CreateRandomString(int length) {
		std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
		std::string str = "";
		for (int i = 0; i < length; i++) {
			str += chars[rand() % chars.length()];
		}
		return str;
	}

	std::string Format::Replace(const std::string& str, const std::string& find, const std::string& replace) {
		// Dont modify the original string
		std::string strcopy = str;

		// Iterate over all instances of the variable to find
		size_t pos = 0;
		while ((pos = strcopy.find(find, pos)) != std::string::npos) {
			strcopy.replace(pos, find.length(), replace); // Replace it
			pos += replace.length();
		}
		
		return strcopy;
	}

}
