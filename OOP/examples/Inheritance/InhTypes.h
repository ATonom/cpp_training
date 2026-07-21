#pragma once


namespace inh
{
enum class EWorldState : uint8_t
{
    BigBang = 0,
    Run,
    End
};

enum class ECollisionType : uint8_t
{
    NoCollision = 0,
    Overlap,
    Block
};

struct FCollisionSphere
{
    ECollisionType type = ECollisionType::NoCollision;
    double radius = 0;
};


struct FPosition
{
    double x = 0.0;
    double y = 0.0;

    FPosition() = default;
    FPosition(double nx, double ny) : x(nx), y(ny) {};
};
} // namespace inh