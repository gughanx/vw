#ifndef VW_CORE_CONCEPTS_INCLUDED
#define VW_CORE_CONCEPTS_INCLUDED

namespace vw::Concepts
{

template <typename T>
concept bool ClassType = std::is_class<T>::value;

template <typename T, typename... Ts>
concept bool Convertible = std::conjunction<std::is_convertible<T, Ts>...>::value;

template <typename T, typename... Ts>
concept bool Same = std::conjunction<std::is_same<T, Ts>...>::value;

} // namespace vw::Concepts

#endif
