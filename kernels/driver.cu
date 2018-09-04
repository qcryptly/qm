#include "driver.h"

namespace KDriver {
    Device::Device() {
      cudaGetDevice(&device_);
      cudaGetDeviceProperties(&properties_, device_);
    }

    void Device::setKernel(void(*kernel)()) {
      kernel_ = kernel;
    }
}
