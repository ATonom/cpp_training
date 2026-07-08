#pragma once
#include "Math/SG_MathFunc.h"

namespace SG
{

// A vector in 2-D space composed of components (x,y).
template <typename T>
struct TVector2
{
    T x, y;

    TVector2() = default;
    inline TVector2(T inX, T inY);
    explicit inline TVector2(T inValue);

    // Copy Constructor.
    explicit inline TVector2(const TVector2<T>& vector);

    // T& operator[](int Index);
    // T operator[](int Index) const;
    inline T length() const;
    // bool isZero() const;
    // std::string toString

    inline TVector2<T> operator+(const TVector2<T>& vector) const;
    inline TVector2<T> operator-(const TVector2<T>& vector) const;
    inline TVector2<T> operator*(const TVector2<T>& vector) const;
    inline TVector2<T> operator/(const TVector2<T>& vector) const;

    inline TVector2<T> operator+(T value) const;
    inline TVector2<T> operator-(T value) const;
    inline TVector2<T> operator*(T value) const;
    inline TVector2<T> operator/(T value) const;

    inline T operator|(const TVector2<T>& vector) const;
    inline T operator^(const TVector2<T>& vector) const;

    inline bool operator==(const TVector2<T>& vector) const;
    inline bool operator!=(const TVector2<T>& vector) const;
    inline bool operator<(const TVector2<T>& Other) const;
    inline bool operator>(const TVector2<T>& Other) const;
    // inline bool operator<=(const TVector2<T>& Other) const;
    // inline bool operator>=(const TVector2<T>& Other) const;

    inline TVector2<T> operator-() const;

    inline TVector2<T> operator+=(const TVector2<T>& vector);
    inline TVector2<T> operator-=(const TVector2<T>& vector);
    inline TVector2<T> operator*=(const TVector2<T>& vector);
    inline TVector2<T> operator/=(const TVector2<T>& vector);

    inline TVector2<T> operator+=(T value);
    inline TVector2<T> operator-=(T value);
    inline TVector2<T> operator*=(T value);
    inline TVector2<T> operator/=(T value);
};

template <typename T>
inline TVector2<T>::TVector2(T inX, T inY) : x(inX), y(inY){};

template <typename T>
inline TVector2<T>::TVector2(T inValue) : x(inValue), y(inValue){};

template <typename T>
inline TVector2<T>::TVector2(const TVector2<T>& vector) : x(vector.x), y(vector.y){};

template <typename T>
inline T TVector2<T>::length() const
{
    return sqrt(x * x + y * y);
}

template <typename T>
inline TVector2<T> TVector2<T>::operator+(const TVector2<T>& vector) const
{
    return TVector2<T>(x + vector.x, y + vector.y);
}

template <typename T>
inline TVector2<T> TVector2<T>::operator-(const TVector2<T>& vector) const
{
    return TVector2<T>(x - vector.x, y - vector.y);
}

template <typename T>
inline TVector2<T> TVector2<T>::operator*(const TVector2<T>& vector) const
{
    return TVector2<T>(x * vector.x, y * vector.y);
}

template <typename T>
inline TVector2<T> TVector2<T>::operator/(const TVector2<T>& vector) const
{
    return TVector2<T>(x / vector.x, y / vector.y);
}

template <typename T>
inline TVector2<T> TVector2<T>::operator+(T value) const
{
    return TVector2<T>(x + value, y + value);
}

template <typename T>
inline TVector2<T> TVector2<T>::operator-(T value) const
{
    return TVector2<T>(x - value, y - value);
}

template <typename T>
inline TVector2<T> TVector2<T>::operator*(T value) const
{
    return TVector2<T>(x * value, y * value);
}

template <typename T>
inline TVector2<T> TVector2<T>::operator/(T value) const
{
    return TVector2<T>(x / value, y / value);
}

template <typename T>
inline T TVector2<T>::operator|(const TVector2<T>& vector) const
{
    return x * vector.x + y * vector.y;
}

template <typename T>
inline T TVector2<T>::operator^(const TVector2<T>& vector) const
{
    return x * vector.y - y * vector.x;
}

template <typename T>
inline bool TVector2<T>::operator==(const TVector2<T>& vector) const
{
    return x == vector.x && y == vector.y;
}

template <typename T>
inline bool TVector2<T>::operator!=(const TVector2<T>& vector) const
{
    return x != vector.x || y != vector.y;
}

// ? Корректный ли данный оператор сравнения?
template <typename T>
inline bool TVector2<T>::operator<(const TVector2<T>& vector) const
{
    return x < vector.x && y < vector.y;
}
// ? Корректный ли данный оператор сравнения?
template <typename T>
inline bool TVector2<T>::operator>(const TVector2<T>& vector) const
{
    return x > vector.x && y > vector.y;
}

template <typename T>
inline TVector2<T> TVector2<T>::operator-() const
{
    return TVector2<T>(-x, -y);
}

template <typename T>
inline TVector2<T> TVector2<T>::operator+=(const TVector2<T>& vector)
{
    x += vector.x;
    y += vector.y;
    return *this;
}

template <typename T>
inline TVector2<T> TVector2<T>::operator-=(const TVector2<T>& vector)
{
    x -= vector.x;
    y -= vector.y;
    return *this;
}

template <typename T>
inline TVector2<T> TVector2<T>::operator*=(const TVector2<T>& vector)
{
    x *= vector.x;
    y *= vector.y;
    return *this;
}

template <typename T>
inline TVector2<T> TVector2<T>::operator/=(const TVector2<T>& vector)
{
    x /= vector.x;
    y /= vector.y;
    return *this;
}

 template <typename T>
 inline TVector2<T> TVector2<T>::operator+=(T value)
{
     x += value;
     y += value;
     return *this;
 }

 template <typename T>
 inline TVector2<T> TVector2<T>::operator-=(T value)
{
     x -= value;
     y -= value;
     return *this;
 }

 template <typename T>
 inline TVector2<T> TVector2<T>::operator*=(T value)
{
     x *= value;
     y *= value;
     return *this;
 }

 template <typename T>
 inline TVector2<T> TVector2<T>::operator/=(T value)
{
     x /= value;
     y /= value;
     return *this;
 }

} // namespace SG