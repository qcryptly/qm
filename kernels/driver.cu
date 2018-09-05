#include "driver.h"

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
    pos[y*width+x] = make_float4(u, w, v, 1.0f);
}

namespace KDriver {
    void defaultKernel (cudaGraphicsResource **vbo_res_, dim3 grid, dim3 block, float time) {
      float4 *dptr;
      cudaGraphicsMapResources(1, vbo_res_, 0);
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
      cudaGraphicsGLRegisterBuffer(&vbo_res_, buffer, cudaGraphicsMapFlagsWriteDiscard);
    }

    void Device::setGLDevice() {
      cudaGLSetGLDevice(device_);
    }

    void Device::run(float time) {
      kernel_(&vbo_res_, grid_, block_, time);
    }
}
