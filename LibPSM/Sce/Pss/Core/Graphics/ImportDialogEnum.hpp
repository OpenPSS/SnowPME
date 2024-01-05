#ifndef LIB_PSS_IMPORTDIALOGENUM_H
#define LIB_PSS_IMPORTENUM_H
#include <string>
using namespace std;

namespace Sce::Pss::Core::Device {
	typedef struct DialogArguments { } DialogArguments;
	typedef struct DialogResults
	{
		string Filename;
	} DialogResults;
}

#endif
