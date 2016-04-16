// Copyright Louis Dionne 2016
// Distributed under the Boost Software License, Version 1.0.

#define BOOST_HANA_CONFIG_ENABLE_STRING_UDL
#include <boost/hana.hpp>

#include <cassert>
#include <string>
namespace hana = boost::hana;


// sample(setup)
struct Cat  { std::string name; };
struct Dog  { std::string name; };
struct Fish { std::string name; };
// ... comparison operators ...
// end-sample

bool operator==(Cat const& a, Cat const& b) { return a.name == b.name; }
bool operator!=(Cat const& a, Cat const& b) { return a.name != b.name; }

bool operator==(Dog const& a, Dog const& b) { return a.name == b.name; }
bool operator!=(Dog const& a, Dog const& b) { return a.name != b.name; }

bool operator==(Fish const& a, Fish const& b) { return a.name == b.name; }
bool operator!=(Fish const& a, Fish const& b) { return a.name != b.name; }

int main() {

{
using namespace hana::literals;

// sample(tuple)
auto animals = hana::make_tuple(
    Fish{"Nemo"}, Dog{"Beethoven"}, Cat{"Garfield"}, Dog{"Snoopy"}
);

assert(animals[0_c] == Fish{"Nemo"});
assert(animals[1_c] == Dog{"Beethoven"});
// end-sample
}

{
using namespace hana::literals;

// sample(map)
auto animals = hana::make_map(
    hana::make_pair("Nemo"_s, Fish{"Nemo"}),
    hana::make_pair("Beethoven"_s, Dog{"Beethoven"}),
    hana::make_pair("Garfield"_s, Cat{"Garfield"}),
    hana::make_pair("Snoopy"_s, Dog{"Snoopy"})
);

assert(animals["Nemo"_s] == Fish{"Nemo"});
assert(animals["Beethoven"_s] == Dog{"Beethoven"});
// end-sample
}

}
