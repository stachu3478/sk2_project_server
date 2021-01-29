#include "MessageFilter.h"

bool newPlayerMessageFilter(char messageType) { return messageType != 0; }
bool ingameMessageFilter(char messageType) { return messageType == 0; }