//
// Created by roman on 1.5.2017.
//

#ifndef PV264_PROJECT_SETTINGSDEFINES_H
#define PV264_PROJECT_SETTINGSDEFINES_H

#include "Core/EngineSettings.h"
#include "Components/Physic/Shapes/RectangleCollider.h"
#include "Components/Transform.h"
#include "Components/Physic/RigidBody.h"
#include "Components/Physic/Shapes/CircleCollider.h"
#include "Components/Graphic/Sprite.h"
#include "Components/Graphic/Shapes/RectangleShape.h"
#include "Components/UI/Button.h"
#include "Components/MovementInputHolder.h"
#include "Components/Graphic/Label.h"
#include "Components/Network/NetworkId.h"


using compSettings = ComponentSettings <Transform, RectangleShape, RigidBody, CircleCollider, RectangleCollider, Sprite,
        MovementInputHolder, Button, Label, NetworkId>;


using SystemSignature_RectangleGraphic = Signature <RectangleShape, Transform>;
using SystemSignature_SpriteGraphic = Signature <Sprite, Transform>;
using SystemSignature_LabelGraphic = Signature <Label, Transform>;

using SystemSignature_Movable = Signature<RigidBody, Transform>;
using SystemSignature_Circle_Collider_Body = Signature <CircleCollider, RigidBody, Transform>;
using SystemSignature_Rectangle_Collider_Body = Signature <RectangleCollider, RigidBody, Transform>;
using SystemSignature_Circle_Collider = Signature <CircleCollider, Transform>;
using SystemSignature_Rectangle_Collider = Signature <RectangleCollider, Transform>;
using SystemSignature_Input = Signature<MovementInputHolder>;
using SystemSignature_Button = Signature<Button, Sprite, Label, Transform>;
using SystemSignature_Network_Input = Signature<NetworkId, MovementInputHolder>;
using SystemSignature_Network = Signature<NetworkId, Transform>;
using SystemSignature_Network_Graphic = Signature<NetworkId, Sprite, Label>;

// define which signatures will the engine use
using sigSettings = SignatureSettings <SystemSignature_SpriteGraphic,
        SystemSignature_Movable, SystemSignature_Circle_Collider_Body, SystemSignature_Rectangle_Collider_Body,
        SystemSignature_Input, SystemSignature_Button, SystemSignature_LabelGraphic ,
        SystemSignature_RectangleGraphic , SystemSignature_Network_Input, SystemSignature_Network,
        SystemSignature_Network_Graphic, SystemSignature_Rectangle_Collider, SystemSignature_Circle_Collider
>;

using settings = EngineSettings<compSettings , sigSettings>;

//using sysSettings = SystemSettings <GraphicSystem<settings >, PhysicSystem<settings >>;
#endif //PV264_PROJECT_SETTINGSDEFINES_H
