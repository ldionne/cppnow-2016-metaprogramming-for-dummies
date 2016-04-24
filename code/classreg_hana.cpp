// Copyright Louis Dionne 2016
// Distributed under the Boost Software License, Version 1.0.

#include <iostream>
#include <typeinfo>
#include <tuple>

#include <boost/hana.hpp>
#include <boost/hana/ext/std/tuple.hpp>
namespace hana = boost::hana;


class A { };
class B { };
class C { };

// sample(main)
template <typename Classes>
void register_(Classes const& classes) {
    hana::for_each(classes, [](auto c) {
        using C = typename decltype(c)::type;
        std::cout << "Registering " << typeid(C).name()
                  << ", which is of size " << sizeof(C) << std::endl;
        static_assert(sizeof(C) <= 1000, "");
    });
}

int main() {
    std::tuple<hana::type<A>, hana::type<B>, hana::type<C>> classes;
    register_(classes);
}
// end-sample
