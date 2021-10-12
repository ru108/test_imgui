#pragma once

#include <memory>

#include "Command/ICommand.h"
#include "UI/WindowManager.h"

class ApplicationCloseCommand : public ICommand {
public:
  ApplicationCloseCommand(std::shared_ptr<UI::WindowManager> manager) : _windowManager{ manager } {}
  void Execute() const override { _windowManager->Close(); }

private:
  std::shared_ptr<UI::WindowManager> _windowManager;
};