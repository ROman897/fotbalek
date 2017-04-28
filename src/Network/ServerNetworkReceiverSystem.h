//
// Created by roman on 28.4.2017.
//

#ifndef PV264_PROJECT_SERVERNETWORKRECEIVERSYSTEM_H
#define PV264_PROJECT_SERVERNETWORKRECEIVERSYSTEM_H

#include "../Core/ComponentManager.h"

template <typename TSettings>
class ServerNetworkReceiverSystem{

private:
    ComponentManager<TSettings>* m_componentManager;
};

#endif //PV264_PROJECT_SERVERNETWORKRECEIVERSYSTEM_H
