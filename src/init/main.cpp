/* SPDX-License-Identifier: MIT */

#include <infos.h>

int main(const char *cmdline)
{
	printf("\33\x0eWelcome to InfOS!\n\33\x07Starting the system...\n");

	while (true) {
		HPROC shell_proc = exec("/usr/shell", NULL);
		if (is_error(shell_proc)) {
			printf("Error: Unable to launch shell");
			return 1;
		}

		wait_proc(shell_proc);

		printf("SHELL TERMINATED!  PRESS ENTER TO RESTART\n");
		while (getch() != '\n');
	}

	return 0;
}
