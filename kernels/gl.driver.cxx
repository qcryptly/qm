#include "gl.driver.h"
#include <iostream>
using namespace glm;
namespace GLDriver {

inline void Device::initializeWindowCtx(std::function<void()> setGLDevice) {
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
  setGLDevice();
}

inline void Device::createVBO(std::function<void(GLuint&)> makeGLBuffer) {
  glGenBuffers(1, &vbo_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);
  std::cout << "[Create VBO - buffer value] " << vbo_ << std::endl;

  // initialize buffer object
  unsigned int size = mesh_width_ * mesh_height_ * 4 * sizeof(float);
  std::cout << "[Create VBO - buffer size] " << size << std::endl;
  std::cout << "[Create VBO - mesh_width_] " << mesh_width_ << std::endl;
  std::cout << "[Create VBO - mesh_height_] " << mesh_height_ << std::endl;
  glBufferData(GL_ARRAY_BUFFER, size, 0, GL_DYNAMIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // register this buffer object with CUDA
  makeGLBuffer(vbo_);
}

Device::Device(
  int width,
  int height,
  const char * name,
  std::function<void()> setGLDevice,
  std::function<void(GLuint&)> makeGLBuffer) :
  width_{width}, height_{height},
  name_{name} {
    initializeWindowCtx(setGLDevice);
    createVBO(makeGLBuffer);
};
void Device::setDisplay(void(*display)()) {
  display_ = display;
}
void Device::run(std::function<void(float)> runCuda) {
  float time = 0.0f;
  do{
    // Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
    // Draw nothing, see you in tutorial 2 !

    // run CUDA kernel to generate vertex positions
    runCuda(time);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set view matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, -3.0);
    glRotatef(0.0, 1.0, 0.0, 0.0);
    glRotatef(0.0, 0.0, 1.0, 0.0);

    // render from the vbo
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glVertexPointer(4, GL_FLOAT, 0, 0);

    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3f(1.0, 0.0, 0.0);
    glDrawArrays(GL_POINTS, 0, 256 * 256);
    glDisableClientState(GL_VERTEX_ARRAY);

    time += 0.01f;

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
