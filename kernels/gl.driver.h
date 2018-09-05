#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <cassert>

namespace GLDriver {
  class Device {
    int width_{};
    int height_{};
    int mesh_width_{};
    int mesh_height_{};
    GLFWwindow* window_;
    const char * name_{};
    // Fxns
    inline void initializeWindowCtx(void(*)());
    inline void createVBO(void(*)(GLuint&));
    void(*display_)();
  public:
    explicit Device(int, int, const char *, void(*)(), void(*)(GLuint&));
    // Set GL render
    void setDisplay(void(*)());
    void run();
  };
}
