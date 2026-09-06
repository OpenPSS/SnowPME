#include <String/Encoding.hpp>
#include <vector>

namespace Shared::String {

	std::u8string Encoding::Utf16ToUtf8(const std::u16string& src)
	{
		std::vector<char8_t> buf((src.length() * 6) + 1);
		char8_t* dst = buf.data();

		for (int i = 0; src[i]; i++) {
			if (!(src[i] & 0xFF80)) {
				*(dst++) = src[i] & 0xFF;
			}
			else if (!(src[i] & 0xF800)) {
				*(dst++) = ((src[i] >> 6) & 0xFF) | 0xC0;
				*(dst++) = (src[i] & 0x3F) | 0x80;
			}
			else if ((src[i] & 0xFC00) == 0xD800 && (src[i + 1] & 0xFC00) == 0xDC00) {
				*(dst++) = (((src[i] + 64) >> 8) & 0x3) | 0xF0;
				*(dst++) = (((src[i] >> 2) + 16) & 0x3F) | 0x80;
				*(dst++) = ((src[i] >> 4) & 0x30) | 0x80 | ((src[i + 1] << 2) & 0xF);
				*(dst++) = (src[i + 1] & 0x3F) | 0x80;
				i += 1;
			}
			else {
				*(dst++) = ((src[i] >> 12) & 0xF) | 0xE0;
				*(dst++) = ((src[i] >> 6) & 0x3F) | 0x80;
				*(dst++) = (src[i] & 0x3F) | 0x80;
			}
		}

		*dst = '\0';

		return std::u8string(buf.data());
	}

	std::u16string Encoding::Utf8ToUtf16(const std::u8string& src)
	{
		std::vector<char16_t> buf((src.length() * 2) + 2);
		char16_t* dst = buf.data();

		for (size_t i = 0; i < buf.size() && src[i];) {
			if ((src[i] & 0xE0) == 0xE0) {
				if (i + 2 >= src.length()) {
					break;
				}
				*(dst++) = ((src[i] & 0x0F) << 12) | ((src[i + 1] & 0x3F) << 6) | (src[i + 2] & 0x3F);
				i += 3;
			}
			else if ((src[i] & 0xC0) == 0xC0) {
				if (i + 1 >= src.length()) {
					break;
				}
				*(dst++) = ((src[i] & 0x1F) << 6) | (src[i + 1] & 0x3F);
				i += 2;
			}
			else {
				*(dst++) = src[i];
				i += 1;
			}
		}

		*dst = '\0';
		return std::u16string(buf.data());
	}


}