#include "World.h"

using namespace inh;


World::World() 
{
    _info.name = "World";
}

World& World::get_instance()
{
    static World instance;
    return instance;
}

EWorldState World::get_state() const
{
    return _state;
}

void World::tick()
{
    [[nolikely]] if (_state == EWorldState::BigBang) init();

    
    for (auto& a : _actors)
    {
        a->tick();
    }
}

void World::init()
{
    do_init();

    // test
    FPosition p(5.0, 5.0); 
    auto a_ptr = spawn_actor<Actor>(FPosition(5, 5));
}

bool World::is_world() const
{
    return true;
}

void World::do_init()
{
    print("INIT \n");

    _state = EWorldState::Run;
}
