//
// Created by tangt on 04/11/2020.
//

#ifndef GAMEENGINE_OBJECTS_UTILS_H
#define GAMEENGINE_OBJECTS_UTILS_H

#include <string>
#include "Vertex.h"
#include <vector>

namespace object
{
    namespace utils
    {
        std::vector<std::string> splitString(const std::string & str, const std::string & delimiter);
        bool loadObj(const std::string & fileName, std::vector<graphics::Vertex> & vertices, std::vector<unsigned int> & indices);
    }
}

#endif //GAMEENGINE_OBJECTS_UTILS_H
