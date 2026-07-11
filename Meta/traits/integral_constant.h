#pragma once
#include "traits_utility.h"

namespace rav
{

template <typename T, T v>
struct integral_constant 
{
    static constexpr T value = v;
    using type_value = T;
    using type = integral_constant<T, v>;
};

/*
* Частный случай, когда Т является bool.
*/
template <bool B>
using bool_constant = integral_constant<bool, B>;

using true_type = bool_constant<true>;
using false_type = bool_constant<false>;

} // namespace rav