#include <stdbool.h>
#include <string.h>

#include "profiler.h"

struct profiler_ctx
{
    bool initialized;
    struct profiler_interface interface;
    struct profiler_event events[EVENT_BUFFOR_SIZE];
    uint32_t event_id;
};

static struct profiler_ctx ctx;

NO_TRACE
void __cyg_profile_func_enter(void *this_fn, void *call_site)
{
    if (call_site == __cyg_profile_func_enter || call_site == __cyg_profile_func_exit)
        return;
    
    if (ctx.initialized)
    {
        if (ctx.event_id < EVENT_BUFFOR_SIZE)
        {
            ctx.events[ctx.event_id++] = (struct profiler_event){
            .enter = true, 
            .function_address = this_fn,
            .time_us = ctx.interface.current_time_us(), 
            .caller = call_site,
            .thread = ctx.interface.thread_id()
            };
        }
        #if PROFILER_AUTO_PROCESS
        if (ctx.event_id == EVENT_BUFFOR_SIZE)
            profiler_process();
        #endif
    }
}

NO_TRACE
void __cyg_profile_func_exit(void *this_fn, void *call_site)
{
    if (call_site == __cyg_profile_func_enter || call_site == __cyg_profile_func_exit)
            return;

    if (ctx.initialized)
    {
        if (ctx.event_id < EVENT_BUFFOR_SIZE)
        {
            ctx.events[ctx.event_id++] = (struct profiler_event){
            .enter = false, 
            .function_address = this_fn,
            .time_us = ctx.interface.current_time_us(), 
            .caller = call_site,
            .thread = ctx.interface.thread_id()
            };
        }
        #if PROFILER_AUTO_PROCESS
        if (ctx.event_id == EVENT_BUFFOR_SIZE)
            profiler_process();
        #endif
    }
}

//////////////
NO_TRACE
void profiler_init(struct profiler_interface* interface)
{
    if (interface == NULL)
        return;

    // TODO RG: check if interface is valid

    interface->calibrate_profiler();
    ctx.interface = *interface;
    ctx.event_id = 0;
    ctx.initialized = true;
}

void profiler_process(void)
{
    if (ctx.interface.send_events(ctx.events, ctx.event_id))
    {
        ctx.event_id = 0;
    }
}