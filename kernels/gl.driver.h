#pragma once

#include <functional>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <cassert>

namespace GLDriver {
  class Device {
    int width_{};
    int height_{};
    int mesh_width_{256};
    int mesh_height_{256};
    GLuint vbo_;
    GLFWwindow* window_;
    const char * name_{};
    // Fxns
    inline void initializeWindowCtx(std::function<void()>);
    inline void createVBO(std::function<void(GLuint&)>);
    void(*display_)();
  public:
    explicit Device(int, int, const char *, std::function<void()>, std::function<void(GLuint&)>);
    // Set GL render
    void setDisplay(void(*)());
    void run(std::function<void(float)>);
  };
}
