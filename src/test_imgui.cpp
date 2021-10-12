#include "UI/GLFWWindowManager.h"
#include "MainMenuBar.h"
#include "ExampleWindow.h"

auto main(int, char**) -> int {
  std::shared_ptr<UI::WindowManager> ui = std::make_shared<UI::GLFWWindowManager>("Dear ImGui GLFW+OpenGL3 example");
  ui->AddWindow(std::make_unique<MainMenuBar>(ui));
  ui->AddWindow(std::make_unique<ExampleWindow>());

  while (!ui->ShouldClose())
    ui->Update();

  return 0;
}