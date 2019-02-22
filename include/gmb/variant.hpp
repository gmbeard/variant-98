#ifndef VARIANT_GMB_VARIANT_HPP_INCLUDED
#define VARIANT_GMB_VARIANT_HPP_INCLUDED

#include "gmb/detail/variant_storage.hpp"
#include "gmb/detail/variant_impl.hpp"
#include "gmb/detail/visitation.hpp"
#include "gmb/detail/type_traits.hpp"
#include <cassert>

namespace gmb {

template<typename TList>
struct Variant {
    typedef TList type_list;

    static const size_t type_npos = size_t(-1);

    Variant() throw() :
        type_index_(type_npos)
    {
        detail::default_construct(storage_);
    }

    Variant(Variant const& other) : 
        type_index_(type_npos)
    {
        type_index_ = 
            detail::visitor_proxy(
                other.storage_, 
                other.type_index_,
                detail::CopyConstructVisitor<TList>(storage_.data()));
    }

    template<typename U>
    Variant(U const& val,
            typename detail::EnableIf<
                !detail::IsSame<U, Variant>::value>::type* = 0) :
        type_index_(type_npos)
    {
        type_index_ = 
            detail::copy_construct_storage_with<TList>(storage_.data(), val);
    }

    ~Variant() {
        if (type_index_ != type_npos) {
            detail::visitor_proxy(
                storage_,
                type_index_,
                detail::DestructionVisitor(storage_.data()));
        }
    }

    Variant& operator=(Variant const& rhs) {
        this->~Variant();
        type_index_ = type_npos;
        type_index_ = 
            detail::visitor_proxy(
                rhs.storage_,
                rhs.type_index_,
                detail::CopyConstructVisitor<TList>(storage_.data()));
        return *this;
    }

//    friend void swap(Variant&, Variant&) throw();

//    friend bool operator==(Variant const&, Variant const&) throw();
//    friend bool operator<(Variant const&, Variant const&) throw();

    size_t type_index() const throw() { return type_index_; }

    template<typename U>
    bool holds_alternative() const throw() {
        return type_index_ == detail::index_of_type<TList, U>::value;
    }

    template<size_t I>
    typename detail::type_at_index<TList, I>::type& get() {
        typedef typename detail::type_at_index<TList, I>::type T;
        assert(type_index_ == I && "Accessing incorrect type!");
        return *reinterpret_cast<T*>(storage_.data());
    }

    template<size_t I>
    typename detail::type_at_index<TList, I>::type const& get() const {
        return const_cast<Variant&>(*this).get<I>();
    }

    template<typename U>
    U& get() {
        assert(holds_alternative<U>() &&
               "Accessing incorrect type!");
        return *reinterpret_cast<U*>(storage_.data());
    }

    template<typename U>
    U const& get() const {
        return const_cast<Variant&>(*this).get<U>();
    }

    template<typename V>
    typename V::return_type visit(V& visitor) {
        assert(type_index_ != type_npos &&
               "Visiting variant holding nothing!");
        return detail::visitor_proxy(storage_, type_index_, visitor);
    }

    template<typename V>
    typename V::return_type visit(V& visitor) const {
        assert(type_index_ != type_npos &&
               "Visiting variant holding nothing!");
        return detail::visitor_proxy(storage_, type_index_, visitor);
    }

    template<typename V>
    typename V::return_type visit(V const& visitor) {
        assert(type_index_ != type_npos &&
               "Visiting variant holding nothing!");
        return detail::visitor_proxy(storage_, type_index_, visitor);
    }

    template<typename V>
    typename V::return_type visit(V const& visitor) const {
        assert(type_index_ != type_npos &&
               "Visiting variant holding nothing!");
        return detail::visitor_proxy(storage_, type_index_, visitor);
    }

private:
    detail::VariantStorage<TList> storage_;
    size_t type_index_;
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
typename detail::type_at_index<TList, I>::type& get(Variant<TList>& v) {
    return v.template get<I>();
}

template<size_t I, typename TList>
typename detail::type_at_index<TList, I>::type const& get(
    Variant<TList> const& v) 
{
    return v.template get<I>();
}

template<typename U, typename TList>
U& get(Variant<TList>& v) {
    return v.template get<U>();
}

template<typename U, typename TList>
U const& get(Variant<TList> const& v) {
    return v.template get<U>();
}

template<typename U, typename TList>
bool holds_alternative(Variant<TList> const& v) {
    return v.template holds_alternative<U>();
}

template<typename U, typename TList>
U const* get(Variant<TList> const* v) {
    if (!holds_alternative<U>(*v)) {
        return 0;
    }

    return &get<U>(*v);
}

template<typename U, typename TList>
U* get(Variant<TList>* v) {
    if (!holds_alternative<U>(*v)) {
        return 0;
    }

    return &get<U>(*v);
}

} // End gmb

#endif // VARIANT_GMB_VARIANT_HPP_INCLUDED
