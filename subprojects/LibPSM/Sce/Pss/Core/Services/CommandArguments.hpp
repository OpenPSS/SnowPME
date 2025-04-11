#ifndef LIB_PSS_COMMANDARGUMENTS_H
#define LIB_PSS_COMMANDARGUMENTS_H 1
#include <Sce/Pss/Core/Services/InAppPurchaseCommand.hpp>
#include <mono/mono.h>
namespace Sce::Pss::Core::Services {
	typedef struct CommandArguments
	{
		InAppPurchaseCommand Command;
		MonoArray* Arguments;
	} CommandArguments;
}

#endif
