#pragma once

#include <iostream>

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"

#include "UI/WindowManager.h"

namespace UI {
  //glfw needs a window
  class GLFWWindow {
  public:
    GLFWWindow(int width, int height, const char* title) : _width{ width }, _height{ height } {
      if (!glfwInit()) std::cerr << "Failed GLFW init\n";

      // GL 3.0
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
      //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
      //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only

      if (_window = glfwCreateWindow(width, height, title, NULL, NULL); !_window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return;
      }
      glfwMakeContextCurrent(_window);
      glfwSwapInterval(1); // Enable vsync
    }

    ~GLFWWindow() {
      glfwDestroyWindow(_window);
      glfwTerminate();
    }

    void PollEvents() const { glfwPollEvents(); }
    void Draw() const { glfwSwapBuffers(_window); }

    void ClearBackground() const {
      int display_w{ 0 }, display_h{0};
      glfwGetFramebufferSize(_window, &display_w, &display_h);
      glViewport(0, 0, display_w, display_h);
      glClearColor(_clear_color.x * _clear_color.w, _clear_color.y * _clear_color.w, _clear_color.z * _clear_color.w, _clear_color.w);
      glClear(GL_COLOR_BUFFER_BIT);
    }

    bool WindowShouldClose() const { return glfwWindowShouldClose(_window); }
    [[nodiscard]] void WindowClose() const { glfwSetWindowShouldClose(_window, GLFW_TRUE); }

    [[nodiscard]] int getWidth() const noexcept { return _width; }
    [[nodiscard]] int getHeight() const noexcept { return _height; }
    void Resize(int width, int height) const { glViewport(0, 0, width, height); }
    [[nodiscard]] GLFWwindow* getRawWindow() const noexcept { return _window; }

  private:
    int _width, _height;
    GLFWwindow* _window;
    ImVec4 _clear_color{ 0.45f, 0.55f, 0.60f, 1.00f };
  };

  //glfw implementation example
  class GLFWWindowManager final : public UI::WindowManager {
  public:
    GLFWWindowManager(const char* title) : _mainWindow{ 800, 600, title } {
      ImGui_ImplGlfw_InitForOpenGL(_mainWindow.getRawWindow(), true);
      ImGui_ImplOpenGL3_Init("#version 410");
    }

    ~GLFWWindowManager() {
      ImGui_ImplOpenGL3_Shutdown();
      ImGui_ImplGlfw_Shutdown();
    }

  private:
    GLFWWindow _mainWindow;

    void pollEvents() const override { _mainWindow.PollEvents(); }

    void createNewFrame() const override {
      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
    }

    void clearBackground() const override { _mainWindow.ClearBackground(); }

    void draw() const override {
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
      _mainWindow.Draw();
    }

    [[nodiscard]] bool shouldClose() const override { return _mainWindow.WindowShouldClose(); }
    void close() const override { _mainWindow.WindowClose(); }
  };
}
