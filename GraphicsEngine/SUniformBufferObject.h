//
// Created by tangt on 20/10/2020.
//
// Structure use for link uniform buffer to shader
//

#ifndef GAMEENGINE_SUNIFORMBUFFEROBJECT_H
#define GAMEENGINE_SUNIFORMBUFFEROBJECT_H

#include "Matrix4F.h"

struct SUniformBufferObject
{
    alignas(16) Math::Matrix4F model;
    alignas(16) Math::Matrix4F view;
    alignas(16) Math::Matrix4F proj;
};

#endif //GAMEENGINE_SUNIFORMBUFFEROBJECT_H
