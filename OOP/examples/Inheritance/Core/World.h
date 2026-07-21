#pragma once
#include "utility.h"
#include "InhTypes.h"
#include "Object.h"
#include "Actor.h"

namespace inh
{
// Объект 
class World : public Object
{
private:
    // Синглтон
    World();
    World(const World&) = delete;
    World& operator=(const World&) = delete;

public:
    static World& get_instance();
    EWorldState get_state() const;

    template <typename TActor>
    TShared_Ptr<Actor> spawn_actor( FPosition position);

    //  Object override
    void tick() override;
    void init() override;
    bool is_world() const override final;

private:
    void do_init();

    TVector<TShared_Ptr<Actor>> _actors;
    EWorldState _state = EWorldState::BigBang;
};



template <typename TActor>
inline TShared_Ptr<Actor> World::spawn_actor(FPosition position)
{
    TShared_Ptr<Actor> new_actor_ptr = make_sh_ptr<TActor>();
    
    if (new_actor_ptr)
    {
        new_actor_ptr->set_position(position);
        new_actor_ptr->init();
    }

    _actors.push_back(new_actor_ptr);

    return new_actor_ptr;
}

} // namespace inh