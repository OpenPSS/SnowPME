/*
 * environment.h: System.Environment support internal calls
 *
 * Author:
 *	Dick Porter (dick@ximian.com)
 *
 * (C) 2002 Ximian, Inc
 */

#ifndef _MONO_METADATA_ENVIRONMENT_H_
#define _MONO_METADATA_ENVIRONMENT_H_

#include <mono/utils/mono-publib.h>

MONO_BEGIN_DECLS

typedef int (*MonoExitCallback) (int);

void mono_exit (int code);
void mono_set_exit_callback (MonoExitCallback cb);

extern int32_t mono_environment_exitcode_get (void);
extern void mono_environment_exitcode_set (int32_t value);

MONO_END_DECLS

#endif /* _MONO_METADATA_ENVIRONMENT_H_ */
