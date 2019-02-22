#include "gmb/detail/variant_storage.hpp"
#include "gmb/detail/variant_impl.hpp"
#include <cassert>
#include <iostream>

#define UNUSED(x) (void)(x)

int main(int argc, char const** argv) {
    UNUSED(argc);
    UNUSED(argv);

    typedef GMB_TL2(char, float) Types;
    gmb::detail::VariantStorage<Types> s;

    size_t i = gmb::detail::copy_construct_storage_with<Types>(s.data(), 1.0f);
    assert(i == 1);

    i = default_construct(s);
    assert(i == 0);

    return 0;
}
