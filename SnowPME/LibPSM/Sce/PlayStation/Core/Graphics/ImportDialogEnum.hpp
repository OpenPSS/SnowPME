#ifndef LIB_PSM_IMPORTDIALOGENUM_H
#define LIB_PSM_IMPORTENUM_H
#include <string>
using namespace std;

namespace Sce::PlayStation::Core::Device {
	typedef struct DialogArguments { } DialogArguments;
	typedef struct DialogResults
	{
		string Filename;
	} DialogResults;
}

#endif
