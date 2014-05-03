#ifndef __COMMAND_H__
#define __COMMAND_H__

#include "field.h"

void interpreter(std::string input, Field &f, bool &invalid);

void interface(std::string input, Field &f);

#endif
