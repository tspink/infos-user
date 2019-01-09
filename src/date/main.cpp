/* SPDX-License-Identifier: MIT */

#include <infos.h>

int main(const char *cmdline)
{
	struct tod t;
	
	int rc = get_time_of_day(&t);
	if (rc) {
		printf("error: unable to get time of day: %d\n", rc);
		return rc;
	}
	
	printf("the current date & time is: %04u/%04u/%04u\n", t.day_of_month, t.month, t.year);
	return 0;
}
