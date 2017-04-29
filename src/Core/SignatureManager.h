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
    //using ComponentList = typename TSettings::ComponentList;
    using signatureSettings = typename TSettings::signatureSettings;
    using Bitset = typename TSettings::Bitset;

    static constexpr Bitset b = Bitset();
    static constexpr auto m_signatures = hana::replicate<hana::tuple_tag>(b, hana::length(signatureSettings::signatureList));

public:

    template<typename T>
    static constexpr auto& getSignatureBitset() noexcept
    {
        static_assert(TSettings::template isSignature<T>(), "requested signature is not a valid signature");
        return hana::at(m_signatures, TSettings::template signatureID<T>());
    }

    static constexpr void initializeBitsets(){
        auto tuple = signatureSettings::signatureList;
        // here I had to make copy of signatureSettings::signatureList, because for_each takes first argument as an rvalue
        // and it resulted in undefined behaviour because it tried to take it from constexpr variable
        // that was not defined as such, it doesnt have address
        hana::for_each(tuple,[](auto t)
                                        {
                                            //initializeBitset <typename decltype(t)::type>();
                                            //int i = t;
                                            using a = typename decltype(t)::type;
                                            static constexpr a typ;
                                            //a b;
                                            //int x = b;
                                            //initializeBitset <typename decltype(t)::type>();

                                            hana::for_each(typ, [](auto t) {
                                            //  b[TSettings::template componentID<t>()] = true;
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
