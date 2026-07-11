#pragma once
#include "traits_utility.h"

namespace rav
{

template <typename T>
struct remove_const : type_is<T>
{
};

template <typename T>
struct remove_const<const T> : type_is<T>
{
};

template <typename T>
using remove_const_t = typename remove_const<T>::type;

} // namespace rav