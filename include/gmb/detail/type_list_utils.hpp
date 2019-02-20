#ifndef VARIANT_GMB_TYPE_LIST_UTILS_HPP_INCLUDED
#define VARIANT_GMB_TYPE_LIST_UTILS_HPP_INCLUDED

#include "gmb/type_list.hpp"
#include <stddef.h>

namespace gmb {
namespace detail {

template<typename TList, size_t I, size_t N = 0>
struct type_at_index { };

template<size_t I, size_t N>
struct type_at_index<TypeListEnd, I, N> { };

template<typename H, typename T, size_t I, size_t N>
struct type_at_index<TypeList<H, T>, I, N> {
private:
    typedef typename type_at_index<T, I, N+1>::type next_type;
public:
    typedef next_type type;
};

template<typename H, typename T, size_t I>
struct type_at_index<TypeList<H, T>, I, I> {
    typedef H type;
};

template<typename TList, typename T, size_t I = 0>
struct index_of_type { };

template<typename T, size_t I>
struct index_of_type<TypeListEnd, T, I> { };

template<typename H, typename T, typename U, size_t I>
struct index_of_type<TypeList<H, T>, U, I> {
private:
    enum { next_value = index_of_type<T, U, I+1>::value };
public:
    enum { value = next_value };
};

template<typename H, typename T, size_t I>
struct index_of_type<TypeList<H, T>, H, I> {
    enum { value = I };
};

template<typename TList>
struct max_size_of { };

template<>
struct max_size_of<TypeListEnd> { enum { value = 0 }; };

template<typename H, typename T>
struct max_size_of<TypeList<H, T> > {
private:
    enum { next_size = max_size_of<T>::value };
public:
    enum { value = sizeof(H) > next_size ? sizeof(H) : next_size };
};

template<typename TList, size_t N = 0>
struct type_count_of { };

template<size_t N>
struct type_count_of<TypeListEnd, N> { enum { value = 0 }; };

template<typename H, typename T, size_t N>
struct type_count_of<TypeList<H, T>, N> {
private:
    enum { next_count = type_count_of<T, N+1>::value };
public:
    enum { value = 1 + next_count };
};

}
}

#endif // VARIANT_GMB_TYPE_LIST_UTILS_HPP_INCLUDED
