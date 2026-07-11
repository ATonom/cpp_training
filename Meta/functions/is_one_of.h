#pragma once
#include "traits.h"

namespace rav
{

/*
 * Проверяет есть ли среди типов Args тип T.
 */
template <typename T, typename... Args>
struct is_one_of;

/*
 * Вызывается если в is_one_of передать только один тип T, а так же
 * если среди Args нет типа равного Т.
 */
template <typename T>
struct is_one_of<T> : false_type
{
};

/*
* Вызывается если первый тип из Args равен Т.
*/
template <typename T, typename... Args>
struct is_one_of<T, T, Args...> : true_type
{
};

/*
* Разворачивает Args, если первый тип из Args не равен Т.
*/
template <typename T, typename F, typename... Args>
struct is_one_of<T, F, Args...> : is_one_of<T, Args...>
{
};

/*
 * Проверяет есть ли среди типов Args тип T.
 */
template <typename T, typename... Args>
bool is_one_of_v = is_one_of<T, Args...>::value;

} // namespace rav