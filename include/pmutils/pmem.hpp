#pragma once
#include <immintrin.h>

#include <cstddef>
namespace pmutils {

void *open(char const *path, size_t len);
inline void clflush(void *ptr) { _mm_clflush(ptr); }
// Fetches the line of data from memory that contains the byte specified with
// the source operand to a location in the cache hierarchy specified by a
// locality hint:
// - T0 (temporal data)—prefetch data into all levels of the cache hierarchy.
// - T1 (temporal data with respect to first level cache misses)—prefetch data
// into level 2 cache and higher.
// - T2 (temporal data with respect to second level cache misses)—prefetch data
// into level 3 cache and higher, or an implementation-specific choice.
// - NTA (non-temporal data with respect to all cache levels)—prefetch data into
// non-temporal cache structure and into a location close to the processor,
// minimizing cache pollution.
inline void prefetch(void *ptr, _mm_hint hint = _MM_HINT_T2) {
    _mm_prefetch(ptr, hint);
}

}  // namespace pmutils