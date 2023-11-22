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

#include <assert.h>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

#endif
