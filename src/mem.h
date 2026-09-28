#ifndef MEM_H
#define MEM_H

#include "config.h"     /* Includes access to global resources */


/**
 * @brief       Loads the victim region of memory into cache.
 *
 * @details     Reads each line from the array so the CPU caches it.
 *              This primes the test region, which will be accessed later on
 *              to measure access time, revealing whether it's still in cache
 *              or has been evicted.
 *
 * @param[in]   victim      Pointer to the victim array, the target to measure.
 * @param[in]   region      Size in bytes of the test region to prime.
 */
extern void
mem_load_victim(volatile uint8_t *victim, size_t region);


/**
 * @brief       Evicts a region of memory from the cache.
 *
 * @details     Fills the cache by accessing a large buffer, forcing out the
 *              victim's data into main memory. This makes access time slower,
 *              which reveals when the victim's data has gone to main memory.
 *
 * @param[in]   buffer      Pointer to the eviction buffer.
 */
extern void
mem_evict_buffer(volatile uint8_t *buffer);


/**
 * @brief       Shuffles a set of indices given by the size of a test region.
 *
 * @details     Uses _rdrand32_step() to select each next index to swap.
 *              This provides random access to the victim region to avoid CPU
 *              optimizations that could skew measurements.
 *
 * @param[in]   block       The length of the array, the current block size.
 * @param[in]   indices     Pointer to the array of indices to shuffle.
 */
extern void
mem_shuffle_indices(size_t *indices, size_t block);

#endif
