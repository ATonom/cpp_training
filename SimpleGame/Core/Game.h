#pragma once
#include "SG_Types.h"

namespace SG
{

class Game
{
public:
    static Game& getInstance();
    const GameState& tick() const;

private:
    GameState _State = Run;
    
    Game() = default;
    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;
};
} // namespace SG