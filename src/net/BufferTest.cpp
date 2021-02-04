#include "Buffer.h"
#include "../spec/spec.h"

using namespace std;

int main(int argc, char* argv[]) {
    Buffer b;
    it("properly_writes_and_reads_single_value", [&b]{
        b.sputn("my value", 8);
        assertEq(string(b.sgetn(b.in_avail(), true)), string("my value"));
    });
    it("properly_writes_and_reads_multiple_values", [&b]{
        b.sputn("how", 3);
        b.sputn("much", 4);
        b.sputn("memory", 6);
        b.sputn("do", 2);
        b.sputn("you need?", 9);
        assertEq(b.in_avail(), 24);
        assertEq(string(b.sgetn(b.in_avail(), true)), string("howmuchmemorydoyou need?"));
    });
    it("properly_reads_multiple_values", [&b]{
        b.sputn("bulk reads does not slow me", 27);
        assertEq(string(b.sgetn(4, true)), string("bulk"));
        assertEq(string(b.sgetn(6, true)), string(" reads"));
        assertEq(string(b.sgetn(5, true)), string(" does"));
        assertEq(string(b.sgetn(4, true)), string(" not"));
        assertEq(string(b.sgetn(5, true)), string(" slow"));
        assertEq(string(b.sgetn(3, true)), string(" me"));
    });
    it("properly_reads_char_by_char", [&b]{
        b.sputn("i'm an array of char", 3);
        assertEq(b.sbumpc(), 'i');
        assertEq(b.sbumpc(), '\'');
        assertEq(b.sbumpc(), 'm');
    });
    it("returns_proper_buffer_size", [&b]{
        b.sputn("This is exactly 25 characters", 25);
        assertEq(b.in_avail(), 25);
        b.sgetn(12);
        assertEq(b.in_avail(), 13);
        b.sputn("Another 17 characters", 17);
        assertEq(b.in_avail(), 30);
    });

    return run(argc, argv);
}