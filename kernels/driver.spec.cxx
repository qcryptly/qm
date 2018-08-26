#pragma once

#include <iostream>
#include <qmtest.hxx>

#include "driver.h"

namespace QM {

TEST_F(Test, DeviceQuery) {
  // How we should provision our kernel runs
  KDriver::Device device{};
  std::cout << "GPU Properties =====================" << std::endl;
  std::cout << "Name: " << device.properties_.name << std::endl;
  std::cout << "Compute Mode: " << device.properties_.computeMode << std::endl;
  std::cout << "Concurrent Kernels: " << device.properties_.concurrentKernels << std::endl;
  std::cout << "L2 Cache Size: " << device.properties_.l2CacheSize << std::endl;
  std::cout << "Memory Clock Rate: " << device.properties_.memoryClockRate << std::endl;
  std::cout << "Max Threads Per Block " << device.properties_.maxThreadsPerBlock << std::endl;
  std::cout << "Max Threads Per Multi Processor: " << device.properties_.maxThreadsPerMultiProcessor << std::endl;
  std::cout << "Multi Processor Count: " << device.properties_.multiProcessorCount << std::endl;
  std::cout << "Async Engine Count: " << device.properties_.asyncEngineCount << std::endl;
  std::cout << "END ===============================" << std::endl;
}

}
