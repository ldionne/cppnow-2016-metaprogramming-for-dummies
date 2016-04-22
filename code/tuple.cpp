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
struct Cat  { std::string name; };
struct Dog  { std::string name; };
struct Fish { std::string name; };
// ... comparison operators ...

hana::tuple<Fish, Dog, Cat, Dog> animals{
    Fish{"Nemo"}, Dog{"Beethoven"}, Cat{"Garfield"}, Dog{"Snoopy"}
};
// end-sample

bool operator==(Cat const& a, Cat const& b) { return a.name == b.name; }
bool operator!=(Cat const& a, Cat const& b) { return a.name != b.name; }

bool operator==(Dog const& a, Dog const& b) { return a.name == b.name; }
bool operator!=(Dog const& a, Dog const& b) { return a.name != b.name; }

bool operator==(Fish const& a, Fish const& b) { return a.name == b.name; }
bool operator!=(Fish const& a, Fish const& b) { return a.name != b.name; }

int main() {

// sample(indexing)
assert(animals[0_c] == Fish{"Nemo"});
assert(animals[1_c] == Dog{"Beethoven"});
assert(animals[2_c] == Cat{"Garfield"});
assert(animals[3_c] == Dog{"Snoopy"});
// end-sample

// sample(insert)
auto more_animals = hana::insert(animals, 2_c, Dog{"Scooby Doo"});
assert(more_animals[2_c] == Dog{"Scooby Doo"}); // used to be Garfield
// end-sample

// sample(remove_at)
auto fewer_animals = hana::remove_at(animals, 1_c);
assert(fewer_animals[1_c] == Cat{"Garfield"}); // used to be Beethoven
// end-sample

// sample(for_each)
// like std::for_each!
hana::for_each(animals, [](auto a) {
    std::cout << a.name << ' ';
});

// outputs `Nemo Beethoven Garfield Snoopy`
// end-sample

{
// sample(transform)
// like std::transform!
auto names = hana::transform(animals, [](auto a) {
    return a.name;
});

assert(names == hana::make_tuple(
    "Nemo", "Beethoven", "Garfield", "Snoopy"
));
// end-sample
}

{
// sample(remove_if)
// like std::remove_if!
auto dogs = hana::remove_if(animals, [](auto a) {
    return hana::decltype_(a) != hana::type<Dog>{};
});

assert(dogs == hana::make_tuple(Dog{"Beethoven"}, Dog{"Snoopy"}));
// end-sample
}

{
// sample(partition)
// like std::partition!
auto parts = hana::partition(animals, [](auto a) {
    return hana::decltype_(a) == hana::type<Dog>{};
});

assert(hana::first(parts) ==
    hana::make_tuple(Dog{"Beethoven"}, Dog{"Snoopy"})
);
assert(hana::second(parts) ==
    hana::make_tuple(Fish{"Nemo"}, Cat{"Garfield"})
);
// end-sample
}

{
// sample(find_if)
// similar to std::find_if
auto garfield = hana::find_if(animals, [](auto a) {
    return hana::decltype_(a) == hana::type<Cat>{};
});

assert(*garfield == Cat{"Garfield"});

auto not_found = hana::find_if(animals, [](auto a) {
    return hana::decltype_(a) == hana::type<int>{};
});

assert(not_found == hana::nothing);
// end-sample
}

{
// sample(count_if)
// like std::count_if!
auto n_dogs = hana::count_if(animals, [](auto a) {
    return hana::decltype_(a) == hana::type<Dog>{};
});

assert(n_dogs == 2u);
// end-sample
}

{
// sample(reverse)
// like std::reverse!
auto reversed = hana::reverse(animals);

assert(reversed == hana::make_tuple(
    Dog{"Snoopy"}, Cat{"Garfield"}, Dog{"Beethoven"}, Fish{"Nemo"}
));
// end-sample
}

}
