
#include <profiler.h>
#include <profiler_interface_provider.h>
#include <time.h>
#include <stdio.h>

/**
 * Treat this file as an example.
 * implement those functions as you like. 
 * Keep in mind to make them as short as possible because those functions will be called in before every measured function.
 */ 

static bool send_events(struct profiler_event* events, uint32_t number_of_events)
{
    for (uint32_t i = 0; i < number_of_events; i ++)
    {// Thread; enter[T]/exit[F]; Function; Caller; Time
        printf("%d;%d;%p;%p;%ld;\n", events[i].thread, events[i].enter, events[i].function_address, events[i].caller, events[i].time_us);
    }
    return true;
}

static uint64_t long_clock(void)
{
    return clock()*1000;
}

static uint32_t thread_id(void)
{
    return 0;
}

static void calibrate(void)
{
    printf("profiler_init;%p\n",profiler_init);
}

static struct profiler_interface interface = 
{
    .current_time_us = long_clock,
    .send_events = send_events,
    .thread_id = thread_id,
    .calibrate_profiler = calibrate,
};

////////////////////////////////////////////////////////

struct profiler_interface* profiler_get_interface(void)
{
    return &interface;
}


