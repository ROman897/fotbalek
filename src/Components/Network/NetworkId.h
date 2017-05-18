//
// Created by roman on 19.4.2017.
//

#ifndef PV264_PROJECT_NETWORKID_H
#define PV264_PROJECT_NETWORKID_H

#include "../../Utils/Declarations.h"
#include <cstddef>

struct NetworkId {
  // id to identify gameObjects over the network
  Id id;

  NetworkId(Id id) : id(id) {}
  NetworkId() = default;
};

#endif // PV264_PROJECT_NETWORKID_H
