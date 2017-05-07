//
// Created by roman on 15.4.2017.
//

#ifndef PV264_PROJECT_COMPONENTSTORAGE_H
#define PV264_PROJECT_COMPONENTSTORAGE_H

#endif //PV264_PROJECT_COMPONENTSTORAGE_H

//#include <boost/hana>
#include <boost/hana.hpp>
#include <vector>
#include <boost/hana/tuple.hpp>
#include <boost/hana/type.hpp>
#include <boost/hana/equal.hpp>
#include <boost/hana/optional.hpp>
#include <iostream>
#include "../Utils/declarations.h"
#include <type_traits>
#include <boost/hana/transform.hpp>
#include <mutex>

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
        using UnpackedTuple = typename decltype(hana::unpack(componentSettings::componentList, hana::template_<TupleOfVectors >))::type;
        UnpackedTuple m_components;


    public:
        void grow(std::size_t mNewCapacity) {

            hana::for_each(m_components, [mNewCapacity](auto& v)
            {
                v.resize(mNewCapacity);
            });
        }

        template <typename T>
        constexpr auto& getComponentVector()
        {
            return hana::at_c<TSettings::template componentID<T>()>(m_components);
        }

        auto& getComponentVector(DataIndex mI) noexcept
        {
            return hana::at_c<mI>(m_components);
        }

        template <typename T>
        constexpr auto getComponentId(){
            std::cout << index_of(m_components, hana::type_c<T>);
            return index_of(m_components, hana::type_c<T>);
        }

    };

