// Copyright Louis Dionne 2016
// Distributed under the Boost Software License, Version 1.0.

#define BOOST_HANA_CONFIG_ENABLE_STRING_UDL
#include <boost/hana.hpp>

#include <cassert>
#include <iostream>
#include <string>
namespace hana = boost::hana;
using namespace hana::literals;


// sample(setup)
template <typename T, typename U, typename V>
struct Triple {
    T first;
    U second;
    V third;
};

struct A { char data; };
struct B { int data; };
struct C { double data; };

// What's the most packed layout?
// end-sample

// sample(main)
template <typename Types>
auto packed_triple(Types const& types) {
    auto sorted = hana::sort(types, [](auto t, auto u) {
        return hana::alignof_(t) > hana::alignof_(u);
    });

    auto triple = hana::unpack(sorted, [](auto ...t) {
        return hana::type<Triple<typename decltype(t)::type...>>{};
    });

    return triple;
}

int main() {
    hana::tuple<hana::type<A>, hana::type<B>, hana::type<C>> types;
    using Packed = decltype(packed_triple(types))::type;
    Packed triple{/* ... */};
}
// end-sample
