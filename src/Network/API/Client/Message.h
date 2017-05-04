//
// Created by pnavratil on 5/3/17.
//

#ifndef PV264_PROJECT_MESSAGE_H
#define PV264_PROJECT_MESSAGE_H

#include <vector>
#include "../../../Utils/declarations.h"
#include "../../../Components/Network/NetworkId.h"
#include "../../../Components/Transform.h"

class Message {
	//pridat ID sprav a counter
	Id messageId;
	std::vector<NetworkId> playerIds;
	std::vector<Transform> playerMovement;
	bool valid;

public:
	Message() {}

	void addNetworkId(const NetworkId &newId) {
		playerIds.push_back(newId);
	}

	void addTransform(const Transform &newTransform) {
		playerMovement.push_back(newTransform);
	}

	void setValid() {
		valid = true;
	}
};

#endif //PV264_PROJECT_MESSAGE_H
