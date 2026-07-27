#pragma once
#include "sorting_examples.h"


namespace examples
{
inline void do_examples()
{
#ifdef SORTING_1
    sort::do_sorting_example_1();
#endif // SORTING_1

#ifdef SORTING_2
    sort::do_sorting_example_2();
#endif // SORTING_2

}
} // namespace examples
