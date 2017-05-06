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
#include "Components/Logic/MovementInputHolder.h"
#include "Components/Graphic/Label.h"
#include "Components/Network/NetworkId.h"
#include "Components/Logic/PlayerComp.h"
#include "Components/Physic/ColliderTrigger.h"
#include "Components/Logic/GameState.h"
#include "Components/Network/GameStateChange.h"
#include "Components/Logic/BallComp.h"


using compSettings = ComponentSettings <Transform, RectangleShape, RigidBody, CircleCollider, RectangleCollider, Sprite,
        MovementInputHolder, Button, Label, NetworkId, PlayerComp, ColliderTrigger, GameState, GameStateChange, BallComp>;


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
using SystemSignature_Network_Input = Signature<MovementInputHolder>;
using SystemSignature_Network = Signature<NetworkId, Transform>;
using SystemSignature_Network_Graphic = Signature<NetworkId, Sprite, Label>;
using SystemSignature_Network_Rigid = Signature<NetworkId, RigidBody>;
using SystemSignature_Network_Player = Signature<NetworkId, Transform, PlayerComp>;
using SystemSignature_Player_Rigid = Signature<RigidBody, Transform, PlayerComp>;
using SystemSignature_Ball_Rigid = Signature<RigidBody, Transform, BallComp>;
using SystemSignature_Ball = Signature<Transform, BallComp>;
using SystemSignature_GameState = Signature<GameState>;
using SystemSignature_GameStateChange = Signature<GameStateChange>;
using SystemSignature_ColliderTrigger = Signature<ColliderTrigger>;
using SystemSignature_Label = Signature<Label>;

// define which signatures will the engine use
using sigSettings = SignatureSettings <SystemSignature_SpriteGraphic,
        SystemSignature_Movable, SystemSignature_Circle_Collider_Body, SystemSignature_Rectangle_Collider_Body,
        SystemSignature_Input, SystemSignature_Button, SystemSignature_LabelGraphic ,
        SystemSignature_RectangleGraphic , SystemSignature_Network_Input, SystemSignature_Network,
        SystemSignature_Network_Graphic, SystemSignature_Rectangle_Collider, SystemSignature_Circle_Collider,
        SystemSignature_Network_Rigid, SystemSignature_Network_Player, SystemSignature_GameState,
        SystemSignature_ColliderTrigger, SystemSignature_GameStateChange, SystemSignature_Player_Rigid,
        SystemSignature_Ball_Rigid, SystemSignature_Ball, SystemSignature_Label
>;

using settings = EngineSettings<compSettings , sigSettings>;

//using sysSettings = SystemSettings <GraphicSystem<settings >, PhysicSystem<settings >>;
#endif //PV264_PROJECT_SETTINGSDEFINES_H
