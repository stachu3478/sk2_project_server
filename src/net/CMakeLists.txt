add_executable(BufferTest BufferTest.cpp
    Buffer
)
target_compile_options(BufferTest PRIVATE "--std=c++2a" "-W" "-Wall" "-Wextra" "-pedantic" "-Werror")
add_test(NAME BufferTest-properly_writes_and_reads_single_value COMMAND BufferTest properly_writes_and_reads_single_value)
add_test(NAME BufferTest-properly_writes_and_reads_multiple_values COMMAND BufferTest properly_writes_and_reads_multiple_values)
add_test(NAME BufferTest-properly_reads_multiple_values COMMAND BufferTest properly_reads_multiple_values)
add_test(NAME BufferTest-properly_reads_char_by_char COMMAND BufferTest properly_reads_char_by_char)
add_test(NAME BufferTest-returns_proper_buffer_size COMMAND BufferTest returns_proper_buffer_size)