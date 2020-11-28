#ifndef PROFILER_H
#define PROFILER_H
#include <stdint.h>
#include <stdbool.h>

#include "porfiler_settings.h"

#define NO_TRACE __attribute__((no_instrument_function))

struct profiler_event
{
    void *function_address;
    void *caller;
    uint64_t time_us;
    uint32_t thread;
    bool enter;
};

struct profiler_interface
{
    uint64_t (*current_time_us)(void);
    bool (*send_events)(struct profiler_event* events, uint32_t number_of_events);
    uint32_t (*thread_id)(void);
    void (*calibrate_profiler)(void);
};

void __cyg_profile_func_enter(void *this_fn, void *call_site)NO_TRACE;
void __cyg_profile_func_exit(void *this_fn, void *call_site)NO_TRACE;

void profiler_init(struct profiler_interface* interface) NO_TRACE;
void profiler_process();
#endif // PROFILER_H