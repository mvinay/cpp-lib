#ifndef COMMON_ERROR_H
#define COMMON_ERROR_H

#include <iostream>
#include <string>

static inline void printError(std::string msg) {
  std::cerr << msg << std::endl;
}

#endif
