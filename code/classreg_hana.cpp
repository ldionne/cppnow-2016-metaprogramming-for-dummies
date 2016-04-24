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

template <typename T>
struct static_type_info {
    static std::string name() { return typeid(T).name(); }
    static std::size_t const size = sizeof(T);
    static std::size_t const alignment = alignof(T);
    // whatever...
};

// sample(register)
template <typename ...T>
void register_(std::tuple<T...> const& classes) {
    // like std::for_each!
    hana::for_each(classes, [](auto c) {
        std::cout << "Registering " << c.name()
                  << ", which is of size " << c.size << std::endl;
        static_assert(c.size <= 1000, "");
    });
}
// end-sample

int main() {
    std::tuple<static_type_info<A>,
               static_type_info<B>,
               static_type_info<C>> classes;
    register_(classes);
}
