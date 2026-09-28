#include "mem.h"


void
mem_load_victim(volatile uint8_t *victim, size_t region)
{
    for (size_t line = 0; line < region; line += CACHE_LINE_SIZE)
    {
       volatile uint8_t junk = victim[line];
       victim[line] = junk;
    }
    _mm_mfence();
}


void
mem_evict_buffer(volatile uint8_t *buffer)
{
    for (size_t line = 0; line < TEST_SIZE; line += CACHE_LINE_SIZE)
    {
        buffer[line] = 1;
    }
    _mm_mfence();
}


void
mem_shuffle_indices(size_t *indices, size_t block)
{
    for (int i = 0; i < block; i++)
    {
        indices[i] = i * CACHE_LINE_SIZE;
    }

    for (int i = block - 1; i > 0; i--)
    {
        uint32_t j;
        _rdrand32_step(&j);
        j = j % (i + 1);
        size_t temp = indices[i];
        indices[i] = indices[j];
        indices[j] = temp;
    }
}
