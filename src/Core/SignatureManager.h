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


    template<typename T>
    static constexpr auto& getSignatureBitset() noexcept
    {
        static_assert(TSettings::template isSignature<T>(), "requested signature is not a valid signature");
        return hana::at(m_signatures, TSettings::template signatureID<T>());
    }



    static constexpr void initializeBitsets(){

        //constexpr auto range = hana::make_range(hana::int_c<0>, hana::int_c<hana::length(signatureSettings::signatureList)>);
        //hana::for_each(range, [](auto num){

        //})
        constexpr auto tup = hana::make_tuple();
        hana::concat(tup, hana::make_tuple("ab", 12));
        //auto x = hana::at_c<0>(tup);




        hana::for_each(signatureSettings::signatureList,[](auto t)
                                        {
                                            //initializeBitset <typename decltype(t)::type>();
                                            //int i = t;
                                            static constexpr auto size = hana::size_c<0>;
                                            using a = typename decltype(t)::type;
                                            static constexpr a signature;
                                            //a b;
                                            //int x = b;
                                            //initializeBitset <typename decltype(t)::type>();
                                            //size ++;
                                            hana::for_each(signature, [](auto t) {
                                              //b[TSettings::template componentID<t>()] = true;
                                                //hana::at_c<>()
                                            //});)



                                        });

    });
    }

    template<typename T>
    static constexpr void initializeBitset() noexcept
    {
        auto& b(getSignatureBitset<T>());

        //std::cout << hana::type_c<T>;
        //hana::for_each(typename decltype (hana::type_c<T>)::value, [&b](auto t) {
          //  b[TSettings::template componentID<t>()] = true;
        //});
    }

public:
    /**
     * constructor of this class should be the one instantiating the template, because before the instantiation the bitsets are not initialized
     */
    SignatureManager() noexcept
    {
        initializeBitsets();
        }


};

#endif //PV264_PROJECT_SIGNATUREMANAGER_H
