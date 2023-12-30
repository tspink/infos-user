/* SPDX-License-Identifier: MIT */

#include <infos.h>

extern int main(const char *cmdline);

HFILE __console_handle;

void infos_main(const char *cmdline)
{
    __console_handle = open("/dev/tty0", 0);
    if (is_error(__console_handle))
        exit(1);

    int rc = main(cmdline);
    close(__console_handle);
    exit(rc);
}
