#pragma once

#ifdef POLIMORPHISM
    #include "Polimorphism.h"
#endif // POLIMORPHISM

#ifdef INHERITANCE
    #include "Inheritance.h"
#endif // INHERITANCE

#ifdef PATTERN_VISITOR
    #include "Visitor.h"
#endif // PATTERN_VISITOR

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

#ifdef PATTERN_VISITOR
    vis::do_visitor();
#endif // PATTERN_VISITOR
}
} // namespace examples
