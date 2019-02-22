#ifndef VARIANT_GMB_DETAIL_TYPE_TRAITS_HPP_INCLUDED
#define VARIANT_GMB_DETAIL_TYPE_TRAITS_HPP_INCLUDED

namespace gmb {
namespace detail {

template<typename T>
struct RemoveReference { typedef T type; };

template<typename T>
struct RemoveReference<T&> { typedef T type; };

template<typename T>
struct RemovePointer { typedef T type; };

template<typename T>
struct RemovePointer<T*> { typedef T type; };

template<typename T>
struct IsConst { enum { value = false }; };

template<typename T>
struct IsConst<T const> { enum { value = true }; };

template<typename T>
struct IsConstPointer { enum { value = false }; };

template<typename T>
struct IsConstPointer<T*> { enum { value = IsConst<T>::value }; };

template<typename T>
struct IsConstReference { enum { value = false }; };

template<typename T>
struct IsConstReference<T&> { enum { value = IsConst<T>::value }; };

template<bool Cond, typename TrueType, typename FalseType>
struct Conditional { typedef TrueType type; };

template<typename TrueType, typename FalseType>
struct Conditional<false, TrueType, FalseType> { typedef FalseType type; };

template<bool Cond, typename T = void>
struct EnableIf { };

template<typename T>
struct EnableIf<true, T> { typedef T type; };

template<typename T, typename U>
struct IsSame { enum { value = false }; };

template<typename T>
struct IsSame<T, T> { enum { value = true }; };

}
}

#endif // VARIANT_GMB_DETAIL_TYPE_TRAITS_HPP_INCLUDED
