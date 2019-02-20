#ifndef VARIANT_GMB_DETAIL_DESTRUCTION_VISITOR_HPP_INCLUDED
#define VARIANT_GMB_DETAIL_DESTRUCTION_VISITOR_HPP_INCLUDED

namespace gmb {
namespace detail {

struct DestructionVisitor {
    typedef void return_type;

    explicit DestructionVisitor(char* storage) throw() :
        storage_(storage)
    { }

    template<typename T>
    return_type operator()(T&) const throw() {
        reinterpret_cast<T*>(storage_)->~T();
    }

private:
    char* storage_;
};

}
}
#endif // VARIANT_GMB_DETAIL_DESTRUCTION_VISITOR_HPP_INCLUDED
