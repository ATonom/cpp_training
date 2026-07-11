#include <iostream>
#include <typeinfo>

#include "traits.h"
#include "functions.h"

using namespace rav;

int main()
{
    auto b = is_one_of_v<int, double, bool, float, int>;
    std::cout << b;

    return 0;
}