#ifndef LIB_PSS_COMMANDRESULTS_H
#define LIB_PSS_COMMANDRESULTS_H 1
#include <Sce/Pss/Core/Services/InAppPurchaseCommand.hpp>
#include <Sce/Pss/Core/Services/InAppPurchaseProductData.hpp>
#include <mono/mono.h>

namespace Sce::Pss::Core::Services {
	typedef struct CommandResults
	{
		InAppPurchaseCommand Command;
		int InfoStatus;
		int Count;
		MonoArray* Results;
	} CommandResults;
}

#endif