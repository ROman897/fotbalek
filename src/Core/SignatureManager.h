//
// Created by roman on 16.4.2017.
//

#ifndef PV264_PROJECT_SIGNATUREMANAGER_H
#define PV264_PROJECT_SIGNATUREMANAGER_H


#include <boost/hana.hpp>
#include <boost/hana/ext/boost/mpl/list.hpp>
#include <vector>
#include <boost/hana/tuple.hpp>
#include <boost/hana/type.hpp>
//#include <boost/hana/basic_tuple.hpp>
#include <iostream>
#include "../Utils/declarations.h"
#include <boost/hana/size.hpp>

#include <boost/hana/equal.hpp>
#include <boost/hana/integral_constant.hpp>
#include <boost/hana/optional.hpp>
#include <boost/hana/replicate.hpp>
#include <boost/hana/length.hpp>

namespace hana = boost::hana;
using namespace hana::literals;

/**
 * this class holds signatures of systems in form of bitsets
 * all arguments are taken as templates
 * and bitsets are stored as constexpr, because all is known at compile-time
 * this enforces that system and their signatures are known at compile time and
 * cannot be changed during runtime
 *
 * this is achievied through boost::hana library, although
 * there are still some errors that I do not know how to solve at the moment
 *
 * @tparam TSettings
 */
template < typename TSettings>
class SignatureManager{
public:
    //using ComponentList = typename TSettings::ComponentList;
    using signatureSettings = typename TSettings::signatureSettings;
    using Bitset = typename TSettings::Bitset;

    static constexpr Bitset b = Bitset();
    static constexpr decltype(hana::replicate<hana::tuple_tag>(b, hana::length(signatureSettings::signatureList))) m_signatures = hana::replicate<hana::tuple_tag>(b, hana::length(signatureSettings::signatureList));
    //static constexpr int x = m_signatures;

    //static decltype(hana::replicate<hana::tuple_tag>(b, hana::length(signatureSettings::signatureList))) m_signatures = hana::replicate<hana::tuple_tag>(b, hana::length(signatureSettings::signatureList));
    //static constexpr auto m_signatures = hana::transform(signaturesTuple, [this](auto bitset){

    //})



public:



};

#endif //PV264_PROJECT_SIGNATUREMANAGER_H
