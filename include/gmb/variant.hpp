#ifndef VARIANT_GMB_VARIANT_HPP_INCLUDED
#define VARIANT_GMB_VARIANT_HPP_INCLUDED

#include "gmb/type_list.hpp"

namespace gmb {

template<typename TList>
struct Variant {
    typedef TList type_list;

    Variant() throw();
    Variant(Variant const&);
    template<typename U>
    Variant(U const&);
    ~Variant();

    Variant& operator=(Variant const&);

    friend void swap(Variant&, Variant&) throw();

    friend bool operator==(Variant const&, Variant const&) throw();
    friend bool operator<(Variant const&, Variant const&) throw();

    size_t type_index() const;

    template<typename U>
    bool holds_alternative() const throw();

    template<size_t I>
    typename type_at_index<type_list, I>::type& get();

    template<size_t I>
    typename type_at_index<type_list, I>::type const& get() const;

    template<typename U>
    U& get();

    template<typename U>
    U const& get() const;

//    template<typename U>
//    U* get();
//
//    template<typename U>
//    U const* get() const;

    template<typename V>
    typename V::return_type visit(V&);

    template<typename V>
    typename V::return_type visit(V const&) const;
};

template<typename TList>
bool operator==(Variant<TList> const& lhs, 
                Variant<TList> const& rhs) throw() 
{
    return !(lhs == rhs);
}

template<typename TList>
bool operator<=(Variant<TList> const& lhs, 
               Variant<TList> const& rhs) throw() 
{
    return (lhs < rhs) || (lhs == rhs);
}

template<typename TList>
bool operator>(Variant<TList> const& lhs, 
               Variant<TList> const& rhs) throw() 
{
    return !(lhs <= rhs);
}

template<typename TList>
bool operator>=(Variant<TList> const& lhs, 
               Variant<TList> const& rhs) throw() 
{
    return !(lhs < rhs);
}

template<size_t I, typename TList>
typename type_at_index<TList, I>::type& get(Variant<TList>& v) {
    return v.get<I>();
}

template<size_t I, typename TList>
typename type_at_index<TList, I>::type const& get(Variant<TList> const& v) {
    return v.get<I>();
}

template<typename U, typename TList>
U& get(Variant<TList>& v) {
    return v.get<U>();
}

template<typename U, typename TList>
U const& get(Variant<TList> const& v) {
    return v.get<U>();
}

template<typename U, typename TList>
bool holds_alternative(Variant<TList> const& v) {
    return v.holds_alternative<U>();
}

} // End gmb

#endif // VARIANT_GMB_VARIANT_HPP_INCLUDED
