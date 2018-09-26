/* SPDX-License-Identifier: MIT */

#include <infos.h>

static void thread_proc(void *arg)
{
	unsigned int thread_num = (unsigned int)(unsigned long)arg;
	
	printf("Thread %d Running!\n", thread_num);
	
	usleep(1500000 + (thread_num * 500000));
	
	printf("Thread %d Stopping!\n", thread_num);
	
	stop_thread(HTHREAD_SELF);
}

int main(const char *cmdline)
{
	printf("Running Scheduler Test!\n");
	
	HTHREAD threads[10];
	for (unsigned int i = 0; i < ARRAY_SIZE(threads); i++) {
		threads[i] = create_thread(thread_proc, (void *)(unsigned long)i);
	}

	for (unsigned int i = 0; i < ARRAY_SIZE(threads); i++) {
		printf("Waiting for thread %d...\n", i);
		join_thread(threads[i]);
	}
	
	printf("Scheduler Test Complete\n");
	
	return 0;
}
