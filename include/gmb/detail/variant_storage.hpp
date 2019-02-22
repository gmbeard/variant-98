#ifndef VARIANT_GMB_DETAIL_VARIANT_STORAGE_HPP_INCLUDED
#define VARIANT_GMB_DETAIL_VARIANT_STORAGE_HPP_INCLUDED

#include "gmb/detail/type_list_utils.hpp"

namespace gmb {
namespace detail {

template<typename TList>
struct VariantStorage {
    char const* data() const {
        return data_;
    }

    char* data() {
        return data_;
    }

private:
    union {
        double align_;
        char data_[max_size_of<TList>::value];
    };
};

} // End detail
} // End gmb

#endif // VARIANT_GMB_DETAIL_VARIANT_STORAGE_HPP_INCLUDED
