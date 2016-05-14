// Copyright Louis Dionne 2016
// Distributed under the Boost Software License, Version 1.0.

#include <iostream>
#include <string>
#include <tuple>
#include <typeinfo>

#include <boost/hana.hpp>
#include <boost/hana/ext/std/tuple.hpp>
namespace hana = boost::hana;


class A { };
class B { };
class C { };

// sample(register)
template <typename ...TypeInfos>
void register_(std::tuple<TypeInfos...> const& classes) {
    // like std::for_each!
    hana::for_each(classes, [](auto c) {
        using T = typename decltype(c)::type;
        std::cout << "Registering " << typeid(T).name()
                  << ", which is of size " << sizeof(T) << std::endl;
        static_assert(sizeof(T) <= 1000, "");
    });
}
// end-sample

// sample(main)
int main() {
    std::tuple<hana::type<A>,
               hana::type<B>,
               hana::type<C>> classes;
    register_(classes);
}
// end-sample
