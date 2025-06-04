#ifndef LIB_PSS_ACTION_H
#define LIB_PSS_ACTION_H 1

#include <mono/mono.h>
#include <Sce/Pss/Core/Environment/ActionType.hpp>

typedef struct Action
{
	ActionType type;
	MonoString* parameter0;
	MonoString* parameter1;
	MonoString* parameter2;
	MonoString* parameter3;
} Action;

#endif