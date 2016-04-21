// Copyright Louis Dionne 2016
// Distributed under the Boost Software License, Version 1.0.

#define BOOST_HANA_CONFIG_ENABLE_STRING_UDL
#include <boost/hana.hpp>

#include <cassert>
#include <string>
namespace hana = boost::hana;
using namespace hana::literals;


// sample(setup)
struct Cat  { std::string name; };
struct Dog  { std::string name; };
struct Fish { std::string name; };
// ... comparison operators ...

auto animals = hana::make_map(
    hana::make_pair("Nemo"_s, Fish{"Nemo"}),
    hana::make_pair("Beethoven"_s, Dog{"Beethoven"}),
    hana::make_pair("Garfield"_s, Cat{"Garfield"}),
    hana::make_pair("Snoopy"_s, Dog{"Snoopy"})
);
// end-sample

bool operator==(Cat const& a, Cat const& b) { return a.name == b.name; }
bool operator!=(Cat const& a, Cat const& b) { return a.name != b.name; }

bool operator==(Dog const& a, Dog const& b) { return a.name == b.name; }
bool operator!=(Dog const& a, Dog const& b) { return a.name != b.name; }

bool operator==(Fish const& a, Fish const& b) { return a.name == b.name; }
bool operator!=(Fish const& a, Fish const& b) { return a.name != b.name; }

int main() {

// sample(accessing)
assert(animals["Nemo"_s] == Fish{"Nemo"});
assert(animals["Beethoven"_s] == Dog{"Beethoven"});
assert(animals["Garfield"_s] == Cat{"Garfield"});
assert(animals["Snoopy"_s] == Dog{"Snoopy"});
// end-sample

// sample(contains)
static_assert(hana::contains(animals, "Beethoven"_s), "");
static_assert(!hana::contains(animals, "Lassie"_s), "");
// end-sample

// sample(insert)
auto more_animals = hana::insert(animals,
    hana::make_pair("Scooby Doo"_s, Dog{"Scooby Doo"}));

assert(more_animals["Scooby Doo"_s] == Dog{"Scooby Doo"});
// end-sample

// sample(erase_key)
auto fewer_animals = hana::erase_key(animals, "Beethoven"_s);
static_assert(!hana::contains(fewer_animals, "Beethoven"_s), "");
// end-sample

}
