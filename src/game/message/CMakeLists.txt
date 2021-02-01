add_executable(messageHelperTest messageHelperTest.cpp
    messageHelper
    ../../net/Buffer
)
target_compile_options(messageHelperTest PRIVATE "--std=c++2a" "-W" "-Wall" "-Wextra" "-pedantic" "-Werror")
add_test(NAME messageHelperTest-converts_small_integer_into_char_array COMMAND messageHelperTest converts_small_integer_into_char_array)
add_test(NAME messageHelperTest-converts_large_integer_into_char_array COMMAND messageHelperTest converts_large_integer_into_char_array)
add_test(NAME messageHelperTest-converts_small_integer_back_from_char_array COMMAND messageHelperTest converts_small_integer_back_from_char_array)
add_test(NAME messageHelperTest-converts_large_integer_back_from_char_array COMMAND messageHelperTest converts_large_integer_back_from_char_array)