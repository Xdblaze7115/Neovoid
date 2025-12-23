#pragma once
#include <string>
#include <functional>
#include "Math/Vector.hpp"
#include "Events/Event.hpp"

using EventCallbackFn = std::function<void(Event&)>;
struct WindowProps {
    std::string Title = "Neovoid";
    Vector2 Size = Vector2(1280, 720);
    bool IsResizeable = true;
    EventCallbackFn EventCallback;
};

enum class GameState {
    None,
    MainMenu,
    Loading,
    World,
    Paused,
    Exiting
};