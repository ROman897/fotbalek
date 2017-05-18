//
// Created by roman on 15.4.2017.
//

#ifndef PV264_PROJECT_DECLARATIONS_H
#define PV264_PROJECT_DECLARATIONS_H

#include "Vector2.h"
#include <boost/hana/core/to.hpp>
#include <boost/hana/equal.hpp>
#include <boost/hana/size.hpp>
#include <boost/hana/tuple.hpp>
#include <boost/hana/type.hpp>
#include <boost/mpl/list.hpp>
#include <boost/serialization/strong_typedef.hpp>

namespace hana = boost::hana;

using namespace hana::literals;

using Id = size_t;

template <typename... Ts> using Signature = hana::tuple<hana::type<Ts>...>;

using Vector_Float = Vector2<float>;
using Vector_Int = Vector2<int>;

#endif // PV264_PROJECT_DECLARATIONS_H
