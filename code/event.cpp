// Copyright Louis Dionne 2016
// Distributed under the Boost Software License, Version 1.0.

#define BOOST_HANA_CONFIG_ENABLE_STRING_UDL
#include <boost/hana.hpp>

#include <functional>
#include <iostream>
#include <vector>
namespace hana = boost::hana;
using namespace hana::literals;



// sample(event_handler)
template <typename EventMap>
class event_handler {
public:
    template <typename Event, typename F>
    void on(Event e, F handler) {
        static_assert(decltype(hana::contains(map_, e)){},
            "trying to add a handler to an unknown event");
        map_[e].push_back(handler);
    }

    template <typename ...Events>
    void trigger(Events ...events) {
        hana::for_each(hana::make_tuple(events...), [this](auto e) {
            static_assert(decltype(hana::contains(map_, e)){},
                "trying to trigger an unknown event");
            for (auto& handler : this->map_[e])
                handler();
        });
    }

private:
    EventMap map_;
};
// end-sample

// sample(make_event_handler)
template <typename ...Events>
auto make_event_handler(Events ...events) {
    auto map = hana::make_map(
        hana::make_pair(events, std::vector<std::function<void()>>{})...
    );

    return event_handler<decltype(map)>{};
}
// end-sample


int main() {
// sample(usage)
auto events = make_event_handler("foo"_s, "bar"_s, "baz"_s);

events.on("foo"_s, []() { std::cout << "foo triggered!" << std::endl; });
events.on("foo"_s, []() { std::cout << "foo triggered again!" << std::endl; });
events.on("bar"_s, []() { std::cout << "bar triggered!" << std::endl; });
events.on("baz"_s, []() { std::cout << "baz triggered!" << std::endl; });
// events.on("unknown"_s, []() { }); // compiler error!

events.trigger("foo"_s, "bar"_s);
events.trigger("baz"_s);
// events.trigger("unknown"_s); // compiler error!
// end-sample
}
