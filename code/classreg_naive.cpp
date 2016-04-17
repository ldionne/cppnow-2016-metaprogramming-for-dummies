// Copyright Louis Dionne 2016
// Distributed under the Boost Software License, Version 1.0.

#include <iostream>
#include <typeinfo>

// sample(main)
class A { };
class B { };
class C { };

template <typename T>
void register_() {
    std::cout << "Registering " << typeid(T).name()
              << ", which is of size " << sizeof(T) << std::endl;
}

int main() {
    register_<A>();
    register_<B>();
    register_<C>();
}
// end-sample
