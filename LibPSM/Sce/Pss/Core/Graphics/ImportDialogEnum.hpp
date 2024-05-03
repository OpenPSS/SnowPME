#ifndef LIB_PSS_IMPORTDIALOGENUM_H
#define LIB_PSS_IMPORTENUM_H
#include <string>

namespace Sce::Pss::Core::Device {
	typedef struct DialogArguments { } DialogArguments;
	typedef struct DialogResults
	{
		std::string Filename;
	} DialogResults;
}

#endif
