#pragma once
#include "utility.h"

class Base
{
public:
    Base() { _id = _count++; };
    void print_name() const;
    static size_t get_count() { return _count; };

protected:
    virtual String get_name() const;

private:
    static size_t _count;
    size_t _id;
};

/*Размер 16 byte.
* Base:
*   Base{vfptr} - 8 byte - указатель на таблицу виртуальных функций
*   size_t _id - 8 byte 
*/