#ifndef LIB_PSM_MULTISAMPLEMODE_H
#define LIB_PSM_MULTISAMPLEMODE_H

namespace Sce::PlayStation::Core::Graphics {
	enum class MultiSampleMode : unsigned int {
		None = 0,
		Msaa2x = 1,
		Msaa4x = 2
	};
}

#endif