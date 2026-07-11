#pragma once
#include "traits_utility.h"

namespace rav
{

template <bool B, typename T>
struct enable_if : type_is<T>
{
};

template <typename T>
struct enable_if<false, T>
{
};

/*
 * Вызов enable_if_t<false, T>, приводит к ошибке компиляции.
 * Данная конструкция необходима для реализации поведения SFINAE.
 */
template <bool B, typename T>
using enable_if_t = typename enable_if<B, T>::type;

} // namespace rav