#pragma once
#include "Base.h"

class Derived : public Base
{
public:
protected:
    virtual String get_name() const override;

private:
    String _name = "Derived";
};

/*Размер 56 byte.
* Base:
*   Base{vfptr}  - 8 byte - указатель на таблицу виртуальных функций
*   size_t _id   - 8 byte
* Derived:
*   String _name - 40 byte
*/