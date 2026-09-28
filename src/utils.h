#ifndef UTILS_H
#define UTILS_H

#include "config.h"     /* Includes access to global resources */


/**
 * @brief       Prints the header of the results table in markdown.
 *
 * @details     Outputs the threshold for the tests, then the column names
 *              for size, average cycles, and cache hit rate.
 *
 * @param[in]   threshold   The threshold the test was measured at.
 */
extern void
print_header(int threshold);


/**
 * @brief       Prints a row in the results table in markdown.
 *
 * @details     Outputs the size in KB, the average cycles, and cache hit rate.
 *
 * @param[in]   region     The region in KB of the current test size.
 * @param[in]   block      The block of cache lines being tested.
 * @param[in]   cache_hits The count of cache hits.
 * @param[in]   total_time The total time, CPU cycles it took to access.
 */
extern void
print_results(size_t region, size_t block, int cache_hits, uint64_t total_time);


/**
 * @brief       Prints the data in CSV format.
 *
 * @param[in]   region     The region in KB of the current test size.
 * @param[in]   block      The block of cache lines being tested.
 * @param[in]   cache_hits The count of cache hits.
 * @param[in]   total_time The total time, CPU cycles it took to access.
 */
extern void
print_csv(size_t region, size_t block, int cache_hits, uint64_t total_time);

#endif