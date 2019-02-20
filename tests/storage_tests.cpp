#include "gmb/variant_impl.hpp"
#include <cassert>
#include <iostream>

#define UNUSED(x) (void)(x)

int main(int argc, char const** argv) {
    UNUSED(argc);
    UNUSED(argv);

    gmb::VariantStorage<GMB_TL2(char, float)> s;

    size_t i = gmb::copy_construct_storage_with(s, 1.0f);
    assert(i == 1);

    i = gmb::default_construct(s);
    assert(i == 0);

    return 0;
}
