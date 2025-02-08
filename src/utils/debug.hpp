#ifndef DEBUG_H
#define DEBUG_H

#include <iostream>

#define DEBUG(x)                                                               \
  do {                                                                         \
    std::cerr << #x << ": " << x << std::endl;                                 \
  } while (0)

#define DEBUG2(x, y)                                                           \
  do {                                                                         \
    std::cerr << #x << ": " << x << " | ";                                     \
    std::cerr << #y << ": " << y << std::endl;                                 \
  } while (0)

#define DEBUG_VEC3(v) printf("%s %.4f %.4f %.4f\n", #v, v.x, v.y, v.z)
#define DEBUG_IVEC3(v) printf("%s %d %d %d\n", #v, v.x, v.y, v.z)

#endif
