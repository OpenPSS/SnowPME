#ifndef LIB_PSS_MULTISAMPLEMODE_H
#define LIB_PSS_MULTISAMPLEMODE_H

namespace Sce::Pss::Core::Graphics {
	enum class MultiSampleMode : unsigned int {
		None = 0,
		Msaa2x = 1,
		Msaa4x = 2
	};
}

#endif