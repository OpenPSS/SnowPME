#ifndef LIB_PSM_INTERNALDATA_H
#define LIB_PSM_INTERNALDATA_H 1

namespace Sce::PlayStation::Core::Environment {
	typedef struct InternalData
	{
		bool QuitRequired;
		bool Restored;
		bool Minimized;
	} InternalData;
}

#endif