#ifndef LIB_PSS_IMPORTDIALOGENUM_H
#define LIB_PSS_IMPORTDIALOGENUM_H 1
#include <string>
#include <mono/mono.h>

namespace Sce::Pss::Core::Device {
	typedef struct DialogArguments { } DialogArguments;
	typedef struct DialogResults
	{
		MonoString* Filename;
	} DialogResults;
}

#endif
