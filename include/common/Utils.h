#ifndef COMMON_UTILS_H
#define COMMON_UTILS_H

#include <memory>
#include <stdexcept>

namespace utils {

// Starting the enum with 1 so that == 0 can't be used!
typedef enum { EQ = 1, LT, GT } Result;

// TODO: Try with lambda functions. Currently, parameterized lambdas are not
// supported.
struct compare {
  template <class T> Result operator()(const T &lhs, const T &rhs) {
    if (!std::is_scalar<T>::value) {
      throw std::invalid_argument("Not a scalar Type."
                                  " Try defining your own comparator");
    }

    if (lhs < rhs)
      return LT;
    if (lhs == rhs)
      return EQ;
    return GT;
  }
};

// Just a utility function.
template <class T, class Comparator>
static inline bool equals(Comparator &comparator, const T &lhs, const T &rhs) {
  return (comparator(lhs, rhs) == EQ);
}

} // end namespace -- utils
#endif
