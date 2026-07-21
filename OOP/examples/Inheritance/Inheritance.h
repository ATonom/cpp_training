#pragma once
#include "utility.h"
#include "World.h"

namespace inh
{
inline void inheritance()
{
    print("[Inheritance]", "\n");

    String input_com; // test

    while (World::get_instance().get_state() != EWorldState::End)
    {
        World::get_instance().tick();
        
        std::cin >> input_com; // test
    };
}
} // namespace inh

  
/* Нужно сделать:
* 1. Систему ввода команд пользователя.
* 2. Добавить класс Character (может передвигаться).
* 3. Добавить класс Wall.
*/