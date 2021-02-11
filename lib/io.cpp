/* SPDX-License-Identifier: MIT */

#include <infos.h>

HFILE open(const char *file, int flags)
{
	return (HFILE)syscall(Syscall::SYS_OPEN, (unsigned long)file, (unsigned long)flags);
}

void close(HFILE file)
{
	syscall(Syscall::SYS_CLOSE, (unsigned long)file);
}

int read(HFILE file, char *buffer, size_t size)
{
	return (int)syscall(Syscall::SYS_READ, (unsigned long)file, (unsigned long)buffer, (unsigned long)size);
}

int write(HFILE file, const char *buffer, size_t size)
{
	return (int)syscall(Syscall::SYS_WRITE, (unsigned long)file, (unsigned long)buffer, (unsigned long)size);
}

int pread(HFILE file, char *buffer, size_t size, off_t off)
{
	return (int)syscall(Syscall::SYS_PREAD, (unsigned long)file, (unsigned long)buffer, (unsigned long)size, (unsigned long)off);
}

int pwrite(HFILE file, const char *buffer, size_t size, off_t off)
{
	return (int)syscall(Syscall::SYS_PWRITE, (unsigned long)file, (unsigned long)buffer, (unsigned long)size, (unsigned long)off);
}

HDIR opendir(const char *path, int flags)
{
	return (HDIR)syscall(Syscall::SYS_OPENDIR, (unsigned long)path, (unsigned long)flags);
}

int readdir(HDIR dir, struct dirent *de)
{
	return (int)syscall(Syscall::SYS_READDIR, (unsigned long)dir, (unsigned long)de);
}

void closedir(HDIR dir)
{
	syscall(Syscall::SYS_CLOSEDIR, (unsigned long)dir);
}

int get_time_of_day(struct tod *t)
{
	return (int)syscall(Syscall::SYS_GET_TOD, (unsigned long)t);
}

uint64_t get_ticks()
{
	return (uint64_t)syscall(Syscall::SYS_GET_TICKS);
}
