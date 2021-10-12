#pragma once

#include "UI/WindowManager.h"

class ExampleWindow : public UI::Window {
public:
  void update() override {
    if (!_showing) return;

    if (ImGui::Begin("Settings", &_showing)) {
      ImGui::Text("This is an example window");
      ImGui::Text("Dock this window!");
      ImGui::Separator();
      ImGui::Text("You can create your own windows for any purpose");

      if (ImGui::Button("This is a button")) {
        ++count;
      }

      ImGui::Text("Count: %d", count);

      ImGui::End();
    }
  }

private:
  int count{ 0 };
};
