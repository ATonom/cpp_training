#pragma once
#include "utility.h"
#include "Base.h"
#include "Derived.h"

namespace pmm
{
inline void polimorphism()
{
    print("[Polimorphism]", "\n");

    Base base1; // Объект класса Base.
    base1.print_name();

    Base base2 = Derived(); // Объект класса Base, свойства класса Derived отброшены.
    base2.print_name();

    Derived derived1; // Объект класса Derived.
    derived1.print_name();

    TVector<TShared_Ptr<Base>> vec;
    vec.push_back(make_sh_ptr<Base>());
    vec.push_back(make_sh_ptr<Base>());
    vec.push_back(make_sh_ptr<Derived>());
    vec.push_back(make_sh_ptr<Derived>());

    print("Vector:", "\n");
    for (auto& b : vec)
    {
        if (b) b->print_name(); // Магия полиморфизма. Динамическое связывание (умный указатель).
    }

    Base* p_base3 = new Derived();
    print("Pointer:", "\n");
    p_base3->print_name(); // Магия полиморфизма. Динамическое связывание (простой указатель).
    delete p_base3;
    p_base3 = nullptr;

    print("Reference:", "\n");
    Base& r_base4 = derived1;
    r_base4.print_name(); // Магия полиморфизма. Динамическое связывание (ссылка).

    print("Number of instances created: ", Base::get_count());
}
}
