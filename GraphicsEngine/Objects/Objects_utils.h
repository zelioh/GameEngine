//
// Created by tangt on 04/11/2020.
//

#ifndef GAMEENGINE_OBJECTS_UTILS_H
#define GAMEENGINE_OBJECTS_UTILS_H

#include <string>
#include "Vertex.h"
#include <vector>
#include "Vector3F.h"

namespace object
{
    namespace utils
    {
        std::vector<std::string> splitString(const std::string & str, const std::string & delimiter);
        bool loadObj(const std::string & fileName,
                     std::vector<graphics::Vertex> & vertices,
                     std::vector<unsigned int> & indices,
                     const Math::Vector3F & vertexColor = Math::Vector3F(1.f, 1.f, 1.f));
    }
}

#endif //GAMEENGINE_OBJECTS_UTILS_H
