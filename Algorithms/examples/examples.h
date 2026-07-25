#pragma once

#ifdef SORTING
    #include "sorting_examples.h"
#endif // SORTING

namespace examples
{
inline void do_examples()
{
#ifdef SORTING
    sort::do_sorting_examples();
#endif // SORTING
}
} // namespace examples
