#pragma once

/*
* Структуры необходимые для упрощения написания метафункций.
*/

namespace rav
{

/*
* Добавляет поле type = T.
*/
template <typename T>
struct type_is
{
    using type = T;
};

/*
 * Добавляет поле T value = v.
 */
template <typename T , T v>
struct value_is
{
    static T value = v;
};

} // namespace rav
