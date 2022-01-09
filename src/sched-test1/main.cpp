/* SPDX-License-Identifier: MIT */

#include <infos.h>

static volatile bool terminate;

static void thread_proc(void *arg)
{
	unsigned int thread_num = (unsigned int)(unsigned long)arg;

	char name_buffer[16] = {0};
	sprintf(name_buffer, "thread/%d", thread_num);
	set_thread_name(HTHREAD_SELF, name_buffer);

	printf("Thread %d Running!\n", thread_num);

	usleep(1500000 + (thread_num * 500000));

	printf("Thread %d Stopping!\n", thread_num);

	stop_thread(HTHREAD_SELF);
}

static void ticker1_thread_proc(void *arg)
{
    printf("Thread 1 ticking every 1.5s\n");
    while (!terminate) {
        printf("TICK 1!\n");
        usleep(1500000);
    }

    stop_thread(HTHREAD_SELF);
}

static void ticker2_thread_proc(void *arg)
{
    printf("Thread 2 ticking every 1s\n");
    while (!terminate) {
        printf("TICK 2!\n");
        usleep(1000000);
    }

    stop_thread(HTHREAD_SELF);
}

static void terminate_ticker_thread_proc(void *arg)
{
    printf("Press <ENTER> to stop\n");
    while (getch() != '\n');
    printf("Stopping threads...\n");
    terminate = true;

    stop_thread(HTHREAD_SELF);
}

static void fibonacci_thread_proc(void *arg) {
    int f1 = 0;
    int f2 = 1;
    int fi;
    for (int i = 0; i < 500; i++) {
        fi = f1 + f2;
        f1 = f2;
        f2 = fi;
        printf("F%u: %u\n", i, fi);
    }
}

int main(const char *cmdline)
{
	printf("Running Scheduler Test!\n");

    terminate = false;

    HTHREAD threads[14];
	printf("Using %d threads...\n", ARRAY_SIZE(threads));
	for (unsigned int i = 0; i < 10; i++) {
		threads[i] = create_thread(thread_proc, (void *)(unsigned long)i, SchedulingEntityPriority::REALTIME);
	}

    threads[10] = create_thread(terminate_ticker_thread_proc, nullptr, SchedulingEntityPriority::INTERACTIVE);
    threads[11] = create_thread(ticker1_thread_proc, nullptr, SchedulingEntityPriority::INTERACTIVE);
    threads[12] = create_thread(ticker2_thread_proc, nullptr, SchedulingEntityPriority::INTERACTIVE);

    threads[13] = create_thread(fibonacci_thread_proc, nullptr, SchedulingEntityPriority::DAEMON);

	for (unsigned int i = 0; i < ARRAY_SIZE(threads); i++) {
		printf("Waiting for thread %d...\n", i);
		join_thread(threads[i]);
	}

	printf("Scheduler Test Complete\n");

	return 0;
}
