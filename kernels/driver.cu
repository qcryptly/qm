#include "driver.h"
#include <iostream>

__global__ void _default_kernel(float4 *pos, unsigned int width, unsigned int height, float time)
{
    unsigned int x = blockIdx.x*blockDim.x + threadIdx.x;
    unsigned int y = blockIdx.y*blockDim.y + threadIdx.y;

    // calculate uv coordinates
    float u = x / (float) width;
    float v = y / (float) height;
    u = u*2.0f - 1.0f;
    v = v*2.0f - 1.0f;

    // calculate simple sine wave pattern
    float freq = 4.0f;
    float w = sinf(u*freq + time) * cosf(v*freq + time) * 0.5f;

    // write output vertex
    pos[y*width+x] = make_float4(0.0,0.0,0.0,0.0);//u, w, v, 0.0f);
}

void checkCudaErrors(int cudaStatus) {
  // switch(cudaStatus) {
  //   case cudaSuccess:
  //     std::cout << "[Cuda - Status] " << "Cuda success" << std::endl;
  //     return;
  //   case cudaErrorMemoryAllocation:
  //     std::cout << "[Cuda - Status] " << "Cuda error memory allocation" << std::endl;
  //     return;
  //   case cudaErrorInvalidDevice:
  //   std::cout << "[Cuda - Status] " << "Cuda error invalid device" << std::endl;
  //     return;
  //   case cudaErrorInvalidValue:
  //   std::cout << "[Cuda - Status] " << "Cuda error invalid value" << std::endl;
  //     return;
  //   case cudaErrorInvalidResourceHandle:
  //   std::cout << "[Cuda - Status] " << "Cuda error invalid resource handle" << std::endl;
  //     return;
  //   case cudaErrorUnknown:
  //   std::cout << "[Cuda - Status] " << "Cuda error unknown" << std::endl;
  //     return;
  // }
  // std::cout << "Unregistered error: " << cudaStatus << std::endl;
}

namespace KDriver {
    void defaultKernel (cudaGraphicsResource **vbo_res_, dim3 grid, dim3 block, float time) {
      float4 *dptr;
      checkCudaErrors(cudaGraphicsMapResources(1, vbo_res_, 0));
      size_t num_bytes;
      cudaGraphicsResourceGetMappedPointer((void **)&dptr, &num_bytes,
        *vbo_res_);
      _default_kernel<<<grid, block>>>(dptr, 256, 256, time);
      cudaGraphicsUnmapResources(1, vbo_res_, 0);
    }

    Device::Device() {
      cudaGetDevice(&device_);
      cudaGetDeviceProperties(&properties_, device_);
      dim3 block(8, 8, 1);
      dim3 grid(256 / block.x, 256 / block.y, 1);
    }

    void Device::setDefaultKernel() {
      kernel_ = defaultKernel;
    }

    void Device::makeGLBuffer(unsigned& buffer) {
      std::cout << "make gl buffer" << std::endl;
      checkCudaErrors(cudaGraphicsGLRegisterBuffer(&vbo_res_, buffer, cudaGraphicsMapFlagsWriteDiscard));
      std::cout << "end cuda graphics gl register buffer" << std::endl;
    }

    void Device::setGLDevice() {
      std::cout << "make gl device" << std::endl;
      checkCudaErrors(cudaGLSetGLDevice(device_));
      std::cout << "end cuda gl set gl device" << std::endl;
    }

    void Device::run(float time) {
      kernel_(&vbo_res_, grid_, block_, time);
    }
}
