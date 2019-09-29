#ifndef VW_MATH_EXPRESSIONS_VECTOR_INCLUDED
#define VW_MATH_EXPRESSIONS_VECTOR_INCLUDED

#include "../Concepts.hpp"
#include "Arithmetic.hpp"

namespace vw::Math::Expressions
{

template <Concepts::VectorExpression E, typename Op>
class VectorArithmeticExpression : public Op
{
  public:
    typedef typename E::ElementType ElementType;

    VectorArithmeticExpression(const E &e, typename E::ElementType a) : e_(e), a_(a)
    {}

    ElementType operator[](size_t i) const
    {
        return Op::Eval(e_[i], a_);
    }

    static constexpr size_t size()
    {
        return E::size();
    }

  private:
    const E &                     e_;
    const typename E::ElementType a_;
};

template <Concepts::VectorExpression E1, Concepts::VectorExpression E2, typename Op>
    requires Concepts::Same<typename E1::ElementType, typename E2::ElementType> &&
    (E1::size() == E2::size()) class VectorVectorExpression : public Op
{
  public:
    typedef typename E1::ElementType ElementType;

    VectorVectorExpression(const E1 &a, const E2 &b) : a_(a), b_(b)
    {}

    ElementType operator[](size_t i) const
    {
        return Op::Eval(a_[i], b_[i]);
    }

    static constexpr size_t size()
    {
        return E1::size();
    }

  private:
    const E1 &a_;
    const E2 &b_;
};

} // namespace vw::Math::Expressions

#endif
