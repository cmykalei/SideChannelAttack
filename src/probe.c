#include "probe.h"


void
probe_cpu_seed(void)
{
    unsigned int seed;
    if (_rdseed32_step(&seed) == 0)
    {
        seed = (unsigned int)time(NULL);
    }

    srand(seed);
}


uint64_t
probe_access_time(volatile uint8_t *addr)
{
    unsigned int dummy_time;
    uint64_t actual_time = __rdtscp(&dummy_time);
    volatile uint8_t junk = *addr;

    return __rdtscp(&dummy_time) - actual_time;
}


int
probe_cpu_threshold(volatile uint8_t* victim, size_t region)
{
    uint64_t time_hit = 0;
    uint64_t time_miss = 0;

    /* Measure cache-hit access times */
    for (int i = 0; i < SAMPLE_SIZE; i++)
    {
        uint32_t r;
        _rdrand32_step(&r);
        size_t cache_lines = region / CACHE_LINE_SIZE;
        int index = r % cache_lines;
        volatile uint8_t *addr = &victim[index * CACHE_LINE_SIZE];

        //_mm_clflush((void *)addr);
        _mm_clflushopt((void *)addr);       /* Flush to reset slot */
        _mm_mfence();
        (void)*addr;                        /* Read to load into cache */

        time_hit += probe_access_time(addr);
    }

    /* Measure cache-miss access times */
    for (int i = 0; i < SAMPLE_SIZE; i++)
    {
        uint32_t r;
        _rdrand32_step(&r);
        size_t cache_lines = region / CACHE_LINE_SIZE;
        int index = r % cache_lines;
        volatile uint8_t *addr = &victim[index * CACHE_LINE_SIZE];

        //_mm_clflush((void *)addr);
        _mm_clflushopt((void *)addr);       /* Flush before access */
        _mm_mfence();

        time_miss += probe_access_time(addr);
    }

    time_hit /= SAMPLE_SIZE;
    time_miss /= SAMPLE_SIZE;

    return (time_hit + time_miss) / 2;
}
