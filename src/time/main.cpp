/* SPDX-License-Identifier: MIT */

#include <infos.h>

int main(const char *cmdline)
{
	if (!cmdline || strlen(cmdline) == 0) {
		return 1;
	}

	const char *cmd = cmdline;
	char prog[64];
	int n = 0;
	while (*cmd && *cmd != ' ' && n < 63) {
		prog[n++] = *cmd++;
	}
	prog[n] = 0;

	if (*cmd) cmd++;

	uint64_t start = get_ticks();

	HPROC pcmd = exec(prog, cmd);
	if (is_error(pcmd)) {
		printf("error: unable to run command '%s' %s\n", cmdline, cmd);
	} else {
		wait_proc(pcmd);

		uint64_t end = get_ticks();
		uint64_t delta = end - start;
		printf("real time: %lu ms\n", delta/1000);
	}

	return 0;
}
