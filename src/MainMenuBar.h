#pragma once

#include "UI/WindowManager.h"
#include "Command/ApplicationCloseCommand.h"

class MainMenuBar : public UI::Window {
public:
  MainMenuBar(std::shared_ptr<UI::WindowManager> windowManager) : _windowManager{ windowManager } {}

  void update() override {
    if (!_showing) return;
    if (!ImGui::BeginMainMenuBar()) return;

    if (ImGui::BeginMenu("File")) {
      if (ImGui::MenuItem("Quit", "Alt+F4")) {
        ApplicationCloseCommand appClose(_windowManager);
        appClose.Execute();
      }
      ImGui::EndMenu();
    }

    ImGui::EndMainMenuBar();
  }

private:
  std::shared_ptr<UI::WindowManager> _windowManager;
};
