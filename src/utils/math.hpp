#ifndef MATH_H
#define MATH_H


#define CHANCE(chance) ((RAND(0, 100000) / 100000.0) <= chance)
#define RAND(min, max) ((rand() % (max - min + 1)) + min)

#endif
