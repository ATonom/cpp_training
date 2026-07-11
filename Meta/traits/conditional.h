#pragma once
#include "traits_utility.h"

namespace rav
{

template <bool B, typename T, typename F>
struct conditional : type_is<T>
{
};

template <typename T, typename F>
struct conditional<false, T, F> : type_is<F>
{
};

template <bool B, typename T, typename F>
using conditional_t = typename conditional<B, T, F>::type;

} // namespace rav