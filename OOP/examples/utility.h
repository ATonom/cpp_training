#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>

//  string  ################################
using String = std::string;

//  vector  ################################
template <typename T>
using Vector = std::vector<T>;

//  iostream  ##############################
inline void print() {};

template <typename T, typename... Args>
inline void print(const T& first, const Args&... rest)
{
    std::cout << first;
    print(rest...);
}

//  memory  ##############################
template <typename Ty>
using Shared_Ptr = std::shared_ptr<Ty>;


template <typename T>
Shared_Ptr<T> make_sh_ptr()
{
    return std::make_shared<T>();
}