#ifndef VARIANT_GMB_TYPE_LIST_HPP_INCLUDED
#define VARIANT_GMB_TYPE_LIST_HPP_INCLUDED

#define GMB_TL1(T) \
    ::gmb::TypeList<T, ::gmb::TypeListEnd>
#define GMB_TL2(T1, T2) \
    ::gmb::TypeList<T1, GMB_TL1(T2) >
#define GMB_TL3(T1, T2, T3) \
    ::gmb::TypeList<T1, GMB_TL2(T2, T3) >
#define GMB_TL4(T1, T2, T3, T4) \
    ::gmb::TypeList<T1, GMB_TL3(T2, T3, T4) >
#define GMB_TL5(T1, T2, T3, T4, T5) \
    ::gmb::TypeList<T1, GMB_TL4(T2, T3, T4, T5) >
#define GMB_TL6(T1, T2, T3, T4, T5, T6) \
    ::gmb::TypeList<T1, GMB_TL5(T2, T3, T4, T5, T6) >
#define GMB_TL7(T1, T2, T3, T4, T5, T6, T7) \
    ::gmb::TypeList<T1, GMB_TL6(T2, T3, T4, T5, T6, T7) >
#define GMB_TL8(T1, T2, T3, T4, T5, T6, T7, T8) \
    ::gmb::TypeList<T1, GMB_TL7(T2, T3, T4, T5, T6, T7, T8) >
#define GMB_TL9(T1, T2, T3, T4, T5, T6, T7, T8, T9) \
    ::gmb::TypeList<T1, GMB_TL8(T2, T3, T4, T5, T6, T7, T8, T9) >

namespace gmb {

struct TypeListEnd { };

template<typename Head, typename Tail>
struct TypeList;

} // End gmb

#endif // VARIANT_GMB_TYPE_LIST_HPP_INCLUDED
