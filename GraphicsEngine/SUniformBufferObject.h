//
// Created by tangt on 20/10/2020.
//
// Structure use for link uniform buffer to shader
//

#ifndef GAMEENGINE_SUNIFORMBUFFEROBJECT_H
#define GAMEENGINE_SUNIFORMBUFFEROBJECT_H

#include "../Math/Matrix4F.h"
#include "../Math/Vector3F.h"
#include "public/GraphicsEngine/GraphicsEngine.h"

struct GRAPHICS_ENGINE_EXPORT SUniformBufferObject
{
    alignas(16) Math::Matrix4F model;
    alignas(16) Math::Matrix4F view;
    alignas(16) Math::Matrix4F proj;
    alignas(16) Math::Vector3F position;
    alignas(16) Math::Vector3F color;
    alignas(4) float strenght;
    alignas(4) float specular;
    alignas(16) Math::Vector3F cameraPosition;
};

#endif //GAMEENGINE_SUNIFORMBUFFEROBJECT_H
