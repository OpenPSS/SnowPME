#ifndef LIB_PSM_CAMERAIMPORTDIALOG_H
#define LIB_PSM_CAMERAIMPORTDIALOG_H 1
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "../Environment/CommonDialogState.hpp"
#include "../Environment/CommonDialogResult.hpp"

using namespace std;
using namespace Sce::PlayStation::Core::Environment;

namespace Sce::PlayStation::Core::Device {
	class CameraImportDialog {
	private:
		typedef struct DialogArguments { } DialogArguments;

		typedef struct DialogResults
		{
			char* Filename;
		} DialogResults;
	public:
		static int NewNative(int type, int *handle);
		static int ReleaseNative(int type, int handle);
		static int OpenNative(int type, int handle, DialogArguments *dialogArguments);
		static int AbortNative(int type, int handle);
		static int GetState(int type, int handle, CommonDialogState *commonDialogState);
		static int GetResult(int type, int handle, CommonDialogResult *commonDialogResult, DialogResults *dialogResults);
	};
}
#endif
