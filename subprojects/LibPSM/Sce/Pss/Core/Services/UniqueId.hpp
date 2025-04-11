#ifndef LIB_PSS_UNIQUEID_H
#define LIB_PSS_UNIQUEID_H 1

#include <string>
#include <cstdint>

namespace Sce::Pss::Core::Services {
	class UniqueId {
	private:
		static int getUniqueIDWindows(uint8_t* id);
		static int getUniqueIDAndroid(uint8_t* id);
		static int getUniqueIDVita(uint8_t* id);
	public:
		static int GetUniqueIDForEmulatedPlatform(uint8_t* id);
	};
}

#endif