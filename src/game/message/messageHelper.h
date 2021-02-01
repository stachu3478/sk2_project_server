#pragma once

#include <string>
#include <exception>
#include "../../net/Buffer.h"

class BufferDrownError : public std::exception {};
void insertInteger(char* str, int v);
/**
 * NOTE: Throws error when buffer cannot be fully read!
*/
int readInteger(Buffer* buff);
