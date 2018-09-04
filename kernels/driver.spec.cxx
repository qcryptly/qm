#pragma once

#include <iostream>
#include <qmtest.hxx>

#include "driver.h"
#include "gl.driver.h"

namespace QM {

TEST_F(Test, OpenGLInterop) {
  const char * name = "OpenGLInterop Test";
  // How we should provision our kernel runs
  KDriver::Device kdevice{};
  GLDriver::Device gldevice{1024, 512, name};
  /*device.setKernel([](){
    // -- Should have no dependencies on cuda
    float4 *dptr;
    checkCudaErrors(cudaGraphicsMapResources(1, vbo_resource, 0));
    size_t num_bytes;
    checkCudaErrors(cudaGraphicsResourceGetMappedPointer((void **)&dptr, &num_bytes,
    launch_kernel(dptr, mesh_width, mesh_height, g_fAnim);
    checkCudaErrors(cudaGraphicsUnmapResources(1, vbo_resource, 0));
  });*/
  //device.run();
}

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
