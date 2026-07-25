#pragma once
#include "utility.h"
#include "sorting_func.h"

namespace sort
{

inline void do_sorting_examples()
{
    print("[Sorting] \n");

    // Исходный вектор <int>.
    std::vector<int> vec{ 1, 4, 7, 3, 6, 8, 9, 23, 7, 8, 2, 56, 67 };
    using vec_type = decltype(*vec.data());
    const std::string vec_type_name = typeid(vec_type).name();

    print("Unsorted vector<", vec_type_name, ">:", "\n");
    print_vector(vec);

    do_sort(vec);                               // Сортировка по умолчанию.
    do_sort(vec, lambda_func_higher<vec_type>); // Сортировка при помощи лямда функции.
    do_sort(vec, func_higher<vec_type>);        // Сортировка при помощи функции.
    do_sort(vec, functor_higher<vec_type>());   // Сортировка при помощи класса-функции.
}

} // namespace sort
