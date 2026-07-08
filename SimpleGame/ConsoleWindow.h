#pragma once

namespace SG
{

struct Resolution
{
    unsigned x = 0;
    unsigned y = 0;

    Resolution(unsigned inX, unsigned inY) : x(inX), y(inY) {};
};


class ConsoleWindow
{
public:
    const Resolution& getResolution() { return _resolution; };
    void update();

private:
    Resolution _resolution;
};

} // namespace SG