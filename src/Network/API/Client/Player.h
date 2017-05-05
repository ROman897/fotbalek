//
// Created by pnavratil on 5/3/17.
//

#ifndef PV264_PROJECT_PLAYER_H
#define PV264_PROJECT_PLAYER_H

#include <string>

struct Player {
	Player() = default;
	using Id = size_t;

	Player(const std::string &name, Id id, bool team = false) : m_name(name), m_id(id), m_team(team) {}

	Id m_id;
	bool m_team;
	std::string m_name;
};

#endif //PV264_PROJECT_PLAYER_H
