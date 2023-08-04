#ifndef LIB_PSM_ACTION_H
#define LIB_PSM_ACTION_H 1
#include <mono/mono.h>
#include <Sce/PlayStation/Core/Environment/ActionType.hpp>

typedef struct Action
{
	ActionType type;
	MonoString* parameter0;
	MonoString* parameter1;
	MonoString* parameter2;
	MonoString* parameter3;
} Action;

#endif