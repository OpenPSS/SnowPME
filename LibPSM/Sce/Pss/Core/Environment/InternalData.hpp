#ifndef LIB_PSS_INTERNALDATA_H
#define LIB_PSS_INTERNALDATA_H 1

namespace Sce::Pss::Core::Environment {
	typedef struct InternalData
	{
		bool QuitRequired;
		bool Restored;
		bool Minimized;
	} InternalData;
}

#endif