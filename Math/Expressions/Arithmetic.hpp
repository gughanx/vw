#ifndef VW_MATH_EXPRESSIONS_ARITHMETIC_INCLUDED
#define VW_MATH_EXPRESSIONS_ARITHMETIC_INCLUDED

#include "../Concepts.hpp"

namespace vw::Math::Expressions
{

template <Concepts::Arithmetic A>
struct Add
{
    A Eval(A a, A b) const
    {
        return a + b;
    }
};

template <Concepts::Arithmetic A>
struct Subtract
{
    A Eval(A a, A b) const
    {
        return a - b;
    }
};

template <Concepts::Arithmetic A>
struct Multiply
{
    A Eval(A a, A b) const
    {
        return a * b;
    }
};

template <Concepts::Arithmetic A>
struct Divide
{
    A Eval(A a, A b) const
    {
        return a / b;
    }
};

} // namespace vw::Math::Expressions

#endif
