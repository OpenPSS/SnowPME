#ifndef SHARED_ENCODING_H
#define SHARED_ENCODING_H 1

#include <string>
#include <vector>
#include <cstdint>

namespace Shared::String {
	class Encoding {
	public:
		static std::u8string Encoding::Utf16ToUtf8(const std::u16string& src);
		static std::u16string Encoding::Utf8ToUtf16(const std::u8string& src);
	};
}

#endif