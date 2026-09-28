#include "utils.h"


void
print_header(int threshold)
{
    printf("\n## LLC Discovery (%d threshold)\n", threshold);
    printf("| Size (KB) | Cycles | Cache Hit |\n");
    printf("| :-------- | -----: | --------: |\n");
}


void
print_results(size_t region, size_t block, int cache_hits, uint64_t total_time)
{
    int rounds = (int)(block * MAX_ROUNDS);
    int avg_cycles = (int)total_time / rounds;
    float hit_rate = (float)cache_hits / (float)rounds * 100.0f;
    int test_region = (int)region / KB;
    printf("| %6d KB | %6d | %7.1f %% |\n",test_region, avg_cycles, hit_rate);
}


void
print_csv(size_t region, size_t block, int cache_hits, uint64_t total_time)
{
    int rounds = (int)(block * MAX_ROUNDS);
    int avg_cycles = (int)total_time / rounds;
    int test_region = (int)region / KB;
    float hit_rate = (float)cache_hits / (float)rounds * 100.0f;
    printf("%d,%d,%.1f\n",test_region, avg_cycles, hit_rate);
}
