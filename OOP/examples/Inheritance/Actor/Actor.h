#pragma once
#include "utility.h"
#include "Object.h"

namespace inh
{
 
    // Объект который можно расположить в пространстве.
class Actor : public Object
{
public:
    Actor();
    const TShared_Ptr<Object> get_owner() const;
    //  Position
    const FPosition& get_position() const;
    void set_position(FPosition& new_pos);
    //  Collision
    

    //  Object override
    void tick() override;
    void init() override;
    bool is_world() const override final;

private:
    TShared_Ptr<Object> _owner = nullptr;
    FPosition _position;
    FCollisionSphere _collision_sphere;
};
} // namespace inh