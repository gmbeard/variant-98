#include "gmb/variant.hpp"
#include "gmb/type_list.hpp"
#include "gmb/detail/variant_impl.hpp"
#include "gmb/detail/visitation.hpp"
#include <cassert>
#include <iostream>

#define UNUSED(x) (void)(x)

struct DestructorCheck {
    explicit DestructorCheck(bool* destroyed) throw() :
        destroyed_(destroyed)
    { }

    ~DestructorCheck() {
        *destroyed_ = true;
    }

private:
    bool* destroyed_;
};

std::ostream& operator<<(std::ostream& os, DestructorCheck const&) {
    return os << "DestructorCheck instance";
}

struct Visitor {
    typedef void return_type;

    void operator()(DestructorCheck const& c) const {
        std::cerr << c << "\n";
    }

    void operator()(char const& c) const {
        std::cerr << c << "\n";
    }

    void operator()(float const& f) const {
        std::cerr << f << "\n";
    }

//    template<typename T>
//    void operator()(T& t) const {
//        std::cerr << t << "\n";
//    }
};

typedef GMB_TL3(char, float, DestructorCheck) Types;

void visit(gmb::Variant<Types> const& v) {
    v.visit(Visitor());
}

int main(int argc, char const** argv) {
    UNUSED(argc);
    UNUSED(argv);

    bool destroyed = false;
    {
        gmb::Variant<Types> v;

        v = DestructorCheck(&destroyed);

        v.visit(Visitor());
        Visitor visitor;
        v.visit(visitor);
        visit(v);
    }

    assert(destroyed && "Didn't destroy instance!");

    return 0;
}
