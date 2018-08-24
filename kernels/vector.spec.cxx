#pragma once

#include <qmtest.hxx>

#include "vector.hxx"

namespace QM {

void set_values(float *&x, float *&y, int N) {
  for (int i = 0; i < n; i ++) {
    x[i] = 1.0f;
    y[i] = 2.0f;
  }
}
TEST_F(Test, VectorTest) {
  int N = 1024;//1<<20;
  float *x;
  float *y;

  Vectors::add(x, y, &set_values, N);
  float maxError = 0.0f;
  for (int i = 0; i < N; i++)
    maxError = fmax(maxError, fabs(y[i]-3.0f));
  EXPECT_EQ(maxError, 0.0f);
  Vectors::free(x, y);
}

}
