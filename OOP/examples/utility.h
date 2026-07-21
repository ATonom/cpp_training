#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cstdint>
#include <typeinfo>

//  string  ################################

using String = std::string;


//  vector  ################################

template <typename T>
using TVector = std::vector<T>;


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
using TShared_Ptr = std::shared_ptr<Ty>;

template <typename Ty>
using TWeak_Ptr = std::weak_ptr<Ty>;


template <typename T>
TShared_Ptr<T> make_sh_ptr()
{
    //print("Make shared pointer: ", typeid(T).name(), ".\n");
    return std::make_shared<T>();
}