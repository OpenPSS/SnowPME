#include <String/StringUtil.hpp>

namespace Shared::String {

	std::string StringUtil::Reverse(std::string str) {
		std::string littleEndainStr = str;
		std::string bigEndainStr = "";

		// Read string in reverse order
		for (int i = littleEndainStr.length(); i >= 0; i--)
			bigEndainStr += littleEndainStr.substr(i, 1);

		return bigEndainStr;
	}

	std::string StringUtil::ToLower(std::string str) {
		// dont modify the original string
		std::string strcopy = str;
		
		//iterate over the entire string
		for (size_t i = 0; i < strcopy.length(); i++) {
			strcopy[i] = std::tolower(strcopy[i]); // change character to lowercase
		}

		return strcopy;
	}

	std::string StringUtil::ToUpper(std::string str) {
		// dont modify the original string
		std::string strcopy = str;

		//iterate over the entire string
		for (size_t i = 0; i < strcopy.length(); i++) {
			strcopy[i] = std::toupper(strcopy[i]); // change character to uppercase
		}

		return strcopy;
	}

	std::string StringUtil::Join(std::vector<std::string> parts, std::string delimiter) {
		std::string str = "";
		for (size_t i = 0; i < parts.size(); i++) {
			str += parts.at(i);
			if (i + 1 < parts.size())
				str += delimiter;
		}
		return str;
	}

	std::vector<std::string> StringUtil::Split(std::string str, std::string delimiter) {
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

	std::string StringUtil::Replace(std::string str, std::string find, std::string replace) {
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
