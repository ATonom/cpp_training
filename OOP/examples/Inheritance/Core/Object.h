#pragma once
#include "utility.h"
#include "InhTypes.h"

namespace inh
{

struct FObjectInfo
{
    String name = "Object";
};

// Базовый класс
class Object
{
public:
    Object() = default;

    virtual void tick() = 0;
    virtual void init() = 0;
    virtual bool is_world() const = 0;

    const String& get_name() const;

protected:
    FObjectInfo _info;

private:

};

} // namespace inh