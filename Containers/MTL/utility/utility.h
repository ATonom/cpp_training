#pragma once
#include <iostream>


using SizeT = std::size_t;

// Объект данного типа можно передавать в std::ostream при помощи оператора<<.
template <typename T>
concept conc_os_printable = requires(T t, std::ostream & os) {
    { os << t } -> std::same_as<std::ostream&>;
};

namespace mtl
{

//  iostream  ##############################

inline void print() {};

template <conc_os_printable T, conc_os_printable... Args>
inline void print(const T& first, const Args&... rest)
{
    std::cout << first;
    print(rest...);
}

}

