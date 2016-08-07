// Copyright Louis Dionne 2016
// Distributed under the Boost Software License, Version 1.0.

#include <cmath>
#include <tuple>


// sample(spherical)
std::tuple<double, double, double>
from_spherical(double rho, double theta, double phi) {
    double x = rho * std::sin(theta) * std::cos(phi);
    double y = rho * std::sin(theta) * std::sin(phi);
    double z = rho * std::cos(theta);
    return {x, y, z};
}

std::tuple<double, double, double> xyz = from_spherical(3, 16.5, 25.5);
double x = std::get<0>(xyz),
       y = std::get<1>(xyz),
       z = std::get<2>(xyz);
// end-sample

// sample(animals)
struct Fish { };
struct Cat { };
struct Dog { };

std::tuple<Fish, Cat, Dog> my_animals() {
    // ...
    return {};
}

std::tuple<Fish, Cat, Dog> animals = my_animals();
Fish fish = std::get<0>(animals);
Cat  cat  = std::get<1>(animals);
Dog  dog  = std::get<2>(animals);
// end-sample

int main() { }
