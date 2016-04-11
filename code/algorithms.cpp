// Copyright Louis Dionne 2016
// Distributed under the Boost Software License, Version 1.0.

#include <boost/hana.hpp>

#include <cassert>
#include <iostream>
#include <string>
namespace hana = boost::hana;


// sample(setup)
struct Cat  { std::string name; };
struct Dog  { std::string name; };
struct Fish { std::string name; };

auto animals = hana::make_tuple(
    Fish{"Nemo"}, Dog{"Beethoven"}, Cat{"Garfield"}, Dog{"Snoopy"}
);
// end-sample

bool operator==(Cat const& a, Cat const& b) { return a.name == b.name; }
bool operator!=(Cat const& a, Cat const& b) { return a.name != b.name; }

bool operator==(Dog const& a, Dog const& b) { return a.name == b.name; }
bool operator!=(Dog const& a, Dog const& b) { return a.name != b.name; }

bool operator==(Fish const& a, Fish const& b) { return a.name == b.name; }
bool operator!=(Fish const& a, Fish const& b) { return a.name != b.name; }

int main() {

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