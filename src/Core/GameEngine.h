//
// Created by roman on 9.4.2017.
//

#ifndef PV264_PROJECT_GAMEENGINE_H
#define PV264_PROJECT_GAMEENGINE_H

#include "../Physic/PhysicSystem.h"
#include "../Utils/Timer.h"
#include "ComponentManager.h"
#include "GameObject.h"
#include "SignatureManager.h"
#include <boost/hana.hpp>
#include <boost/hana/ext/boost/mpl/list.hpp>
#include <boost/hana/tuple.hpp>
#include <thread>
#include <vector>

namespace hana = boost::hana;
using namespace hana::literals;

template <typename TSettings, typename SystemSettings,
          typename ExternalSystemSettings>
class GameEngine {
public:
  using componentSettings = typename TSettings::componentSettings;

private:
  ComponentManager<TSettings> m_componentManager;
  using UnpackedTuple = typename decltype(hana::unpack(
      SystemSettings::systemList, hana::template_<hana::tuple>))::type;
  UnpackedTuple m_systems;

  using unpackedExternalSystems = typename decltype(hana::unpack(
      ExternalSystemSettings::systemList, hana::template_<hana::tuple>))::type;
  unpackedExternalSystems m_externalSystems;
  std::vector<std::thread> m_externalThreads;

public:
  GameEngine() {

    hana::for_each(m_systems, [this](auto &system) {
      system.setManager(&m_componentManager);
    });

    hana::for_each(m_externalSystems, [this](auto &system) {
      system.setManager(&m_componentManager);
    });
  }

  virtual ~GameEngine() { quitExternalSystems(); }

  Id spawnGameObject() { return m_componentManager.addEmptyGameObject(); }

  Id spawnGameObject(const std::string &tag) {
    return m_componentManager.addEmptyGameObject(tag);
  }

  template <typename System> System &getSystem() {
    auto size = decltype(hana::size(SystemSettings::systemList)){};
    auto dropped = decltype(hana::size(
        hana::drop_while(SystemSettings::systemList,
                         hana::not_equal.to(hana::type_c<System>)))){};
    return m_systems[size - dropped];
  }

  template <typename System> System &getExternalSystem() {
    auto size = decltype(hana::size(ExternalSystemSettings::systemList)){};
    auto dropped = decltype(hana::size(
        hana::drop_while(ExternalSystemSettings::systemList,
                         hana::not_equal.to(hana::type_c<System>)))){};
    return m_externalSystems[size - dropped];
  }

  template <typename T, typename... TArgs>
  auto &addComponent(Id id, TArgs &&... args) noexcept {
    return m_componentManager.template addComponent<T>(
        id, std::forward<TArgs>(args)...);
  }

  template <typename T> void removeComponent(Id id) noexcept {
    m_componentManager.removeComponent(id);
  }

  template <typename T> auto hasComponent(Id id) const noexcept {
    return m_componentManager.template hasComponent<T>(id);
  }

  const ComponentManager<TSettings> *getComponentManager() const {
    return &m_componentManager;
  }

  void start() {
    hana::for_each(m_externalSystems, [this](auto &system) {
      m_externalThreads.emplace_back([&system]() { system.start(); });
    });

    hana::for_each(m_systems, [](auto &t) { t.start(); });
    run();
  }

private:
  Timer timer;

  void run() {
    Uint32 accumulator = 0;
    Timer timer;
    timer.start();

    Uint32 frameStart = timer.getTime();
    timer.resetTime();

    while (true) {
      accumulator += timer.getTime() - frameStart;

      frameStart = timer.getTime();

      if (accumulator > GameConstants::kEngineAccumulatorLimit)
        accumulator = GameConstants::kEngineAccumulatorLimit;

      while (accumulator > GameConstants::kEngineDeltaTime) {
        runUpdate(GameConstants::kEngineDeltaTime);
        accumulator -= GameConstants::kEngineDeltaTime;
      }

      if (m_componentManager.shouldQuit()) {
        break;
      }
    }
  }

  void runUpdate(float dt) {
    hana::for_each(m_systems, [dt, this](auto &system) { system.run(dt); });
  }

  void quitExternalSystems() {
    for (auto &sysThread : m_externalThreads) {
      sysThread.join();
    }
  }
};

#endif // PV264_PROJECT_GAMEENGINE_H
