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

{
// sample(indexing)
hana::tuple<Cat, Dog, Fish> animals{
    Cat{"Garfield"}, Dog{"Beethoven"}, Fish{"Nemo"}
};

assert(animals[0_c] == Cat{"Garfield"});
assert(animals[1_c] == Dog{"Beethoven"});
assert(animals[2_c] == Fish{"Nemo"});
// end-sample
}

{
// sample(insert)
hana::tuple<Cat, Dog, Fish> animals{
    Cat{"Garfield"}, Dog{"Beethoven"}, Fish{"Nemo"}
};

hana::tuple<Cat, Elephant, Dog, Fish> more_animals =
                hana::insert(animals, 1_c, Elephant{"Dumbo"});
assert(more_animals[1_c] == Elephant{"Dumbo"}); // used to be Beethoven
// end-sample
}


{
// sample(remove_at)
hana::tuple<Cat, Dog, Fish> animals{
    Cat{"Garfield"}, Dog{"Beethoven"}, Fish{"Nemo"}
};

hana::tuple<Cat, Fish> fewer_animals = hana::remove_at(animals, 1_c);
assert(fewer_animals[1_c] == Fish{"Nemo"}); // used to be Beethoven
// end-sample
}

{
// sample(for_each)
hana::tuple<Cat, Dog, Fish> animals{
    Cat{"Garfield"}, Dog{"Beethoven"}, Fish{"Nemo"}
};

// like std::for_each!
hana::for_each(animals, [](auto a) {
    std::cout << a.name << ' ';
});

// outputs `Garfield Beethoven Nemo`
// end-sample
}

{
// sample(transform)
hana::tuple<Cat, Dog, Fish> animals{
    Cat{"Garfield"}, Dog{"Beethoven"}, Fish{"Nemo"}
};

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
hana::tuple<Cat, Fish, Dog, Fish> animals{
    Cat{"Garfield"}, Fish{"Jaws"}, Dog{"Beethoven"}, Fish{"Nemo"}
};

// like std::remove_if!
auto mammals = hana::remove_if(animals, [](auto a) {
    return hana::decltype_(a) == hana::type<Fish>{};
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
hana::tuple<Cat, Dog, Fish> animals{
    Cat{"Garfield"}, Dog{"Beethoven"}, Fish{"Nemo"}, Dog{"Lassie"}
};

// like std::partition!
auto parts = hana::partition(animals, [](auto a) {
    return hana::decltype_(a) == hana::type<Dog>{};
});

assert(hana::first(parts) ==
    hana::make_tuple(Dog{"Beethoven"}, Dog{"Lassie"})
);
assert(hana::second(parts) ==
    hana::make_tuple(Cat{"Garfield"}, Fish{"Nemo"})
);
// end-sample
}

{
// sample(find_if)
hana::tuple<Cat, Dog, Fish, Dog> animals{
    Cat{"Garfield"}, Dog{"Beethoven"}, Fish{"Nemo"}, Dog{"Lassie"}
};

// similar to std::find_if
auto beethoven = hana::find_if(animals, [](auto a) {
    return hana::decltype_(a) == hana::type<Dog>{};
});

assert(*beethoven == Dog{"Beethoven"});

auto not_found = hana::find_if(animals, [](auto a) {
    return hana::decltype_(a) == hana::type<int>{};
});

assert(not_found == hana::nothing);
// end-sample
}

{
// sample(count_if)
hana::tuple<Cat, Dog, Fish, Dog> animals{
    Cat{"Garfield"}, Dog{"Beethoven"}, Fish{"Nemo"}, Dog{"Lassie"}
};

// like std::count_if!
auto dogs = hana::count_if(animals, [](auto a) {
    return hana::decltype_(a) == hana::type<Dog>{};
});

assert(dogs == 2u);
// end-sample
}

{
// sample(reverse)
hana::tuple<Cat, Dog, Fish> animals{
    Cat{"Garfield"}, Dog{"Beethoven"}, Fish{"Nemo"}
};

// like std::reverse!
auto reversed = hana::reverse(animals);

assert(reversed == hana::make_tuple(
    Fish{"Nemo"}, Dog{"Beethoven"}, Cat{"Garfield"}
));
// end-sample
}

{
// sample(unpack)
hana::tuple<Cat, Dog, Fish> animals{
    Cat{"Garfield"}, Dog{"Beethoven"}, Fish{"Nemo"}
};

auto names = hana::unpack(animals, [](auto ...a) {
    return std::vector<std::string>{a.name...};
});

assert((names == std::vector<std::string>{"Garfield",
                                          "Beethoven",
                                          "Nemo"}));
// end-sample
}

{
hana::tuple<Cat, Dog, Fish> animals{
    Cat{"Garfield"}, Dog{"Beethoven"}, Fish{"Nemo"}
};

// sample(unpack-equiv)
auto f = [](auto ...a) {
    return std::vector<std::string>{a.name...};
};

auto names = f(animals[0_c], animals[1_c], animals[2_c]);
// end-sample

assert((names == std::vector<std::string>{"Garfield",
                                          "Beethoven",
                                          "Nemo"}));
}

}
