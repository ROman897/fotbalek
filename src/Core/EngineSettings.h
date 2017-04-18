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
    static constexpr auto componentList = hana::tuple_t<Components ...>;
};

template <typename ... Signatures>
struct SignatureSettings{
    static constexpr auto signatureList = hana::tuple_c<Signatures ...>;
    static constexpr int a = 4;
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


    template<typename T>
    static constexpr auto isComponent() noexcept
    {
        return hana::contains_t(componentSettings::componentList, hana::type_c<T>);
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

    static constexpr std::size_t signatureCount() noexcept
    {
        return hana::length(signatureSettings::signatureList);
    }

    template<typename T>
    static constexpr std::size_t componentID() noexcept
    {
        return index_of(componentSettings::componentList, hana::type_c<T>);
    }
    template<typename T>
    static constexpr auto signatureID() noexcept
    {
        return index_of(signatureSettings::signatureList, hana::type_c<T>);
    }

};

#endif //PV264_PROJECT_ENGINESETTINGS_H
