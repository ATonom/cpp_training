#include "Base.h"

using namespace pmm;

void Base::print_name() const
{
    print("Class name: ", get_name(), " id: ", _id, "\n");
}

String Base::get_name() const
{
    return "Base";
}

size_t Base::_count = 0;