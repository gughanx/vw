#ifndef VW_MATH_CONCEPTS_INCLUDED
#define VW_MATH_CONCEPTS_INCLUDED

#include "../Core/Concepts.hpp"

namespace vw::Concepts
{

template <typename T>
concept bool Arithmetic = std::is_arithmetic<T>::value;

template <typename T>
concept bool VectorExpression = requires(T a, size_t index)
{
    {
        a[index]
    }
    ->Arithmetic;
    {
        T::size()
    }
    ->size_t;
    typename T::ElementType;
};

} // namespace vw::Concepts

#endif
