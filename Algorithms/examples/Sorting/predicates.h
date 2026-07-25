#pragma once
#include "utility.h"


namespace sort
{
// Функция - бинарный предикат (компаратор). Возвращает bool (a > b).
template <conc_op_greater T>
bool func_higher(const T& a, const T& b)
{
    return a > b;
}

// Лямбда функция - бинарный предикат (компаратор). Возвращает bool (a > b).
template <conc_op_greater T>
auto lambda_func_higher = [](const T& a, const T& b) -> bool { return a > b; };

// Функтор - бинарный предикат (компаратор). Возвращает bool (a > b).
template <conc_op_greater T>
class functor_higher
{
public:
    bool operator()(const T& a, const T& b) const { return a > b; }
};
} // namespace sort