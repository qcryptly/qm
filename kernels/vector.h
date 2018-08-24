#pragma once

namespace Vectors {
  // Accepts
  void add(float *&, float *&, void(*)(float *&, float *&, int), int);
  void free(float *&, float *&);
}
