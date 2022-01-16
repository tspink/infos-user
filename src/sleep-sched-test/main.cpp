/* SPDX-License-Identifier: MIT */

#include <infos.h>

static void sleep_thread_proc(void *arg)
{
    unsigned int thread_num = (unsigned int)(unsigned long)arg;

    char name_buffer[16] = {0};
    sprintf(name_buffer, "thread/%d", thread_num);
    set_thread_name(HTHREAD_SELF, name_buffer);

    printf("Thread %d running!\n", thread_num);

    usleep(1500000 + (thread_num * 500000));

    printf("Thread %d stopping!\n", thread_num);

    stop_thread(HTHREAD_SELF);
}

int main(const char *cmdline)
{
    printf("Running scheduler test with sleeping threads!\n");

    HTHREAD threads[10];
    printf("Using %d threads...\n", ARRAY_SIZE(threads));
    for (unsigned int i = 0; i < ARRAY_SIZE(threads); i++) {
        threads[i] = create_thread(sleep_thread_proc, (void *)(unsigned long)i);
    }

    for (unsigned int i = 0; i < ARRAY_SIZE(threads); i++) {
        printf("Waiting for thread %d...\n", i);
        join_thread(threads[i]);
    }

    printf("Scheduler test complete!\n");

    return 0;
}