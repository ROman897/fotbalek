//
// Created by roman on 13.4.2017.
//

#ifndef PV264_PROJECT_COMPONENTPOOL_H
#define PV264_PROJECT_COMPONENTPOOL_H

//BOOST_STRONG_TYPEDEF

#include <assert.h>
#include "SignatureManager.h"
#include "ComponentStorage.h"
#include "GameObject.h"
#include "../Components/Transform.h"
#include <iostream>
#include <utility>





template <typename TSettings>
class ComponentManager{
    template <typename ... Args >
    using PtrTuple = hana::tuple<Args* ...>;
    SignatureManager<TSettings> signatureManager;
    ComponentStorage<TSettings> componentStorage;
    std::vector<GameObject<TSettings>> m_gameObjects;
    size_t m_size, m_capacity, m_newSize;
    const size_t m_startingSize = 50U;

public:
    template<typename T>
    auto matchesSignature(Id id) const noexcept
    {
        static_assert(TSettings::template isSignature<T>(), "");
        const auto& entityBitset(getGameObject(id).m_bitset);
        //const auto& signatureBitset(signatureManager.
                //template getSignatureBitset<T>());
        T t;
        bool matches = true;
        auto len = hana::length(t);
        hana::for_each(t, [&matches, this, id, entityBitset](auto comp){
            if (! entityBitset[TSettings::template componentID<typename decltype(comp)::type>()])
                matches = false;
        });
        return matches;

        //return (signatureBitset & entityBitset) == signatureBitset;
    }

    template<typename TF>
    void forEntities(TF&& mFunction)
    {
        for(Id i{0}; i < m_size; ++i)
            mFunction(i);
    }

    template<typename TF>
    void forEntityPairs(TF&& mFunction)
    {
        for(Id i{0}; i < m_size; ++i) {
            for (Id i2{i + 1}; i2 < m_size; ++i2)
            mFunction(i, i2);

        }
    }

    template<typename T, typename TF>
    void forEntitiesMatching(TF&& mFunction)

    {
        //std::cout << "for entities matching" << std::endl;
        //T t;
        //int x = t;
        static_assert(TSettings::template isSignature<T>(), "requested signature is not in the list of signatures");

        forEntities([this, &mFunction](auto i)
                    {
                        if(matchesSignature<T>(i))
                            signatureCallFunction<T, TF>(i, std::forward<TF>(mFunction));
                    });
    }

    template<typename T, typename U, typename TF>
    void forEntitiesMatchingPairs(TF&& mFunction)
    {
        static_assert(TSettings::template isSignature<T>(), "");

        forEntityPairs([this, &mFunction](auto i, auto i2){
            // we have to look for signatures in order given and also reordered, as caller has information
            // about layout of components

           if (matchesSignature<T>(i) && matchesSignature<U>(i2)){
                signatureCallPairFunction<T, U, TF>(i, i2, std::forward<TF>(mFunction));
           } else
           if (matchesSignature<U>(i) && matchesSignature<T>(i2)){
               signatureCallPairFunction<T, U, TF>(i2, i, std::forward<TF>(mFunction));
           }
        });
    }

    template<typename T, typename TF>
    void forEntityMatching(Id id, TF&& mFunction){
        if (matchesSignature<T>(id)){
            signatureCallFunction<T, TF>(id, mFunction);
        }
    };

    template<typename T>
    Id findEntityMatching(){
        Id id = 0;
        forEntities([this, &id](auto i)
                    {
                        if(matchesSignature<T>(i))
                            id = i;
                    });
        return id;
    }



    template<typename T, typename TF>
    void signatureCallFunction(Id id, TF&& mFunction){

        constexpr static T signature;
        using Unpacked = typename decltype(hana::unpack(signature, hana::template_<PtrTuple>))::type;
        Unpacked components;

        auto range = hana::make_range(hana::int_c<0>, hana::int_c<hana::length(components)>);
        hana::for_each(range, [&components, this, id](auto i){
            hana::at_c<i>(components) = &this->componentStorage.template getComponentVector<typename decltype(+hana::at_c<i>(signature))::type>()[id];
        });

        /*hana::for_each(components, [this, id](auto& comp){
            int x;
            Transform t;
            //using type = typename decltype(t);

            //auto ts = hana::make_tuple(hana::type_c<int>, hana::type_c<char>);
            using F = decltype(*(comp));
            Transform trans;
            F f = trans;
            //std::cout << f;
            //comp = &this->componentStorage.template getComponentVector<F>()[id];
        });*/

        /*auto i = hana::size_c<0>;
        hana::for_each(signature, [this, &i, id, &components ](auto t) {
            hana::at(components, hana::size_c<i>) = &this->componentStorage.template getComponentVector<typename decltype(t)::type>()[id];
        });*/

        /*long i = 0;
        hana::for_each(components,){
            item = &this->componentStorage.template getComponentVector<typename decltype(hana::at_c<0>(signature))::type>()[id];
        }*/

        /*long i = 0;
        hana::for_each(components, [this, &i, id, &components ](auto& t) {
            t = &this->componentStorage.template getComponentVector<hana::type_c<(hana::at_c<0>(signature))>::type>()[id];
        });*/



        hana::unpack(components, mFunction);
    }

    template<typename T, typename U, typename TF>
    void signatureCallPairFunction(Id id1, Id id2, TF&& mFunction){

        constexpr static T signature1;
        constexpr static U signature2;
        using Unpacked = typename decltype(hana::unpack(signature1, hana::template_<PtrTuple>))::type;
        using Unpacked2 = typename decltype(hana::unpack(signature2, hana::template_<PtrTuple>))::type;
        Unpacked components1;
        Unpacked2 components2;

        auto range1 = hana::make_range(hana::int_c<0>, hana::int_c<hana::length(components1)>);
        hana::for_each(range1, [&components1, this, id1](auto i){
            hana::at_c<i>(components1) = &this->componentStorage.template getComponentVector<typename decltype(+hana::at_c<i>(signature1))::type>()[id1];
        });

        auto range2 = hana::make_range(hana::int_c<0>, hana::int_c<hana::length(components2)>);
        hana::for_each(range2, [&components2, this, id2](auto i){
            hana::at_c<i>(components2) = &this->componentStorage.template getComponentVector<typename decltype(+hana::at_c<i>(signature2))::type>()[id2];
        });

        /*using CombinedTuple = hana::c

        int i = 0;
        hana::for_each_t(hana::type_c<T>, [this, &i, id, &components ](auto t) {
            hana::at_c<i>(components) = &this->componentStorage.template getComponentVector<typename decltype(t)::type>()[id];
            ++i;
        });

        i = 0;
        hana::for_each_t(hana::type_c<U>, [this, &i, id2, &components2 ](auto t) {
            hana::at_c<i>(components2) = &this->componentStorage.template getComponentVector<typename decltype(t)::type>()[id2];
            ++i;
        });*/

        auto combinedComps = hana::concat(components1, components2);

        hana::unpack(combinedComps, mFunction);
    }


    void changeSize(size_t newCapacity){
        assert(newCapacity > m_capacity);

        componentStorage.grow(newCapacity);
        m_gameObjects.resize(newCapacity);
        for (auto i = m_capacity; i < newCapacity; ++i){
            GameObject<TSettings>& gameObject = m_gameObjects[i];
            gameObject.m_id = i;
            gameObject.m_bitset.reset();
            gameObject.m_alive = false;
        }

        m_capacity = newCapacity;
    }

    void tryChangeSize(){
        if (m_newSize > m_size){
            changeSize(20 + m_size * 2);
        }
    }

    GameObject<TSettings>& getGameObject(Id id){
        return m_gameObjects[id];
    }

    const GameObject<TSettings>& getGameObject(Id id) const {
        return m_gameObjects[id];
    }

    ComponentManager() : m_size(0U), m_capacity(0U), m_newSize(0U){
        changeSize(m_startingSize);
    }

    template<typename T>
    auto hasComponent(Id id) const noexcept
    {
        static_assert(TSettings::template isComponent<T>(), "");
        return getGameObject(id).m_bitset
        [TSettings::template componentID<T>()];
    }

    template<typename T, typename... TArgs>
    auto& addComponent(Id id, TArgs&&... mXs) noexcept
    {
        static_assert(TSettings::template isComponent<T>(), "");

        GameObject<TSettings>& gameObject = getGameObject(id);
        gameObject.m_bitset[TSettings::template componentID<T>()] = true;
        std::cout << TSettings::template componentID<T>();
        auto& c = componentStorage.template getComponentVector<T>()[id];
        new (&c) T(std::forward<TArgs>(mXs)...);

        return c;
    }

    template<typename T>
    auto& getComponent(Id id) noexcept
    {
        static_assert(TSettings::template isComponent<T>(), "");
        assert(hasComponent<T>(id));

        return componentStorage.
                template getComponentVector<T>()[getGameObject(id).dataIndex];
    }

    template<typename T>
    void removeComponent(Id id) noexcept
    {
        static_assert(TSettings::template isComponent<T>(), "");
        getGameObject(id).bitset
        [TSettings::template componentBit<T>()] = false;
    }

    Id addEmptyGameObject(){
        tryChangeSize();
        Id thisId = m_newSize++;
        auto& g(m_gameObjects[thisId]);
        g.m_alive = true;
        g.m_bitset.reset();
        ++m_size;
        return thisId;
    }

    Id addEmptyGameObject(const std::string& tag){
        Id id = addEmptyGameObject();
        m_gameObjects[id].m_tag = tag;
        return id;
    }

    Id findGameObjectByTag(const std::string tag){
        Id id;
        forEntities([&id, &tag, this](Id goId){
            auto go = getGameObject(goId);
            if (go.m_tag == tag){
                id = goId;
            }
        });
        return id;
    }





};

#endif //PV264_PROJECT_COMPONENTPOOL_H