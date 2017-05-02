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
#include "Components/Graphic/Layers/RenderingLayer_Foreground.h"
#include "Components/Graphic/Sprite.h"
#include "Components/Graphic/Layers/RenderingLayer_Background.h"
#include "Components/Graphic/Shapes/RectangleShape.h"
#include "Components/Graphic/Layers/RenderingLayer_UI.h"
#include "Components/UI/Button.h"
#include "Components/MovementInputHolder.h"
#include "Components/Graphic/Label.h"


using compSettings = ComponentSettings <Transform, RectangleShape, RigidBody, CircleCollider, RectangleCollider, Sprite, RenderingLayer_Foreground,
        RenderingLayer_Background, RenderingLayer_UI, MovementInputHolder, Button, Label>;

using SystemSignature_Sprite = Signature <Sprite, Transform>;
using SystemSignature_Rectangle_Background = Signature <RectangleShape, Transform, RenderingLayer_Background>;
using SystemSignature_Rectangle_Foreground = Signature <RectangleShape, Transform, RenderingLayer_Foreground>;
using SystemSignature_Sprite_Background = Signature <Sprite, Transform, RenderingLayer_Background>;
using SystemSignature_Sprite_Foreground = Signature <Sprite, Transform, RenderingLayer_Foreground>;
using SystemSignature_Sprite_UI = Signature <Sprite, Transform, RenderingLayer_UI>;
using SystemSignature_Movable = Signature<RigidBody, Transform>;
using SystemSignature_Circle_Collider = Signature <CircleCollider, RigidBody, Transform>;
using SystemSignature_Rectangle_Collider = Signature <RectangleCollider, RigidBody, Transform>;
using SystemSignature_Input = Signature<MovementInputHolder>;
using SystemSignature_Button = Signature<Button, Sprite, Label, Transform>;

// define which signatures will the engine use
using sigSettings = SignatureSettings <SystemSignature_Rectangle_Background, SystemSignature_Rectangle_Foreground,
        SystemSignature_Sprite_Background, SystemSignature_Sprite_Foreground,
        SystemSignature_Movable, SystemSignature_Circle_Collider, SystemSignature_Rectangle_Collider,
        SystemSignature_Input, SystemSignature_Button, SystemSignature_Sprite,
        SystemSignature_Sprite_UI
>;

using settings = EngineSettings<compSettings , sigSettings>;

//using sysSettings = SystemSettings <GraphicSystem<settings >, PhysicSystem<settings >>;
#endif //PV264_PROJECT_SETTINGSDEFINES_H
