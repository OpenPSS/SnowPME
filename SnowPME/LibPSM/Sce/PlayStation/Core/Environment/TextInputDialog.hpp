#ifndef LIB_PSM_TEXTINPUTDIALOG_H
#define LIB_PSM_TEXTINPUTDIALOG_H 1

#include <string>
#include <iostream>
#include "CommonDialogType.hpp"
#include "CommonDialogResult.hpp"
#include "CommonDialogState.hpp"
#include "TextInputMode.hpp"


namespace Sce::PlayStation::Core::Environment {
	typedef struct Arguments
	{
		TextInputMode mode;
		std::string text;
	} Arguments;

	typedef struct Results
	{
		std::string text;
	} Results;

	class TextInputDialog {
	public:

		static int NewNative(CommonDialogType type, int *handle);
		static int ReleaseNative(CommonDialogType type, int handle);
		static int OpenNative(CommonDialogType type, int handle, Arguments *arguments);
		static int AbortNative(CommonDialogType type, int handle);
		static int GetState(CommonDialogType type, int handle, CommonDialogState *state);
		static int GetResult(CommonDialogType type, int handle, CommonDialogResult *result, Results *results);
	};
}
#endif
