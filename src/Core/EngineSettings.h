//
// Created by roman on 15.4.2017.
//

#ifndef PV264_PROJECT_ENGINESETTINGS_H
#define PV264_PROJECT_ENGINESETTINGS_H

//#include <boost/hana>
#include <boost/hana.hpp>
#include <boost/hana/ext/boost/mpl/list.hpp>
#include <boost/hana/contains.hpp>
#include <boost/hana/integral_constant.hpp>

#include <boost/hana/find.hpp>
#include <boost/hana/find_if.hpp>
#include <boost/hana/optional.hpp>
#include <boost/hana/type.hpp>
#include <bitset>
#include "../Utils/declarations.h"


/*
 * TComponentList is template list of all components that gameengine will accept
 * TTagList is list of all gameobject tags that engine will store
 * TSystem list is template list of all systems working in this engine
 */

namespace hana = boost::hana;
using namespace hana::literals;

template <typename ... Components>
struct ComponentSettings{
    //static constexpr auto componentList = hana::tuple_t<Components ...>;
    static constexpr auto componentList = hana::make_tuple(hana::type_c<Components > ...);
    //static constexpr typename decltype(hana::tuple_t<Components ...>)::type componentList;
    //static constexpr int x = componentList;
};

template <typename ... Signatures>
struct SignatureSettings{
    //static constexpr auto signatureList = hana::tuple_t<Signatures ...>;

    //static constexpr hana::tuple<Signatures ...> signatureList = hana::tuple_t<Signatures ...>;
    //static constexpr auto signatureList = hana::make_tuple(hana::type_c<Signatures>...);


    // Really weird behaviour of compiler, it throws error saying that I tried to redefine signature list with different type, however it should be the same as
    // I used decltype and auto,
    // when I use decltype in both cases it compiles
    static constexpr decltype(hana::make_tuple(hana::type_c<Signatures>...)) signatureList = hana::make_tuple(hana::type_c<Signatures>...);
    //static constexpr int a = signatureList;
};

template <typename ... Systems>
struct SystemSettings{
    static constexpr auto systemList = hana::tuple_t<Systems ...>;
};


template
        <
                typename TComponentSettings,
                typename TSignatureSettings
        >
struct EngineSettings{


    using componentSettings = TComponentSettings;
    using signatureSettings = TSignatureSettings;
    //using systemSettings = TSystemSettings;
    using Bitset = std::bitset<hana::length(componentSettings::componentList)>;

    static constexpr componentSettings m_componentSettings = componentSettings();


    template<typename T>
    static constexpr auto isComponent() noexcept
    {
        return hana::contains(componentSettings::componentList, hana::type_c<T>);
    }

    template<typename T>
    static constexpr auto isSignature() noexcept
    {
        return hana::contains(signatureSettings::signatureList, hana::type_c<T>);
    }

    static constexpr auto componentCount() noexcept
    {
        return hana::length(componentSettings::componentList);
    }

    static constexpr auto signatureCount() noexcept
    {
        return hana::length(signatureSettings::signatureList);
    }

    template<typename T>
    static constexpr auto componentID() noexcept
    {
        //using t = typename std::decay<decltype(componentSettings::componentList)>::type;
        //t x;
       // int a = x;
        //int x =  componentSettings::componentList;
        //std::cout << componentSettings::componentList;
        auto size = decltype(hana::size(componentSettings::componentList)){};
        auto dropped = decltype(hana::size(
                hana::drop_while(componentSettings::componentList, hana::not_equal.to(hana::type_c<T>))
        )){};
        return size - dropped;


        //return index_of(componentSettings::componentList, hana::type_c<T>);
    }
    template<typename T>
    static constexpr auto signatureID() noexcept
    {
        //return index_of(signatureSettings::signatureList, hana::type_c<T>);

        auto size = decltype(hana::size(signatureSettings::signatureList)){};
        auto dropped = decltype(hana::size(
                hana::drop_while(signatureSettings::signatureList, hana::not_equal.to(hana::type_c<T>))
        )){};
        return size - dropped;
    }

};

#endif //PV264_PROJECT_ENGINESETTINGS_H
