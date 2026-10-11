#include "Visitor.h"

using namespace vis;

void vis::do_visitor() {
    
    TVector<BaseStruct*> vec;
    vec.push_back(new FirstDerivedStruct());
    vec.push_back(new SecondDerivedStruct());
    vec.push_back(new ThirdDerivedStruct());

    for (auto v : vec)
    {
        PrintTypeVisitor ptv;
        PrintValueVisitor pvv;
        v->assept(ptv);
        v->assept(pvv);
    }
}

using namespace vis;

void FirstDerivedStruct::assept(Visitor& v) 
{
    v.visit(*this);
}

void SecondDerivedStruct::assept(Visitor& v) 
{
    v.visit(*this);
}

void ThirdDerivedStruct::assept(Visitor& v) 
{
    v.visit(*this);
}

void PrintTypeVisitor::visit(FirstDerivedStruct& s) 
{
    print("First Derived Struct \n");
}

void PrintTypeVisitor::visit(SecondDerivedStruct& s)
{
    print("Second Derived Struct \n");
}

void PrintTypeVisitor::visit(ThirdDerivedStruct& s)
{
    print("Third Derived Struct \n");
}

void PrintValueVisitor::visit(FirstDerivedStruct& s) 
{
    print(s.value, "\n");
}

void PrintValueVisitor::visit(SecondDerivedStruct& s) 
{
    print(s.value, "\n");
}

void PrintValueVisitor::visit(ThirdDerivedStruct& s) 
{
    print(s.value, "\n");
}
