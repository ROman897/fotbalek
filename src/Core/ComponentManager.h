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
#include <iostream>





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
        const auto& signatureBitset(signatureManager.
                template getSignatureBitset<T>());

        return (signatureBitset & entityBitset) == signatureBitset;
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
                signatureCallPairFunction<T, U, TF>(i, i2, mFunction);
           } else
           if (matchesSignature<U>(i) && matchesSignature<T>(i2)){
               signatureCallPairFunction<U, T, TF>(i2, i, mFunction);
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

        using Unpacked = typename decltype(hana::unpack(hana::template type_c<T>, hana::template_<PtrTuple>))::type;
        Unpacked components;

        int i = 0;
        hana::for_each_t(hana::type_c<T>, [this, &i, id, &components ](auto t) {
            hana::at_c<i>(components) = &this->componentStorage.template getComponentVector<typename decltype(t)::type>()[id];
            ++i;
        });

        hana::unpack(components, mFunction);
    }

    template<typename T, typename U, typename TF>
    void signatureCallPairFunction(Id id, Id id2, TF&& mFunction){

        using Unpacked = typename decltype(hana::unpack(hana::template type_c<T>, hana::template_<PtrTuple>))::type;
        using Unpacked2 = typename decltype(hana::unpack(hana::template type_c<U>, hana::template_<PtrTuple>))::type;
        Unpacked components;
        Unpacked2 components2;

        int i = 0;
        hana::for_each_t(hana::type_c<T>, [this, &i, id, &components ](auto t) {
            hana::at_c<i>(components) = &this->componentStorage.template getComponentVector<typename decltype(t)::type>()[id];
            ++i;
        });

        i = 0;
        hana::for_each_t(hana::type_c<U>, [this, &i, id2, &components2 ](auto t) {
            hana::at_c<i>(components2) = &this->componentStorage.template getComponentVector<typename decltype(t)::type>()[id2];
            ++i;
        });

        auto combinedComps = hana::concat(components, components2);

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
        return thisId;
    }





};

#endif //PV264_PROJECT_COMPONENTPOOL_H