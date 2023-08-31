#ifndef UTILS_VECTORS_H
#define UTILS_VECTORS_H

#include <vector>

template <typename T>
std::vector<T> flatten(std::vector<std::vector<T>> &input) {
  std::vector<T> result;
  for (const auto &inner_vector : input) {
    result.insert(result.end(), inner_vector.begin(), inner_vector.end());
  }
  return result;
}

#endif
