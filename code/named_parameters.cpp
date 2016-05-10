#define BOOST_HANA_CONFIG_ENABLE_STRING_UDL
#include <boost/hana.hpp>
namespace hana = boost::hana;
using namespace hana::literals;


template <typename Keyword, typename Type, bool Optional>
struct named_parameter {
    Keyword keyword;
    Type type;
    hana::bool_<Optional> optional;
};

template <typename ...Parameters>
struct named_parameter_map {
    using Map = decltype(hana::make_map(
        hana::make_pair(
            std::declval<Parameters>().keyword,
            std::declval<Parameters>()
        )...
    ));
    Map params;

    template <typename ...Arguments>
    auto parse(Arguments ...a) {
        auto args = hana::make_map(a...);

        // Make sure all the required parameters have a matching argument
        hana::for_each(hana::values(params), [](auto&& param) {
            static_assert(decltype(param.optional || hana::contains(args, param.keyword)){},
                "Required parameter is missing from the arguments");
        });

        // Make sure all the arguments have a matching parameter, and they all
        // have the expected type.
        hana::for_each(args, [&](auto&& arg) {
            static_assert(decltype(hana::contains(params, hana::first(arg))){},
                "Argument passed, but no corresponding parameter was found");

            auto param = params[hana::first(arg)];
            static_assert(decltype(param.type == hana::decltype_(hana::second(arg))){},
                "Type of argument does not match the type specified by the corresponding parameter");
        });

        return args;
    }

    template <typename F>
    auto parse_into(F&& f) {
        return [f, this](auto&& ...args) -> decltype(auto) {
            return f(this->parse(static_cast<decltype(args)&&>(args)...));
        };
    }
};

template <typename Key, typename Type>
constexpr named_parameter<Key, Type, false> required(Key const&, Type const&) noexcept {
    return {};
}

template <typename Key, typename Type>
constexpr named_parameter<Key, Type, true> optional(Key const&, Type const&) noexcept {
    return {};
}

template <typename ...Parameters>
constexpr named_parameter_map<Parameters...> params(Parameters const& ...) noexcept {
    return {};
}



template <char ...s>
struct named_argument {
    // TODO: Take by perfect ref; currently this triggers an error because
    //       hana::pair's copy constructor is deleted.
    template <typename T>
    constexpr hana::pair<hana::string<s...>, T> operator=(T value) noexcept {
        return {hana::string_c<s...>, value};
    }
};

template <typename CharT, CharT ...s>
constexpr named_argument<s...> operator"" _arg() noexcept { return {}; }


//////////////////////////////////////////////////////////////////////////////
// Example
//////////////////////////////////////////////////////////////////////////////
#include <iostream>

auto parameters = params(
    required("foo"_s, hana::type<int>{}),
    required("bar"_s, hana::type<char>{}),
    optional("baz"_s, hana::type<double>{})
);

auto f = [](auto ...a) {
    auto kwargs = parameters.parse(a...);
    std::cout << "kwargs[foo] = " << kwargs["foo"_s] << std::endl;
    std::cout << "kwargs[bar] = " << kwargs["bar"_s] << std::endl;
    std::cout << "kwargs[baz] = " <<
        hana::eval_if(hana::contains(kwargs, "baz"_s),
                  [&](auto _){ return _(kwargs)["baz"_s]; },
                  []{ return "not provided"; })
    << std::endl;
};

auto g = parameters.parse_into([](auto kwargs) {
    std::cout << "kwargs[foo] = " << kwargs["foo"_s] << std::endl;
    std::cout << "kwargs[bar] = " << kwargs["bar"_s] << std::endl;
    std::cout << "kwargs[baz] = " <<
        hana::eval_if(hana::contains(kwargs, "baz"_s),
                  [&](auto _){ return _(kwargs)["baz"_s]; },
                  []{ return "not provided"; })
    << std::endl;
});

int main() {
    f("foo"_arg = 1, "bar"_arg = 'x', "baz"_arg = 3.4);
    g("foo"_arg = 1, "bar"_arg = 'x', "baz"_arg = 3.4);
}