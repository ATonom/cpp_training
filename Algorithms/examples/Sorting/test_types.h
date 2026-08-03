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
    void set_value(T& new_value);

    template <conc_os_printable U>
    friend std::ostream& operator<<(std::ostream& os, const test_type<U>& tt);

    bool operator>(const test_type<T>& tt) const;
    bool operator<(const test_type<T>& tt) const;

private:
    T value;
};

template <typename T>
inline const T& test_type<T>::get_value() const
{
    return value;
}

template <typename T>
inline void test_type<T>::set_value(T& new_value)
{
    value = new_value;
}

template <typename T>
inline bool test_type<T>::operator>(const test_type<T>& tt) const
{
    return value > tt.value;
}

template <typename T>
inline bool test_type<T>::operator<(const test_type<T>& tt) const
{
    return value < tt.value;
}

template <conc_os_printable U>
std::ostream& operator<<(std::ostream& os, const test_type<U>& tt)
{
    os << tt.value;
    return os;
}

} // namespace sort