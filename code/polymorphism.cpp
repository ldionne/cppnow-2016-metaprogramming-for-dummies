// Copyright Louis Dionne 2016
// Distributed under the Boost Software License, Version 1.0.

#include <iostream>
#include <typeinfo>
#include <vector>
#include <tuple>


int main() {
    {
        struct Animal { };
        struct Cat  : Animal { };
        struct Dog  : Animal { };
        struct Fish : Animal { };

        std::vector<Animal*> xs{new Cat, new Dog, new Fish};
        std::cout << typeid(*xs[0]).name() << std::endl;
        std::cout << typeid(*xs[1]).name() << std::endl;
        std::cout << typeid(*xs[2]).name() << std::endl;
    }

    {
        struct Animal { virtual ~Animal() { } };
        struct Cat  : Animal { };
        struct Dog  : Animal { };
        struct Fish : Animal { };

        std::vector<Animal*> xs{new Cat, new Dog, new Fish};
        std::cout << typeid(*xs[0]).name() << std::endl;
        std::cout << typeid(*xs[1]).name() << std::endl;
        std::cout << typeid(*xs[2]).name() << std::endl;
    }

    {
        struct Cat  { };
        struct Dog  { };
        struct Fish { };

        std::tuple<Cat, Dog, Fish> xs{Cat{}, Dog{}, Fish{}};
        std::cout << typeid(std::get<0>(xs)).name() << std::endl;
        std::cout << typeid(std::get<1>(xs)).name() << std::endl;
        std::cout << typeid(std::get<2>(xs)).name() << std::endl;
    }
}
