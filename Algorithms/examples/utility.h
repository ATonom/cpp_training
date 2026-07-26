#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cstdint>
#include <typeinfo>
#include <algorithm>
#include <concepts>


//  iostream  ##############################

inline void print() {};

template <typename T, typename... Args>
inline void print(const T& first, const Args&... rest)
{
    std::cout << first;
    print(rest...);
}

template <typename T>
void print_vector(std::vector<T> vec)
{
    if (vec.empty()) return;

    for (auto& v : vec)
    {
        print(v, " ");
    }
    print("\n");
}

//  My concepts  ##############################

//Объекты данного типа можно сравнить при помощи оператора< (возвращает bool).
template <typename T>
concept conc_op_less = requires(T a, T b) {
    { a < b } -> std::same_as<bool>;
};

// Объекты данного типа можно сравнить при помощи оператора> (возвращает bool).
template <typename T>
concept conc_op_greater = requires(T a, T b) {
    { a > b } -> std::same_as<bool>;
};

// Объект данного типа можно вызвать при помощи оператора() (возвращает bool).
template< typename F, typename T>
concept conc_binary_comp = requires(F f, T a, T b) {
    { f(a, b) } -> std::same_as<bool>;
};


// Тестовый составной концепт
template <typename F, typename T>
concept conc_test = conc_binary_comp<F, T> && conc_op_greater<T>;


template <typename F, typename T>
requires conc_test<F,T>
bool test(T a, T b, F f)
{
    return f(a, b);
}