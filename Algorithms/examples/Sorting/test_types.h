#pragma once
#include "utility.h"


namespace sort
{
template <typename T>
class test_type
{
public:
    test_type() = default;
    explicit test_type(T new_value) : value(new_value) {};

    const T& get_value() const;

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const test_type<U>& tt);

private:
    T value;
};



template <typename T>
inline const T& test_type<T>::get_value() const
{
    return value;
}


template <typename U>
std::ostream& operator<<(std::ostream& os, const test_type<U>& tt)
{
    os << tt.value;
    return os;
}

} // namespace sort