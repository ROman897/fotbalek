//
// Created by pnavratil on 5/3/17.
//

#ifndef PV264_PROJECT_MESSAGE_H
#define PV264_PROJECT_MESSAGE_H

#include "../../../Utils/declarations.h"
#include "../../../Components/Network/NetworkId.h"
#include "../../../Components/MovementInputHolder.h"

struct Message {
	//pridat ID sprav a counter
	Id messageId;
	std::vector<NetworkId> playerIds;
	std::vector<MovementInputHolder> playerMovement;
};

#endif //PV264_PROJECT_MESSAGE_H
