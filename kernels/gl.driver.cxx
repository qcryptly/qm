#include "gl.driver.h"

using namespace glm;
namespace GLDriver {

inline void Device::initializeWindowCtx() {
  assert(glfwInit());
  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window_ = glfwCreateWindow(
    width_,
    height_,
    name_,
    NULL, NULL);

  assert(window_);

  glfwMakeContextCurrent(window_);
  assert(glewInit() == GLEW_OK);

  glfwSetInputMode(window_, GLFW_STICKY_KEYS, GL_TRUE);
  glClearColor(1.0f,1.0f,1.0f,1.0f);

  // cudaGLSetGLDevice(device_);
}

inline void Device::createVBO() {
  GLuint vbo_;
  GLFWwindow* window_;
  glGenBuffers(1, &vbo_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);

  // initialize buffer object
  unsigned int size = mesh_width_ * mesh_height_ * 4 * sizeof(float);
  glBufferData(GL_ARRAY_BUFFER, size, 0, GL_DYNAMIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // register this buffer object with CUDA
//  checkCudaErrors(cudaGraphicsGLRegisterBuffer(*vbo_res_, vbo_, cudaGraphicsMapFlagsWriteDiscard));

  // SDK_CHECK_ERROR_GL();
}
Device::Device(
  int width,
  int height,
  const char * name) :
  width_{width}, height_{height},
  name_{name} {
    initializeWindowCtx();
    createVBO();
};
void Device::setDisplay(void(*display)()) {
  display_ = display;
}
void Device::run() {
  do{
    // Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
    glClear( GL_COLOR_BUFFER_BIT );
    // Draw nothing, see you in tutorial 2 !

    // Swap buffers
    glfwSwapBuffers(window_);
    glfwPollEvents();
  } // Check if the ESC key was pressed or the window was closed
  while(glfwGetKey(window_, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
       glfwWindowShouldClose(window_) == 0 );

  // Close OpenGL window and terminate GLFW
  glfwTerminate();
}

}
