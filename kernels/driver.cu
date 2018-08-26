#include "driver.h"

namespace KDriver {
    Device::Device() {
      cudaGetDevice(&device_);
      cudaGetDeviceProperties(&properties_, device_);
    }
}
