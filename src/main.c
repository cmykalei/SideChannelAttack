#include "config.h"     /* Access to global configs */
#include "utils.h"      /* Printing output */
#include "mem.h"        /* Handling memory of test regions */
#include "probe.h"      /* Probing victim for measurements */


/**
 * @brief       Entry point.
 *
 * @details     Demonstrates LLC side-channel attack to infer the size LLC on a
 *              system by comparing the cache and main memory acccess times.
 */
int
main(void)
{
    /* Allocate array for test region */
    volatile uint8_t *victim = malloc(TEST_SIZE);
    if (victim == NULL)
    {
        printf("Failed to allocate victim memory.\n");
        return 1;
    }

    /* Allocate a large buffer for eviction */
    volatile uint8_t *buffer = malloc(TEST_SIZE);
    if (buffer == NULL)
    {
        printf("Failed to allocate buffer memory.\n");
        free((void *)victim);
        return 1;
    }

    probe_cpu_seed(); /* Get hardware generated seed */

    /* Calculate the threshold for measurement */
    int threshold = probe_cpu_threshold(victim, TEST_SIZE);
    print_header(threshold); /* This is just for my md tables */

    /* Iterate over increasing memory region sizes */
    for (size_t region = PAGE_SIZE; region <= TEST_SIZE; region *= 2)
    {
        size_t block = region / CACHE_LINE_SIZE;
        uint64_t total_time = 0;
        int cache_hits = 0;

        /* Get indices of the test region to access */
        size_t *indices = malloc(block * sizeof(size_t));
        if (indices == NULL)
        {
            printf("Failed to allocate indices.\n");
            free((void *)victim);
            free((void *)buffer);
            return 1;
        }

        /* Shuffle the indices for random access */
        mem_shuffle_indices(indices, block);

        /* Prime the victim test region into cache */
        mem_load_victim(victim, region);

        /* Evict the test region by accessing a large buffer */
        mem_evict_buffer(buffer);

        /* Start repeatedly measuring access times */
        for (int round = 0; round < MAX_ROUNDS + WARMUP; round++)
        {
            /* Iterate over each cache line in the array */
            for (size_t line = 0; line < block; line++)
            {
                /* Calculate cycles from measured access time */
                uint64_t cycles = probe_access_time(&victim[indices[line]]);

                /* Measure results if after warm up */
                if (round >= WARMUP)
                {
                    total_time += cycles;

                    /* Record a cache hit if under the threshold */
                    if (cycles < threshold)
                    {
                        cache_hits++;
                    }
                }
            }
        }

        /* Clean up indices and print results */
        free(indices);
        print_results(region, block, cache_hits, total_time);
        //print_csv(region, block, cache_hits, total_time);
    }

    /* Clean up */
    free((void *)victim);
    free((void *)buffer);

    return 0;
}
