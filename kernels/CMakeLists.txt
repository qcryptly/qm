set(CMAKE_CXX_COMPILER     "/usr/bin/clang++-6.0")
set(CMAKE_CXX_FlAGS        "-g -Wall -pthread -std=c++2a")

# We need thread support
find_package(Threads REQUIRED)

# Cuda support
find_package(CUDA REQUIRED)
set(CUDA_NVCC_FLAGS "-arch=sm_52;-ccbin=/usr/bin/clang-4.0")

# Enable ExternalProject CMake module
include(ExternalProject)

# Download and install GoogleTest
ExternalProject_Add(
    gtest
    URL https://github.com/google/googletest/archive/master.zip
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
    # Disable install step
    INSTALL_COMMAND ""
)

# Get GTest source and binary directories from CMake project
ExternalProject_Get_Property(gtest source_dir binary_dir)

# Create a libgtest target to be used as a dependency by test programs
add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)

# Set libgtest properties
set_target_properties(libgtest PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/libgtest.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

# Create a libgmock target to be used as a dependency by test programs
add_library(libgmock IMPORTED STATIC GLOBAL)
add_dependencies(libgmock gtest)

# Set libgmock properties
set_target_properties(libgmock PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/googlemock/libgmock.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

# I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
include_directories("${source_dir}/googletest/include"
                    "${source_dir}/googlemock/include")

enable_testing()

file(GLOB SRCS *spec.cxx)
foreach(executablepath ${SRCS})
  GET_FILENAME_COMPONENT(executable ${executablepath} NAME_WE)

  set(cudapath "${CMAKE_CURRENT_SOURCE_DIR}/${executable}.cu")
  message(STATUS "Cuda Path='${cudapath}'")
  cuda_add_library("${executable}.cuda" SHARED
    ${cudapath}
  )

  set_target_properties("${executable}.cuda" PROPERTIES CUDA_POSITION_INDEPENDENT_CODE ON)
  set_target_properties("${executable}.cuda" PROPERTIES CUDA_SEPARABLE_COMPILATION ON)

  message(STATUS "Includes='${PROJECT_SOURCE_DIR}/include'")
  message(STATUS "Executable='${executable}'")

  add_executable("test${executable}" ${executablepath})

  target_link_libraries(
      "test${executable}"
      "${executable}.cuda"
      libgtest
      stdc++
      cudart_static
      cuda
      dl
      rt
  )

  # Specify here the include directories exported by this library
  target_include_directories("test${executable}" PUBLIC
      ${PROJECT_SOURCE_DIR}/include
      ${PROJECT_SOURCE_DIR}/kernels
  )
  add_test(NAME "test${executable}"
           COMMAND "kernels/test${executable}")
endforeach()
