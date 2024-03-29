/* SPDX-License-Identifier: MIT */

#include <infos.h>

HPROC exec(const char *program, const char *args)
{
	return (HPROC)syscall(Syscall::SYS_EXEC, (unsigned long)program, (unsigned long)args);
}

void wait_proc(HPROC proc)
{
	syscall(Syscall::SYS_WAIT_PROC, proc);
}

HTHREAD create_thread(ThreadProc tp, void *arg, SchedulingEntityPriority priority)
{
    return (HTHREAD)syscall(Syscall::SYS_CREATE_THREAD, (unsigned long)tp, (unsigned long)arg, (unsigned long)priority);
}

void stop_thread(HTHREAD thread)
{
	syscall(Syscall::SYS_STOP_THREAD, thread);
}

void join_thread(HTHREAD thread)
{
	syscall(Syscall::SYS_JOIN_THREAD, thread);
}

void set_thread_name(HTHREAD thread, const char *name)
{
	syscall(Syscall::SYS_SET_THREAD_NAME, thread, (unsigned long)name);
}

void usleep(unsigned long us)
{
	syscall(Syscall::SYS_USLEEP, us);
}
