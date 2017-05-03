//
// Created by pnavratil on 5/3/17.
//

#ifndef PV264_PROJECT_PLAYER_H
#define PV264_PROJECT_PLAYER_H

#include <string>


struct Player {
	using Id = size_t;
	Id id;
	std::string name;
};

#endif //PV264_PROJECT_PLAYER_H
