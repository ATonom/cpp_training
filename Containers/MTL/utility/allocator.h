#pragma once
#include <utility>
#include "utility.h"

namespace mtl
{

// TODO
template <typename AllocType, typename T, typename... Args>
concept conc_alloc = requires(AllocType alloc, std::size_t n, T* ptr, Args&&... args)
{
    {
        alloc.allocate(n) &&
        alloc.deallocate(ptr, n) &&
        alloc.construct(ptr, args...) &&
        alloc.destroy(ptr, n)
    };
};




template <typename T>
class Allocator
{
public:

    using value_type = T;
    using size_type = std::size_t;


    constexpr Allocator() noexcept = default;

    template <typename U>
    constexpr Allocator(const Allocator<U>&) noexcept {};


    T* allocate(size_type n)
    {
        if (n > std::numeric_limits<size_type>::max() / sizeof(T))
            throw std::bad_alloc();

        auto ptr = static_cast<T*>(::operator new(n * sizeof(T)));
        if(!ptr) throw std::bad_alloc();

        print("Allocating ", n, " objects of type ", typeid(T).name(), ".\n");
        return ptr;
    }

    void deallocate(T* ptr, size_type n)
    {
        print("Deallocating ", n, " objects of type ", typeid(T).name(), ".\n");
        ::operator delete(ptr);
    }

    template <typename U, typename... Args>
    void construct(U* ptr, Args&&... args)
    {
        print("The ", typeid(T).name(), "-type object has been constructed.\n");
        new(ptr) U(std::forward<Args>(args)...);
    }

    template <typename U>
    void destroy(U* ptr, size_type) noexcept
    {
        print("The ", typeid(T).name(), "-type object has been destroyed.\n");
        ptr->~U();
    }

    template <typename U>
    struct rebind
    {
        using other = Allocator<U>;
    };

};

/*
template <typename T, typename AllocType = Allocator<T>>
class PrintAllocator : public AllocType
{
public:

    using value_type = T;
    using size_type = std::size_t;

    //constexpr PrintAllocator() noexcept = default;

    //template <typename U>
    //constexpr PrintAllocator(const PrintAllocator<U>&) noexcept {};

    T* allocate(size_type n)
    {
        print("Allocating ", n, " objects of type ", typeid(T).name(), ".\n");
        AllocType::allocate(n);
    }

    void deallocate(T* ptr, size_type n)
    {
        print("Deallocating ", n, " objects of type ", typeid(T).name(), ".\n");
        AllocType::deallocate(ptr, n);
    }

    template <typename U, typename... Args>
    void construct(U* ptr, Args&&... args)
    {
        print("The ", typeid(T).name(), "-type object has been constructed.\n");
        AllocType::construct(ptr, args);
    }

    template <typename U>
    void destroy(U* ptr, size_type) noexcept
    {
        print("The ", typeid(T).name(), "-type object has been destroyed.\n");
        AllocType::destroy(ptr);
    }

};
*/
}

