#ifndef _MONO_THREADPOOL_H_
#define _MONO_THREADPOOL_H_

#include <mono/metadata/object.h>
#include <mono/metadata/reflection.h>

/* No managed code here */
void mono_thread_pool_init (void);

void icall_append_job (MonoObject *ar) ;
void icall_append_io_job (MonoObject *target, void *state) ;
void * mono_thread_pool_add     (MonoObject *target, void *msg, MonoDelegate *async_callback, MonoObject *state) ;

MonoObject * mono_thread_pool_finish (void*ares, MonoArray **out_args, MonoObject **exc);

void mono_thread_pool_cleanup (void);

bool mono_thread_pool_remove_domain_jobs (MonoDomain *domain, int timeout);

void
ves_icall_System_Threading_ThreadPool_GetAvailableThreads (int *workerThreads,
							   int *completionPortThreads);

void
ves_icall_System_Threading_ThreadPool_GetMaxThreads (int *workerThreads,
						     int *completionPortThreads);

void
ves_icall_System_Threading_ThreadPool_GetMinThreads (int *workerThreads, 
								int *completionPortThreads) ;

MonoBoolean
ves_icall_System_Threading_ThreadPool_SetMinThreads (int workerThreads, 
								int completionPortThreads) ;

MonoBoolean
ves_icall_System_Threading_ThreadPool_SetMaxThreads (int workerThreads, 
								int completionPortThreads) ;

typedef void  (*MonoThreadPoolFunc) (uintptr_t user_data);
void mono_install_threadpool_thread_hooks (MonoThreadPoolFunc start_func, MonoThreadPoolFunc finish_func, uintptr_t user_data);

typedef void  (*MonoThreadPoolItemFunc) (uintptr_t user_data);
void mono_install_threadpool_item_hooks (MonoThreadPoolItemFunc begin_func, MonoThreadPoolItemFunc end_func, uintptr_t user_data);

void mono_threadpool_set_max_threads (int tp_max, int io_max);
#endif

