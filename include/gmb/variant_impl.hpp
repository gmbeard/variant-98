#ifndef VARIANT_GMB_VARIANT_IMPL_HPP_INCLUDED
#define VARIANT_GMB_VARIANT_IMPL_HPP_INCLUDED

#include "gmb/type_list.hpp"
#include "gmb/detail/type_list_utils.hpp"
#include "gmb/detail/type_traits.hpp"

namespace gmb {

template<typename TList>
struct VariantStorage {
    union {
        double align_;
        char data[detail::max_size_of<TList>::value];
    };
};

template<typename TList, typename U>
size_t copy_construct_storage_with(VariantStorage<TList>& s,
                                   U const& val)
{
    ::new (static_cast<void*>(s.data)) U(val);
    return detail::index_of_type<TList, U>::value;
}

template<typename TList>
size_t default_construct(VariantStorage<TList>& s) {
    typedef typename detail::type_at_index<TList, 0>::type FirstType;
    ::new (static_cast<void*>(s.data)) FirstType();
    return 0;
}

template<typename T, typename V>
typename detail::RemoveReference<V>::type::return_type 
dispatch_proxy(char* storage, V v) {
    return v(*reinterpret_cast<T*>(storage));
}

template<typename T, typename V>
typename detail::RemoveReference<V>::type::return_type 
dispatch_proxy_const(char const* storage, V v) {
    return v(*reinterpret_cast<T*>(storage));
}

template<typename TList, 
         typename V, 
         typename Function,
         bool Const,
         size_t I = 0, 
         size_t N = detail::type_count_of<TList>::value>
struct DispatchGenerator { };

template<typename H, 
         typename T, 
         typename F, 
         bool Const, 
         typename V, 
         size_t I, 
         size_t N>
struct DispatchGenerator<TypeList<H, T>, V, F, Const, I, N> :
    DispatchGenerator<T, V, F, Const, I + 1, N> 
{
private:
    typedef DispatchGenerator<T, V, F, Const, I + 1, N> Base;
    struct ConstDispatcherTag { };
    struct NonConstDispatcherTag { };
    typedef typename 
        detail::Conditional<Const, 
                            ConstDispatcherTag,
                            NonConstDispatcherTag>::type Tag;

    static void gen_(F (&table)[N], NonConstDispatcherTag) throw() {
        table[I] = &dispatch_proxy<H, V>;
    }

    static void gen_(F (&table)[N], ConstDispatcherTag) throw() {
        table[I] = &dispatch_proxy_const<H const, V>;
    }

public:
    static void gen(F (&table)[N]) throw() {
        gen_(table, Tag()); 
        Base::gen(table);
    }
};

template<typename V, typename F, bool Const, size_t I, size_t N>
struct DispatchGenerator<TypeListEnd, V, F, Const, I, N> {
public: 
    static void gen(F (&)[N]) throw() { }
};

template<typename TList, typename V, bool Const = false>
struct Dispatcher {
private:
    enum { list_size = detail::type_count_of<TList>::value };
    typedef typename detail::Conditional<Const, char const*, char*>::type Data;
    typedef typename detail::RemoveReference<V>::type::return_type ReturnType;
    typedef ReturnType (*Function)(Data, V&);
    typedef DispatchGenerator<TList, V, Function, Const> Generator;

public:
    static ReturnType dispatch(Data storage, 
                               size_t type_index, 
                               V visitor) {
        Function table[detail::type_count_of<TList>::value]; 
        Generator::gen(table);
        return (table[type_index])(storage, visitor);
    }
};

template<typename TList, typename V>
void visitor_proxy(VariantStorage<TList>& s, 
                   size_t type_index, 
                   V& visitor) 
{
    Dispatcher<TList, V&>::dispatch(s.data, type_index, visitor);
}

template<typename TList, typename V>
void visitor_proxy(VariantStorage<TList>& s, 
                   size_t type_index, 
                   V const& visitor) 
{
    Dispatcher<TList, V const&>::dispatch(s.data, type_index, visitor);
}

template<typename TList, typename V>
void visitor_proxy(VariantStorage<TList> const& s, 
                   size_t type_index, 
                   V& visitor) 
{
    Dispatcher<TList, V&, true>::dispatch(s.data, type_index, visitor);
}

template<typename TList, typename V>
void visitor_proxy(VariantStorage<TList> const& s, 
                   size_t type_index, 
                   V const& visitor) 
{
    Dispatcher<TList, V const&, true>::dispatch(s.data, type_index, visitor);
}

} // End gmb

#endif // VARIANT_GMB_VARIANT_IMPL_HPP_INCLUDED
