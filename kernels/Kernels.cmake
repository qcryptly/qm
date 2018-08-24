set(CMAKE_CXX_COMPILER     "/usr/bin/nvcc")
set(CMAKE_CXX_FlAGS        "--std=c++03 -ccbin=clang-4.0 -x cu -arch=sm_52")

FIND_PACKAGE(CUDA)
CUDA_NVCC_FLAGS(--std=c++03;-ccbin=clang-4.0;-x cu;-arch=sm_52)
file(GLOB SRCS *.cu)
foreach(executablepath ${SRCS})
  GET_FILENAME_COMPONENT(executable ${executablepath} NAME_WE)
  message(STATUS "Includes='${PROJECT_SOURCE_DIR}/include'")
  message(STATUS "Executable='${executable}'")

  cuda_add_library(${executable} SHARED ${executablepath})
endforeach()
