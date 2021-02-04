#include <unordered_map>
#include <functional>
#include <exception>
#include <iostream>

class NoTestSpecifiedException : public std::exception {};
class AssertionError : public std::exception {};

typedef std::function<void()> TestCase; 

std::unordered_map<std::string, TestCase> its;

void it(const char* description, TestCase lambda) {
    its.insert(std::pair<std::string, TestCase>(std::string(description), lambda));
}

void fail() {
    std::exit(1);
}

int run(int argc, char* argv[]) {
    if (argc < 1) throw new NoTestSpecifiedException();
    try {
        its.at(std::string(argv[1]))();
    } catch (const std::out_of_range& e) {
        printf("Test case not found! - %s\n", argv[1]);
        fail();
    }
    
    return 0;
}

void fail(const char* message) {
    printf("Failed: %s\n", message);
    fail();
}

void assertFalse(bool value) {
    if (value) fail();
}

void assertFalse(bool value, const char* messageOnFailure) {
    if (value) fail(messageOnFailure);
}

void assertTrue(bool value) {
    assertFalse(!value);
}

void assertTrue(bool value, const char* messageOnFailure) {
    assertFalse(!value, messageOnFailure);
}

template <class X>
void assertEq(X actual, X expected, const char* message = "Expected arguments to be equal") {
    if (actual != expected) {
        std::cout << "Actual: " << actual << std::endl;
        std::cout << "Expected: " << expected << std::endl;
        fail(message);
    }
}

template <class X, class Y>
void assertEq(X actual, Y expected, const char* message = "Expected arguments to be equal") {
    if (actual != expected) {
        std::cout << "Actual: " << actual << " | " << (Y)actual << std::endl;
        std::cout << "Expected: " << expected << " | " << (X)expected << std::endl;
        fail(message);
    }
}
