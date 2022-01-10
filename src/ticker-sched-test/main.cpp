/* SPDX-License-Identifier: MIT */

#include <infos.h>

static volatile bool terminate;

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

int main(const char *cmdline)
{
    printf("Running scheduler test with tickers!\n");

    terminate = false;

    HTHREAD ticker1, ticker2;
    ticker1 = create_thread(ticker1_thread_proc, nullptr);
    ticker2 = create_thread(ticker2_thread_proc, nullptr);

    printf("Press <ENTER> to stop\n");
    while (getch() != '\n');
    printf("Stopping threads...\n");
    terminate = true;

    join_thread(ticker1);
    join_thread(ticker2);

    printf("Scheduler test complete!\n");

    return 0;
}