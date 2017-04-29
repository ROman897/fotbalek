//
// Created by roman on 15.4.2017.
//

#ifndef PV264_PROJECT_DECLARATIONS_H
#define PV264_PROJECT_DECLARATIONS_H

#include <boost/hana/core/to.hpp>
#include <boost/hana/equal.hpp>
#include <boost/hana/tuple.hpp>
#include <boost/hana/type.hpp>
#include <boost/mpl/list.hpp>
#include <boost/hana/size.hpp>
#include <boost/serialization/strong_typedef.hpp>
#include "Vector2.h"

namespace hana = boost::hana;

using namespace hana::literals;


using Id = size_t ;

//hana::to_tuple(hana::tuple_t<int, char, void, int(float)>)
//using Signatr = hana::tuple<hana::type_c<int >>;


template<typename... Ts> using Signature = hana::tuple<hana::type <Ts>...>;
//template<typename... Ts> using SignatureList = hana::tuple<hana::type <Ts>...>;
//template<typename... Ts> using ComponentList = hana::tuple<hana::type <Ts>...>;
//template<typename... Ts> using SystemList = hana::tuple<hana::type <Ts>...>;

using Vector_Float = Vector2<float>;
using Vector_Int = Vector2<int>;

//BOOST_STRONG_TYPEDEF(std::string, )

template <typename Iterable, typename T>
// TODO for now i have changed Iterable parameter to be taken by value, because taking by reference causes it to be odr-defined
// TODO but it should only be defined in header file
// TODO still causes undefined reference

constexpr auto index_of(Iterable iterable, T element) {
    //int x = iterable;
    auto size = decltype(hana::size(iterable)){};
    auto dropped = decltype(hana::size(
            hana::drop_while(iterable, hana::not_equal.to(element))
    )){};
    return size - dropped;
}

// note this is far from ideal solution, probable need to ask at lecture about better solution
// because this takes iterable by value each time
/*template <typename Iterable, typename T>
constexpr auto index_of(typename std::decay<Iterable>::type iterable, const T& element) {
    auto size = decltype(hana::size(iterable)){};
    auto dropped = decltype(hana::size(
            hana::drop_while(iterable, hana::not_equal.to(element))
    )){};
    return size - dropped;
}*/

#endif //PV264_PROJECT_DECLARATIONS_H
