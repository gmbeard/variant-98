#ifndef VARIANT_GMB_VARIANT_IMPL_HPP_INCLUDED
#define VARIANT_GMB_VARIANT_IMPL_HPP_INCLUDED

#include "gmb/detail/variant_storage.hpp"
#include "gmb/detail/type_list_utils.hpp"

namespace gmb {
namespace detail {

template<typename TList, typename U>
size_t copy_construct_storage_with(char* s, U const& val)
{
    ::new (static_cast<void*>(s)) U(val);
    return index_of_type<TList, U>::value;
}

template<typename TList>
size_t default_construct(VariantStorage<TList>& s) {
    typedef typename type_at_index<TList, 0>::type FirstType;
    ::new (static_cast<void*>(s.data())) FirstType();
    return 0;
}

struct MutableStorageVisitorBase {
    explicit MutableStorageVisitorBase(char* storage) throw() :
        storage_(storage)
    { }

    char* storage() const throw() { return storage_; }
private:
    char* storage_;
};

struct DestructionVisitor : MutableStorageVisitorBase {
    typedef void return_type;
    explicit DestructionVisitor(char* storage) throw() :
        MutableStorageVisitorBase(storage)
    { }

    template<typename T>
    void operator()(T&) const throw() {
        reinterpret_cast<T*>(storage())->~T();
    }
};

template<typename TList>
struct CopyConstructVisitor : MutableStorageVisitorBase {
    typedef size_t return_type;

    explicit CopyConstructVisitor(char* storage) throw() :
        MutableStorageVisitorBase(storage)
    { }

    template<typename T>
    size_t operator()(T const& val) const throw() {
        return copy_construct_storage_with<TList>(storage(), val);
    }
};

} // End detail
} // End gmb

#endif // VARIANT_GMB_VARIANT_IMPL_HPP_INCLUDED
