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
	std::vector<NetworkId> m_playerIds;
	std::vector<Transform> m_playerMovement;
	bool m_valid;

public:
	Message() {}

	void addNetworkId(const NetworkId &newId) {
		m_playerIds.push_back(newId);
	}

	void addTransform(const Transform &newTransform) {
		m_playerMovement.push_back(newTransform);
	}

	const std::vector<NetworkId> &getIds() const {
		return m_playerIds;
	}

	const std::vector<Transform> &getTransforms() const {
		return m_playerMovement;
	}

	bool isValid() const {
		return m_valid;
	}

	void setValid() {
		m_valid = true;
	}
};

#endif //PV264_PROJECT_MESSAGE_H
