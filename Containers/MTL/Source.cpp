#include "utility.h"
#include "allocator.h"

#include <vector>

using namespace mtl;

int main()
{
    std::vector<int, Allocator<int>> vec;
    vec.reserve(10);

    for (int i = 1; i <= 10; ++i)
    {
        vec.push_back(i);
        print(i, "\n");
    }

    return 0;
}