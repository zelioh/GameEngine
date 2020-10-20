//
// Created by tangt on 20/10/2020.
//
// Structure use for link uniform buffer to shader
//

#ifndef GAMEENGINE_SUNIFORMBUFFEROBJECT_H
#define GAMEENGINE_SUNIFORMBUFFEROBJECT_H

#include "Matrix.h"

struct SUniformBufferObject
{
    alignas(16) Math::Matrix model;
    alignas(16) Math::Matrix view;
    alignas(16) Math::Matrix proj;
};

#endif //GAMEENGINE_SUNIFORMBUFFEROBJECT_H
