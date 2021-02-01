#include "Buffer.h"
#include "../spec/spec.h"

int main(int argc, char* argv[]) {
    it("properly_writes_and_reads_single_value", []{
        Buffer b;
        b.sputn("my value", 8);
        assertEq(std::string(b.sgetn(b.in_avail(), true)), std::string("my value"));
    });
    it("properly_writes_and_reads_multiple_values", []{
        Buffer b;
        b.sputn("how", 3);
        b.sputn("much", 4);
        b.sputn("memory", 6);
        b.sputn("do", 2);
        b.sputn("you need?", 9);
        assertEq(b.in_avail(), 24);
        assertEq(std::string(b.sgetn(b.in_avail(), true)), std::string("howmuchmemorydoyou need?"));
    });
    it("properly_reads_multiple_values", []{
        Buffer b;
        b.sputn("bulk reads does not slow me", 27);
        assertEq(std::string(b.sgetn(4, true)), std::string("bulk"));
        assertEq(std::string(b.sgetn(6, true)), std::string(" reads"));
        assertEq(std::string(b.sgetn(5, true)), std::string(" does"));
        assertEq(std::string(b.sgetn(4, true)), std::string(" not"));
        assertEq(std::string(b.sgetn(5, true)), std::string(" slow"));
        assertEq(std::string(b.sgetn(3, true)), std::string(" me"));
    });
    it("properly_reads_char_by_char", []{
        Buffer b;
        b.sputn("i'm an array of char", 3);
        assertEq(b.sbumpc(), 'i');
        assertEq(b.sbumpc(), '\'');
        assertEq(b.sbumpc(), 'm');
    });
    it("returns_proper_buffer_size", []{
        Buffer b;
        b.sputn("This is exactly 25 characters", 25);
        assertEq(b.in_avail(), 25);
        b.sgetn(12);
        assertEq(b.in_avail(), 13);
        b.sputn("Another 17 characters", 17);
        assertEq(b.in_avail(), 30);
    });

    return run(argc, argv);
}