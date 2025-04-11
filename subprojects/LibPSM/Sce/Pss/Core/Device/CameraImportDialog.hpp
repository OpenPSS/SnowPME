#ifndef LIB_PSS_CAMERAIMPORTDIALOG_H
#define LIB_PSS_CAMERAIMPORTDIALOG_H 1
#include <cstdint>

#include <string>
#include <iostream>
#include "../Environment/CommonDialogState.hpp"
#include "../Environment/CommonDialogResult.hpp"


namespace Sce::Pss::Core::Device {
	using namespace Sce::Pss::Core::Environment;

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
