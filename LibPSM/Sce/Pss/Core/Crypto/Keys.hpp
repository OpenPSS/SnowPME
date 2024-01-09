#ifndef LIB_PSS_KEYS_H 
#define LIB_PSS_KEYS_H
#include <iostream>

namespace Sce::Pss::Core::Crypto::Keys {
		// used for calculating Sce::Pss::Core::Services::AccountInformation::GetUniqueID on PSVita and Android.
		static const uint8_t HashAccountIdHmac256[0x20] { 0xBD, 0xEE, 0x3E, 0x0B, 0x93, 0x07, 0x37, 0x49, 0x85, 0x6F, 0x25, 0xCC, 0xDB, 0x44, 0x3A, 0xFB, 0x0F, 0xAB, 0x94, 0x28, 0x74, 0x93, 0xDC, 0x1A, 0xD0, 0xC5, 0x69, 0x7E, 0x2A, 0x7A, 0xE1, 0x4E };
		static const uint8_t HashAccountIdAes128[0x10] { 0x5A, 0xA3, 0xDB, 0x8F, 0xE6, 0xAE, 0xE2, 0x6C, 0xD1, 0x85, 0xB0, 0x86, 0xF5, 0xBD, 0x78, 0xA4 };
		
		// used for decryption of PSSE ..
		static const uint8_t PsseHeaderKey[0x10] { 0x4E, 0x29, 0x8B, 0x40, 0xF5, 0x31, 0xF4, 0x69, 0xD2, 0x1F, 0x75, 0xB1, 0x33, 0xC3, 0x07, 0xBE }; 
		static const uint8_t RuntimeGameKey[0x10] = { 0xA8, 0x69, 0x3C, 0x4D, 0xF0, 0xAE, 0xED, 0xBC, 0x9A, 0xBF, 0xD8, 0x21, 0x36, 0x92, 0x91, 0x2D };
		static const uint8_t PsseHeaderKeyPsmDev[0x10] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF };

		static const uint8_t SequentialIv[0x10]{ 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F };
		static const uint8_t NullIv[0x10] { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
}

#endif