#ifndef LIB_PSM_INAPPPURCHASEDIALOG_H
#define LIB_PSM_INAPPPURCHASEDIALOG_H 1
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "InAppPurchaseCommand.hpp"
#include "InAppPurchaseProductData.hpp"
#include "../Environment/CommonDialogState.hpp"
#include "../Environment/CommonDialogResult.hpp"
using namespace Sce::PlayStation::Core::Environment;
using namespace std;

namespace Sce::PlayStation::Core::Services {
	class InAppPurchaseDialog {
	private:
		typedef struct CommandArguments
		{
			InAppPurchaseCommand Command;
			int* Arguments;
		} CommandArguments;

		typedef struct CommandResults
		{
			InAppPurchaseCommand Command;
			int InfoStatus;
			int Count;
			InAppPurchaseProductData* Results;
		} CommandResults;
	public:
		static int NewNative(int type, int *handle);
		static int ReleaseNative(int type, int handle);
		static int OpenNative(int type, int handle, CommandArguments *cmdArg);
		static int AbortNative(int type, int handle);
		static int GetState(int type, int handle, CommonDialogState *state);
		static int GetResult(int type, int handle, CommonDialogResult *result, CommandResults *results);
	};
}
#endif
