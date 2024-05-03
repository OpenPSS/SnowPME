#ifndef MONO_H
#define MONO_H 1

#ifdef __cplusplus
extern "C" {
#endif

#include <mono/metadata/appdomain.h>
#include <mono/metadata/mono-config.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/mono-gc.h>
#include <mono/metadata/threads.h>
#include <mono/metadata/threadpool.h>
#include <mono/metadata/file-io-pss.h>
#include <mono/metadata/profiler.h>
#include <mono/metadata/mono-debug.h>
#include <mono/metadata/tabledefs.h>

#include <mono/jit/jit.h>
#include <mono/utils/mono-counters.h>

#ifdef __cplusplus
}
#endif
#endif