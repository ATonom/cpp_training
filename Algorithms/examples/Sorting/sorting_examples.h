#pragma once
#include "utility.h"
#include "sorting_func.h"

namespace sort
{

inline void do_sorting_example_1()
{
    print("[Example of using the std::sort function] \n");

    
    std::vector<int> vec{ 1, 4, 7, 3, 6, 8, 9, 23, 7, 8, 2, 56, 67 };       // Исходный вектор <int>.
    //std::vector<double> vec{ 1.23, 4.0, 7.65, 3.0, 6.0, 8.0, 9.0, 23.0, };  // Исходный вектор <double>.
    //std::vector<std::string> vec{ "A", "r", "word", "string", "String" };   // Исходный вектор <std::string>.
    
    using vec_type = decltype(*vec.data());
    print("Unsorted vector<", typeid(vec_type).name(), ">:", "\n");
    print_vector(vec);

    do_sort(vec);                               // Сортировка по умолчанию.
    do_sort(vec, lambda_func_higher<vec_type>); // Сортировка при помощи лямда функции.
    do_sort(vec, func_higher<vec_type>);        // Сортировка при помощи функции.
    do_sort(vec, functor_higher<vec_type>());   // Сортировка при помощи класса-функции.

    // test(2, 1, func_higher<int>);  // корректный вызов
    // test(2.0, 1, func_higher<int>);  // !корректный вызов
}

} // namespace sort
