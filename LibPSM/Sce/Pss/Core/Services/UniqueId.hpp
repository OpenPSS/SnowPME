#ifndef LIB_PSS_UNIQUEID_H
#define LIB_PSS_UNIQUEID_H 1

#include <string>

namespace Sce::Pss::Core::Services {
	class UniqueId {
	private:
		static int getUniqueIDWindows(std::byte* id);
		static int getUniqueIDAndroid(std::byte* id);
		static int getUniqueIDVita(std::byte* id);
	public:
		static int GetUniqueIDForEmulatedPlatform(std::byte* id);
	};
}

#endif