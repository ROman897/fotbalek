//
// Created by roman on 9.4.2017.
//

#ifndef PV264_PROJECT_GAMEENGINE_H
#define PV264_PROJECT_GAMEENGINE_H


#include "GameObject.h"
#include "ComponentManager.h"
#include "SignatureManager.h"
#include <boost/hana.hpp>
#include <boost/hana/ext/boost/mpl/list.hpp>
#include <vector>
#include <boost/hana/tuple.hpp>


namespace hana = boost::hana;
using namespace hana::literals;


template <typename TSettings, typename SystemSettings>
class GameEngine {
public:
    using componentSettings = typename TSettings::componentSettings;
private:
    ComponentManager<TSettings> m_componentManager;
    using UnpackedTuple = typename decltype(hana::unpack(SystemSettings::systemList, hana::template_<hana::tuple >))::type;
    UnpackedTuple m_systems;
    // basically network id of this client
    size_t networkId;


public:
    GameEngine() {

        hana::for_each(m_systems, [this](auto& system){
            system.setManager(&m_componentManager);
        });
    }


    Id spawnGameObject(){
        return m_componentManager.addEmptyGameObject();
    }

    Id spawnGameObject(const std::string& tag){
        return m_componentManager.addEmptyGameObject(tag);
    }

    template <typename System, typename ... Args>
    void initSystem(Args&&... args){
        auto& system = getSystem<System>();
        system.initialize(std::forward<Args>(args)...);
    }

    template <typename System>
    System& getSystem(){
        //auto index = index_of(m_systems, hana::type_c<System>);
        //return m_systems[index];

        auto size = decltype(hana::size(SystemSettings::systemList)){};
        auto dropped = decltype(hana::size(
                hana::drop_while(SystemSettings::systemList, hana::not_equal.to(hana::type_c<System>))
        )){};
        return m_systems[size - dropped];
    }

    void start(){
        hana::for_each(m_systems, [](auto& t ){
            t.start();
        });
    }

    template<typename T, typename... TArgs>
    auto& addComponent(Id id, TArgs&&... args) noexcept{
        return m_componentManager.template addComponent<T>(id, std::forward<TArgs>(args) ...);
    }

    template<typename T>
    void removeComponent(Id id) noexcept{
        m_componentManager.removeComponent(id);
    }

    template<typename T>
    auto hasComponent(Id id) const noexcept{
        return m_componentManager.template hasComponent<T>(id);
    }

    void eraseDeadGameObjects() {

        /*m_gameObjects.erase(
                std::remove_if(std::begin(m_gameObjects), std::end(m_gameObjects),
                               [](const std::unique_ptr<GameObject>& go)
                               {
                                   return !go->isAlive();
                               }),
                std::end(m_gameObjects));
*/
    }

    const ComponentManager<TSettings> *getComponentManager() const {
        return &m_componentManager;
    }

private:

};


#endif //PV264_PROJECT_GAMEENGINE_H
