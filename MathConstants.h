
#ifndef PI
#define PI 3.14159265536f
#endif
#ifndef PI2
#define PI2 6.2831853072f
#endif

#ifndef RANDOM_FROM_TO
#define RANDOM_FROM_TO
#include <math.h>
template <class T> T randomRange(T from_, T to_) {
  T uns = (double)rand() / RAND_MAX * (to_ - from_) - to_;
  return uns;
}

#endif
