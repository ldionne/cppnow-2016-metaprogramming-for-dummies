// Copyright Louis Dionne 2016
// Distributed under the Boost Software License, Version 1.0.

#define BOOST_HANA_CONFIG_ENABLE_STRING_UDL
#include <boost/hana.hpp>

#include <cassert>
#include <iostream>
#include <string>
#include <vector>
namespace hana = boost::hana;
using namespace hana::literals;


// sample(setup)
struct Cat      { std::string name; };
struct Dog      { std::string name; };
struct Elephant { std::string name; };
struct Fish     { std::string name; };
// ... comparison operators ...

hana::tuple<Cat, Dog, Fish> animals{
    Cat{"Garfield"}, Dog{"Beethoven"}, Fish{"Nemo"}
};
// end-sample

bool operator==(Cat const& a, Cat const& b) { return a.name == b.name; }
bool operator!=(Cat const& a, Cat const& b) { return a.name != b.name; }

bool operator==(Dog const& a, Dog const& b) { return a.name == b.name; }
bool operator!=(Dog const& a, Dog const& b) { return a.name != b.name; }

bool operator==(Elephant const& a, Elephant const& b) { return a.name == b.name; }
bool operator!=(Elephant const& a, Elephant const& b) { return a.name != b.name; }

bool operator==(Fish const& a, Fish const& b) { return a.name == b.name; }
bool operator!=(Fish const& a, Fish const& b) { return a.name != b.name; }

int main() {

// sample(indexing)
assert(animals[0_c] == Cat{"Garfield"});
assert(animals[1_c] == Dog{"Beethoven"});
assert(animals[2_c] == Fish{"Nemo"});
// end-sample

// sample(insert)
auto more_animals = hana::insert(animals, 1_c, Elephant{"Dumbo"});
assert(more_animals[1_c] == Elephant{"Dumbo"}); // used to be Beethoven
// end-sample

// sample(remove_at)
auto fewer_animals = hana::remove_at(animals, 1_c);
assert(fewer_animals[1_c] == Fish{"Nemo"}); // used to be Beethoven
// end-sample

// sample(for_each)
// like std::for_each!
hana::for_each(animals, [](auto a) {
    std::cout << a.name << ' ';
});

// outputs `Garfield Beethoven Nemo`
// end-sample

{
// sample(transform)
// like std::transform!
auto names = hana::transform(animals, [](auto a) {
    return a.name;
});

assert(names == hana::make_tuple(
    "Garfield", "Beethoven", "Nemo"
));
// end-sample
}

{
// sample(remove_if)
// like std::remove_if!
auto mammals = hana::remove_if(animals, [](auto a) {
    return hana::is_a<Fish>(a);
});

assert(mammals == hana::make_tuple(Cat{"Garfield"}, Dog{"Beethoven"}));
// end-sample
}

{
// sample(sort)
hana::tuple<hana::type<char[10]>,
            hana::type<char[5]>,
            hana::type<char[1]>> types;

// like std::sort!
auto sorted = hana::sort(types, [](auto t, auto u) {
    return hana::sizeof_(t) < hana::sizeof_(u);
});

assert((sorted == hana::tuple<hana::type<char[1]>,
                              hana::type<char[5]>,
                              hana::type<char[10]>>{}));
// end-sample
}

{
// sample(partition)
// like std::partition!
auto parts = hana::partition(animals, [](auto a) {
    return hana::is_a<Dog>(a);
});

assert(hana::first(parts) ==
    hana::make_tuple(Dog{"Beethoven"})
);
assert(hana::second(parts) ==
    hana::make_tuple(Cat{"Garfield"}, Fish{"Nemo"})
);
// end-sample
}

{
// sample(find_if)
// similar to std::find_if
auto garfield = hana::find_if(animals, [](auto a) {
    return hana::is_a<Cat>(a);
});

assert(*garfield == Cat{"Garfield"});

auto not_found = hana::find_if(animals, [](auto a) {
    return hana::is_an<int>(a);
});

assert(not_found == hana::nothing);
// end-sample
}

{
// sample(count_if)
// like std::count_if!
auto n_mammals = hana::count_if(animals, [](auto a) {
    return !hana::is_a<Fish>(a);
});

assert(n_mammals == 2u);
// end-sample
}

{
// sample(reverse)
// like std::reverse!
auto reversed = hana::reverse(animals);

assert(reversed == hana::make_tuple(
    Fish{"Nemo"}, Dog{"Beethoven"}, Cat{"Garfield"}
));
// end-sample
}

{
// sample(unpack)
auto names = hana::unpack(animals, [](auto ...a) {
    return std::vector<std::string>{a.name...};
});

assert((names == std::vector<std::string>{"Garfield",
                                          "Beethoven",
                                          "Nemo"}));
// end-sample
}

}
