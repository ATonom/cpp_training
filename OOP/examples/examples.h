#pragma once

#ifdef POLIMORPHISM
    #include "Polimorphism.h"
#endif // POLIMORPHISM

#ifdef INHERITANCE
    #include "Inheritance.h"
#endif // INHERITANCE

namespace examples
{
inline void do_examples()
{
#ifdef POLIMORPHISM
    pmm::polimorphism();
#endif // POLIMORPHISM

#ifdef INHERITANCE
    inh::inheritance();
#endif // INHERITANCE
}
} // namespace examples
