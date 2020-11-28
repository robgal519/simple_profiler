#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <stdbool.h>

#include "profiler.h"
#include "profiler_interface_provider.h"

//////////////////////////

void delay(int milli_seconds)
{

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}

void foo()
{
    delay(100);
}

int main()
{

    profiler_init(profiler_get_interface());

    int i = 5;
    while (i--)
    {
        foo();
    }
    profiler_process();
}