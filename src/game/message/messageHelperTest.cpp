#include "../../net/Buffer.h"
#include "messageHelper.h"
#include "../../spec/spec.h"

int main(int argc, char* argv[]) {
    it("converts_small_integer_into_char_array", []{
        char array[4];
        insertInteger(array, 123);
        assertEq(array[0], 0);
        assertEq(array[1], 0);
        assertEq(array[2], 0);
        assertEq(array[3], 123);
    });
    it("converts_large_integer_into_char_array", []{
        char array[4];
        insertInteger(array, 123456789);
        assertEq(array[0], 7);
        assertEq(array[1], 91);
        assertEq(array[2], -51);
        assertEq(array[3], 21);
    });
    it("converts_small_integer_back_from_char_array", []{
        char array[4] { 0, 0, 0, 123 };
        Buffer b(array, 4);
        assertEq(readInteger(&b), 123);
    });
    it("converts_large_integer_back_from_char_array", []{
        char array[4] { 7, 91, -51, 21 };
        Buffer b(array, 4);
        assertEq(readInteger(&b), 123456789);
    });

    return run(argc, argv);
}