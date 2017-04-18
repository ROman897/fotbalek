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

template <typename TSettings>
struct ComponentManager{
    SignatureManager<TSettings> signatureManager;
    ComponentStorage<TSettings> componentStorage;
    std::vector<GameObject<TSettings>> m_gameObjects;
    size_t m_size, m_capacity, m_newSize;
    const size_t m_startingSize = 50U;

    template<typename T>
    auto matchesSignature(Id id) const noexcept
    {
        static_assert(TSettings::template isSignature<T>(), "");

        const auto& entityBitset(getGameObject(id).bitset);
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

    template<typename T, typename TF>
    void forEntitiesMatching(TF&& mFunction)
    {
        static_assert(TSettings::template isSignature<T>(), "");

        forEntities([this, &mFunction](auto i)
                    {
                        if(matchesSignature<T>(i))
                            signatureCallFunction<T, TF>(i, mFunction);
                    });
    }

    template<typename T, typename U, typename TF>
    void forEntitiesMatchingPairs(TF&& mFunction)
    {
        static_assert(TSettings::template isSignature<T>(), "");

        forEntities([this, &mFunction](auto i)
                    {
                        //if(matchesSignature<T>(i))
                         //SignatureCall::signatureCallFunction<>()
                    });
    }


    template<typename T, typename TF>
    void signatureCallFunction(Id id, TF&& mFunction){

        //using UnpacketTuple = typename decltype(hana::unpack(componentSettings::ComponentList, hana::template_<TupleOfVectors >))::type;


        //_signatureCallFunction<T, TF, hana::unpack(hana::template type_c<T>)>(mFunction);

        /*
        using unpacked = typename decltype(hana::unpack(hana::template type_c<T>, hana::template_<hana::tuple>)>(mFunction))::type;
        _signatureCallFunction<T, TF, unpacked> ;
         */
    }

    template <typename T,typename TF, typename ... Comps>
    void _signatureCallFunction(Id id, TF&& mFunction){
        /*hana::tuple<Comps...> components;
        hana::for_each_t(hana::type_c<T>, [id, this](auto t){
            hana::at<t>(components) = componentStorage.template getComponentVector<T>()[id];
        });
        mFunction(hana::unpack(components));

*/
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
        return getGameObject(id).bitset
        [TSettings::template componentBit<T>()];
    }

    template<typename T, typename... TArgs>
    auto& addComponent(Id id, TArgs&&... mXs) noexcept
    {
        static_assert(TSettings::template isComponent<T>(), "");

        GameObject<TSettings>& gameObject = getGameObject(id);
        gameObject.m_bitset[TSettings::template componentBit<T>()] = true;
        auto& c = componentStorage.template getComponentVector<T>()[id];
        new (&c) T(std::forward<TArgs...>(mXs)...);

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
        g.alive = true;
        g.bitset.reset();
        return thisId;
    }





};

#endif //PV264_PROJECT_COMPONENTPOOL_H