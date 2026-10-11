#pragma once
#include "utility.h"

namespace vis
{

void do_visitor();


struct Visitor;

struct BaseStruct
{
    virtual void assept(Visitor& v) = 0;
    virtual ~BaseStruct() = default;
};

struct FirstDerivedStruct : BaseStruct
{
    int value = 0;
    void assept(Visitor& v) override;
};

struct SecondDerivedStruct : BaseStruct
{
    float value = 0.0f;
    void assept(Visitor& v) override;
};

struct ThirdDerivedStruct : BaseStruct
{
    String value = "0";
    void assept(Visitor& v) override;
};

struct Visitor
{
    virtual void visit(FirstDerivedStruct& s) = 0;
    virtual void visit(SecondDerivedStruct& s) = 0;
    virtual void visit(ThirdDerivedStruct& s) = 0;
};

struct PrintTypeVisitor : Visitor
{
    void visit(FirstDerivedStruct& s) override;
    void visit(SecondDerivedStruct& s) override;
    void visit(ThirdDerivedStruct& s) override;
};

struct PrintValueVisitor : Visitor
{
    void visit(FirstDerivedStruct& s) override;
    void visit(SecondDerivedStruct& s) override;
    void visit(ThirdDerivedStruct& s) override;
};


}