/* SPDX-License-Identifier: MIT */

#include <infos.h>

int main(const char *cmdline)
{
	if (!cmdline || strlen(cmdline) == 0) {
		return 1;
	}

	uint64_t start = get_ticks();

	HPROC pcmd = exec(cmdline, "");
	if (is_error(pcmd)) {
		printf("error: unable to run command '%s'\n", cmdline);
	} else {
		wait_proc(pcmd);

		uint64_t end = get_ticks();
		uint64_t delta = end - start;
		printf("real time: %lu ns\n", delta);
	}

	return 0;
}
