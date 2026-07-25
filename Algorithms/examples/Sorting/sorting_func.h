#pragma once
#include "utility.h"
#include "predicates.h"

namespace sort
{

// Пример использования функции std::sort по умолчанию (при помощи оператора "<").
template <typename T>
void do_sort(const std::vector<T>& vec, std::string msg = "std::sort(begin, end) result:")
{
    print("\n", msg, "\n");

    auto vec1 = vec;
    std::sort(vec1.begin(), vec1.end());

    print_vector(vec1);
}

// Пример использования функции std::sort при помощи предиката (компаратора). 
template <typename T, conc_binary_comp<T> F>
void do_sort(const std::vector<T>& vec, F comp, std::string msg = "std::sort(begin, end, comp) result:")
{
    print("\n", msg, "\n");

    auto vec1 = vec;
    std::sort(vec1.begin(), vec1.end(), comp);

    print_vector(vec1);
}


} // namespace sort