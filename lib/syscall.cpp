/* SPDX-License-Identifier: MIT */

#include <infos.h>

unsigned long syscall(Syscall nr)
{
	unsigned long ret;
	
	asm volatile("int $0x81" : "=a"(ret) : "a"((unsigned long)nr) : "rcx", "r11");
	
	return ret;
}

unsigned long syscall(Syscall nr, unsigned long a1)
{
	unsigned long ret;
	
	asm volatile("int $0x81" : "=a"(ret) : "a"((unsigned long)nr), "D"(a1) : "rcx", "r11");
	
	return ret;
}

unsigned long syscall(Syscall nr, unsigned long a1, unsigned long a2)
{
	unsigned long ret;
	
	asm volatile("int $0x81" : "=a"(ret) : "a"((unsigned long)nr), "D"(a1), "S"(a2) : "rcx", "r11");
	
	return ret;
}

unsigned long syscall(Syscall nr, unsigned long a1, unsigned long a2, unsigned long a3)
{
	unsigned long ret;
	
	asm volatile("int $0x81" : "=a"(ret) : "a"((unsigned long)nr), "D"(a1), "S"(a2), "d"(a3) : "rcx", "r11");
	
	return ret;
}
