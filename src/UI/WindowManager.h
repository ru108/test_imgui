#pragma once

#include <algorithm>
#include <vector>
#include <memory>

#include "imgui.h"

namespace UI {
  class Window {
  public:
    virtual ~Window() = default;
    virtual void update() = 0;

  protected:
    bool _showing{true};
  };

  class WindowManager {
  public:
    WindowManager() {
      IMGUI_CHECKVERSION();
      ImGui::CreateContext();

      auto& io = ImGui::GetIO(); (void)io;
      io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

      SetStyle();
      AddFonts();
    }

    virtual ~WindowManager() { ImGui::DestroyContext();	}

    void Update() {
      pollEvents();
      createNewFrame();
      update();
      clearBackground();
      draw();
    }

    [[nodiscard]] bool ShouldClose() const { return shouldClose(); }
    void Close() const { close(); }

    void SetStyle() const {
      ImGui::StyleColorsClassic();
    }

    void AddFonts() const {
      auto& io = ImGui::GetIO();
      io.Fonts->AddFontFromFileTTF("../fonts/JetBrainsMono-Regular.ttf", 20.0f);
      io.Fonts->Build();
    }

    void AddWindow(std::unique_ptr<Window> newWindow) {
      windows.push_back(std::move(newWindow));
    }

  private:
    std::vector<std::unique_ptr<Window>> windows;

    void update() const {
      ImGui::NewFrame();

      std::ranges::for_each(windows, [](const auto& window) { window->update(); });

      ImGui::Render();
    }

    virtual void pollEvents() const = 0;
    virtual void createNewFrame() const = 0;
    virtual void clearBackground() const = 0;
    virtual void draw() const = 0;
    [[nodiscard]] virtual bool shouldClose() const = 0;
    virtual void close() const = 0;
  };
}