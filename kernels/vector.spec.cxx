#pragma once

#include <qmtest.hxx>

#include "vector.h"

namespace QM {

void set_values(float *&x, float *&y, int N) {
  for (int i = 0; i < N; i ++) {
    x[i] = 1.0f;
    y[i] = 2.0f;
  }
}
TEST_F(Test, VectorAdd) {
  int N = 1<<20;
  float *x;
  float *y;

  Vectors::add(x, y, &set_values, N);
  float maxError = 0.0f;
  for (int i = 0; i < N; i++) {
    if (maxError > y[i] - 3.0f + .001f) {
      maxError = y[i];
    }
  }
  EXPECT_EQ(maxError, 0.0f);
  Vectors::free(x, y);
}

}
