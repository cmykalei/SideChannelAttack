#ifndef CONFIG_H
#define CONFIG_H

/*
 * Include Standard C libraries.
 */
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* malloc, free, rand, srand */
#include <stdint.h>     /* unint8_t, unint32_t, uint64_t, size_t */
#include <inttypes.h>   /* PRIu64 (format for integers) */
#include <time.h>       /* time */

/*
 * Include CPU instrinsic headers.
 */
#include <x86intrin.h>  /* _mm_clflushopt(), _rdrand32_step(), __rdtscp() */
#include <emmintrin.h>  /* _mm_si128(), _mm_store_si128(), _mm_add_epi32() */
#include <immintrin.h>  /* _mm256_si256(), _mm256_store_si256(), _mm256_add_epi32() */

/*
 * Define constants for test configuration.
 */
#define KB                  (1024)
#define CACHE_LINE_SIZE     (64)
#define PAGE_SIZE           (4096)
#define TEST_SIZE           (CACHE_LINE_SIZE * KB * KB)
#define SAMPLE_SIZE         (1000)
#define MAX_ROUNDS          (5)
#define WARMUP              (5)

#endif
