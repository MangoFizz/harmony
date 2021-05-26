#ifndef HARMONY_MEMORY_PADDING_HPP
#define HARMONY_MEMORY_PADDING_HPP

#include <cstddef>

// Padding
#define GAP(bytes, line) std::byte gap_##line[bytes]
#define GET_GAP(bytes, line) GAP(bytes, line)
#define PADDING(bytes) GET_GAP(bytes, __LINE__)

#endif