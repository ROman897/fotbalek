//
// Created by pnavratil on 5/3/17.
//

#ifndef PV264_PROJECT_PLAYER_H
#define PV264_PROJECT_PLAYER_H

#include <string>

struct Player {
	Player() = default;
	using Id = size_t;

	Player(const std::string &name, Id id) : m_name(name), m_id(id) {}

	Id m_id;
	bool m_team;
	std::string m_name;
	//pridat info o time
};

#endif //PV264_PROJECT_PLAYER_H
