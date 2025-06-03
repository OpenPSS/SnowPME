#ifndef LIB_PSS_COMMANDARGUMENTS_H
#define LIB_PSS_COMMANDARGUMENTS_H 1
#include <Sce/Pss/Core/Services/InAppPurchaseCommand.hpp>
#include <Sce/Pss/Core/Environment/CommonDialogArguments.hpp>

#define MONO_ZERO_LEN_ARRAY 1
#include <mono/mono.h>
namespace Sce::Pss::Core::Services {
	typedef struct InAppPurchaseCommandArguments : Environment::CommonDialogArguments
	{
		InAppPurchaseCommand Command;
		MonoArray* Arguments;
	} InAppPurchaseCommandArguments;
}

#endif
