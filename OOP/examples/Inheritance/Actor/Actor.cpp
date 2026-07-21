#include "Actor.h"

using namespace inh;

Actor::Actor()
{
    _info.name = "Actor";
}

const TShared_Ptr<Object> Actor::get_owner() const
{
    return _owner;
}

const FPosition& Actor::get_position() const
{
    return _position;
}

void Actor::set_position(FPosition& new_pos)
{
    _position = new_pos;
}


void Actor::tick()
{
    print("Actor tick \n");
}

void Actor::init() 
{
    print("Actor init \n");
}

bool Actor::is_world() const
{
    return false;
}
