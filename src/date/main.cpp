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
	
	printf("the current system date & time is: %02u/%02u/%u %02u:%02u:%02u\n", t.day_of_month, t.month, t.year, t.hours, t.minutes, t.seconds);
	
	HFILE rtc_device = open("/dev/cmos-rtc0", 0);
	if (is_error(rtc_device)) {
		printf("unable to open rtc device\n");
		return 1;
	}
	
	read(rtc_device, (char *)&t, sizeof(t));
	close(rtc_device);
	
	printf("the current hardware date & time is: %02u/%02u/%u %02u:%02u:%02u\n", t.day_of_month, t.month, t.year, t.hours, t.minutes, t.seconds);
	return 0;
}
