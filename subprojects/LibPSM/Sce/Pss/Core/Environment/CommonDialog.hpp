#ifndef LIB_PSS_COMMONDIALOG_H
#define LIB_PSS_COMMONDIALOG_H 1
#include <cstdint>

#include <string>
#include <iostream>

#include <Sce/Pss/Core/PsmObject.hpp>
#include <Sce/Pss/Core/Environment/CommonDialogType.hpp>
#include <Sce/Pss/Core/Environment/CommonDialogArguments.hpp>
#include <Sce/Pss/Core/Environment/CommonDialogResults.hpp>
#include <Sce/Pss/Core/Environment/CommonDialogResult.hpp>
#include <Sce/Pss/Core/Environment/CommonDialogState.hpp>


namespace Sce::Pss::Core::Environment {
	class CommonDialog : public PsmObject<CommonDialog> {
	protected:
		CommonDialogState state = CommonDialogState::None;
		CommonDialogResult result = CommonDialogResult::OK;
		bool aborted = false;
	public:
		virtual int Open(CommonDialogArguments* cmdArg) = 0;
		virtual int Abort();
		virtual int State(CommonDialogState* state);
		virtual int Result(CommonDialogResult* result, CommonDialogResults* results) = 0;

		static int NewNative(CommonDialogType type, int* handle);
		static int ReleaseNative(CommonDialogType type, int handle);
		static int OpenNative(CommonDialogType type, int handle, CommonDialogArguments* cmdArg);
		static int AbortNative(CommonDialogType type, int handle);
		static int GetState(CommonDialogType type, int handle, CommonDialogState* state);
		static int GetResult(CommonDialogType type, int handle, CommonDialogResult* result, CommonDialogResults* results);
	};
}
#endif
