#include "gmb/type_list.hpp"
#include "gmb/variant_impl.hpp"
#include <cassert>
#include <iostream>

#define UNUSED(x) (void)(x)

struct Visitor {
    typedef void return_type;

    void operator()(char c) const {
        std::cerr << c << "\n";
    }

    void operator()(float f) const {
        std::cerr << f << "\n";
    }
};

struct DestructionVisitor {
    typedef void return_type;

    explicit DestructionVisitor(char* storage) throw() :
        storage_(storage)
    { }

    template<typename T>
    void operator()(T&) const {
        reinterpret_cast<T*>(storage_)->~T();
    }

private:
    char* storage_;
};

typedef GMB_TL2(char, float) Types;

void visit(gmb::VariantStorage<Types> const& v, size_t i) {
    visitor_proxy(v, i, Visitor());
}

int main(int argc, char const** argv) {
    UNUSED(argc);
    UNUSED(argv);

    gmb::VariantStorage<Types> s;

    size_t i = gmb::copy_construct_storage_with(s, 1.5f);
    visitor_proxy(s, i, Visitor());
    visit(s, i);
    visitor_proxy(s, i, DestructionVisitor(s.data));

    return 0;
}
