#ifndef PROBE_H
#define PROBE_H

#include "config.h"     /* Includes access to global resources */


/**
 * @brief      Sets a global a random seed from the CPU.
 *
 * @details    Provides a hardware generated random seed using the instruction
 *              _rdrand32_step() supported by the target CPU.
 */
extern void
probe_cpu_seed(void);


/**
 * @brief       Measures the time it takes to access a given address.
 *
 * @details     Uses the __rdtscp() instruction, supported by the target CPU,
 *              to get the timestamp counter before and after access.
 *
 * @param[in]   addr    Pointer to the address to access.
 * @return      The number of CPU cycles taken to access the address.
 */
extern uint64_t
probe_access_time(volatile uint8_t *addr);


/**
 * @brief       Calculates the threshold to distinguish cache hits.
 *
 * @details     Measures access time for cache hits by accesssing data from the
 *              victim array immediately after loading. Then measures the access
 *              time for cache misses by attempting to access the data
 *              immediately after flushing.
 *
 *              Uses the instruction _mm_clflushopt() supported by the target
 *              CPU. The threshold is given by the average of total cycles for
 *              cache-hits and total cycles for cache-misses, with respect
 *              to the specified SAMPLE_SIZE set in configurations.
 *
 * @param[in]   victim      Pointer to the victim array, the target to measure.
 * @param[in]   region      Size in bytes of the test region to probe.
 * @return      The estimated threshold of CPU cycles for cache hits.
 */
extern int
probe_cpu_threshold(volatile uint8_t* victim, size_t region);

#endif
