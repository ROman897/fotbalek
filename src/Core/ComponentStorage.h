//
// Created by roman on 15.4.2017.
//

#ifndef PV264_PROJECT_COMPONENTSTORAGE_H
#define PV264_PROJECT_COMPONENTSTORAGE_H

#endif //PV264_PROJECT_COMPONENTSTORAGE_H

//#include <boost/hana>
#include <boost/hana.hpp>
#include <boost/hana/ext/boost/mpl/list.hpp>
#include <vector>
#include <boost/hana/tuple.hpp>
#include <boost/hana/type.hpp>
//#include <boost/hana/basic_tuple.hpp>
#include <iostream>
#include "../Utils/declarations.h"
#include <boost/hana/type.hpp>
#include <type_traits>

namespace hana = boost::hana;
using namespace hana::literals;
using DataIndex = size_t ;

template<typename TSettings>
    class ComponentStorage
    {
    private:
        using componentSettings = typename TSettings::componentSettings;

        template<typename... Ts>
        using TupleOfVectors = hana::tuple<std::vector<Ts>...>;
        using UnpacketTuple = typename decltype(hana::unpack(componentSettings::componentList, hana::template_<TupleOfVectors >))::type;
        UnpacketTuple m_components;


        //auto t = hana::make_tuple(5);
    public:
        void grow(std::size_t mNewCapacity) {
            /*
            hana::for_each(components, [this, mNewCapacity](auto& v)
            {
                v.resize(mNewCapacity);
            });*/


            //error code, needs fix: no matching function for call to object of type 'const make_t<boost::hana::tuple_tag>'
            /*hana::transform(components, [this, mNewCapacity](auto &v) {
                v.resize(mNewCapacity);
            });*/


        }

        template <typename T>
        auto& getComponentVector()
        {
            //return components[mI];
            return hana::at<getComponentId<T>()>(m_components);
        }

        //template<typename T>
        auto& getComponentVector(DataIndex mI) noexcept
        {
            //return components[mI];
            return hana::at_c<mI>(m_components);
        }

        template <typename T>
        auto getComponentId(){
            return index_of(m_components, hana::type_c<T>);
        }

    };

