//
// Created by roman on 28.4.2017.
//

#ifndef PV264_PROJECT_PLAYERNETWORKSENDERSYSTEM_H
#define PV264_PROJECT_PLAYERNETWORKSENDERSYSTEM_H

#include "../Components/Network/NetworkId.h"
#include "../Components/MovementInputHolder.h"
#include "../Core/ComponentManager.h"

template <typename TSettings>
class PlaynerNetworkSenderSystem{
    using SystemSignature_Network_Sender = Signature<NetworkId, MovementInputHolder>;

private:
    ComponentManager<TSettings>* m_componentManager;


};

#endif //PV264_PROJECT_PLAYERNETWORKSENDERSYSTEM_H
