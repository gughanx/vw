#ifndef VW_MATH_VECTOR_INCLUDED
#define VW_MATH_VECTOR_INCLUDED

#include <cmath>
#include <cstring>
#include <iostream>

#include "Concepts.hpp"
#include "Expressions/Vector.hpp"

namespace vw::Math
{
template <Concepts::Arithmetic T, size_t N>
class Vector
{
  public:
    typedef T ElementType;

  public:
    Vector()
    {
        std::memset(v_, 0, sizeinbytes());
    }

    Vector(const Vector &v2)
    {
        std::memcpy(v_, v2.v_, sizeinbytes());
    }

    Vector(Vector &&v2)
    {
        std::swap(v_, v2.v_);
    }

    // clang-format off
    template <typename T2>
    requires Concepts::Convertible<T, T2>
    Vector(const Vector<T2, N> &v2) // clang-format on
    {
        for (size_t i = 0; i < N; ++i)
        {
            v_[i] = static_cast<T>(v2[i]);
        }
    }

    // clang-format off
    template <typename... Ts>
    requires (sizeof...(Ts) == N) && Concepts::Same<T, Ts...>
    Vector(Ts const &... args) : v_{args...} // clang-format on
    {}

    // clang-format off
    template <typename... Ts>
    requires (sizeof...(Ts) == N) && !Concepts::Same<T, Ts...> && Concepts::Convertible<T, Ts...>
    Vector(Ts const &... args) : v_{static_cast<T>(args)...} // clang-format on
    {}

    Vector(const Concepts::VectorExpression &expr)
    {
        static_assert(expr.size() == size());
        std::cout << typeid(expr).name() << std::endl;
        for (size_t i = 0; i < N; ++i)
        {
            v_[i] = expr[i];
        }
    }

    const Vector &operator=(const Concepts::VectorExpression &expr)
    {
        static_assert(expr.size() == size());
        std::cout << typeid(expr).name() << std::endl;
        for (size_t i = 0; i < N; ++i)
        {
            v_[i] = expr[i];
        }
        return *this;
    }

    T operator[](const size_t i) const
    {
        checkIndex(i);
        return v_[i];
    }

    static constexpr size_t size()
    {
        return N;
    }

    static constexpr size_t sizeinbytes()
    {
        return N * sizeof(T);
    }

    T dot(const Vector &v2) const
    {
        T dot = static_cast<T>(0);
        for (size_t i = 0; i < N; ++i)
            dot += v_[i] * v2[i];
        return dot;
    }

    T norm() const
    {
        return static_cast<T>(std::sqrt(dot(*this)));
    }

    void normalize()
    {
        T n = norm();
        if (n != static_cast<T>(0))
            for (size_t i = 0; i < N; ++i)
                v_[i] /= n;
    }

    Vector normalized() const
    {
        Vector n(*this);
        n.normalize();
        return n;
    }

  private:
    void checkIndex(const size_t i) const
    {
#ifdef VW_DEBUG
        if (i >= N)
            throw std::runtime_error("Vector index out of bounds!");
#endif
    }

    T v_[N];
};

template <Concepts::VectorExpression E>
auto operator+(const E &e, typename E::ElementType a)
{
    using namespace vw::Math::Expressions;
    return VectorArithmeticExpression<E, Add<typename E::ElementType>>(e, a);
}

template <Concepts::VectorExpression E>
auto operator-(const E &e, typename E::ElementType a)
{
    using namespace vw::Math::Expressions;
    return VectorArithmeticExpression<E, Subtract<typename E::ElementType>>(e, a);
}

template <Concepts::VectorExpression E>
auto operator*(const E &e, typename E::ElementType a)
{
    using namespace vw::Math::Expressions;
    return VectorArithmeticExpression<E, Multiply<typename E::ElementType>>(e, a);
}

template <Concepts::VectorExpression E>
auto operator/(const E &e, typename E::ElementType a)
{
    using namespace vw::Math::Expressions;
    return VectorArithmeticExpression<E, Divide<typename E::ElementType>>(e, a);
}

template <Concepts::VectorExpression E1, Concepts::VectorExpression E2>
auto operator+(const E1 &a, const E2 &b)
{
    using namespace vw::Math::Expressions;
    return VectorVectorExpression<E1, E2, Add<typename E1::ElementType>>(a, b);
}

template <Concepts::VectorExpression E1, Concepts::VectorExpression E2>
auto operator-(const E1 &a, const E2 &b)
{
    using namespace vw::Math::Expressions;
    return VectorVectorExpression<E1, E2, Subtract<typename E1::ElementType>>(a, b);
}

typedef Vector<int, 2>          Vector2i;
typedef Vector<int, 3>          Vector3i;
typedef Vector<int, 4>          Vector4i;
typedef Vector<unsigned int, 2> Vector2u;
typedef Vector<unsigned int, 3> Vector3u;
typedef Vector<unsigned int, 4> Vector4u;
typedef Vector<float, 2>        Vector2f;
typedef Vector<float, 3>        Vector3f;
typedef Vector<float, 4>        Vector4f;
typedef Vector<double, 2>       Vector2d;
typedef Vector<double, 3>       Vector3d;
typedef Vector<double, 4>       Vector4d;

std::ostream &operator<<(std::ostream &out, const Concepts::VectorExpression &v)
{
    out << "[";
    for (size_t i = 0; i < v.size(); ++i)
        out << ((i == 0) ? "" : ", ") << v[i];
    out << "]";
    return out;
}

} // namespace vw::Math

#endif
