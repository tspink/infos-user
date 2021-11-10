/* SPDX-License-Identifier: MIT */

#include <infos.h>

extern int infos_main(const char *cmdline);

extern "C"
{
	void _start(const char *cmdline)
	{
		exit(infos_main(cmdline));
	}

	void __stack_chk_fail()
	{
		exit(1);
	}
}
