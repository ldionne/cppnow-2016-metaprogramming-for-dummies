// Copyright Louis Dionne 2016
// Distributed under the Boost Software License, Version 1.0.

#include <iostream>
#include <typeinfo>

class A { };
class B { };
class C { };

// sample(main)
template <typename ...Ts>
struct register_;

template <>
struct register_<> {
    void operator()() const { }
};

template <typename T, typename ...Ts>
struct register_<T, Ts...> {
    void operator()() const {
        std::cout << "Registering " << typeid(T).name()
                  << ", which is of size " << sizeof(T) << std::endl;
        register_<Ts...>{}();
    }
};

int main() {
    register_<A, B, C>{}();
}
// end-sample
