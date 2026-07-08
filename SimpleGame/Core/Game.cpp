#include <iostream>

#include "Game.h"


using namespace SG;

Game& Game::getInstance()
{
    static Game instance;
    return instance;
}

const GameState& Game::tick() const
{
    return _State;
}
