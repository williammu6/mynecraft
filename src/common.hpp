#ifndef COMMON_H
#define COMMON_H

#define DEBUG(x)                                                               \
  do {                                                                         \
    std::cerr << #x << ": " << x << std::endl;                                 \
  } while (0)

#define DEBUG2(x, y)                                                           \
  do {                                                                         \
    std::cerr << #x << ": " << x << " | ";                                     \
    std::cerr << #y << ": " << y << std::endl;                                 \
  } while (0)

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <functional>
#include <memory>
#include <assert.h>

#endif
