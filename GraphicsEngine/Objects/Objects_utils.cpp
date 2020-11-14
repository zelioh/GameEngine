//
// Created by tangt on 04/11/2020.
//

#include "GraphicsEngine/Objects_utils.h"
#include <istream>
#include <fstream>
#include <sstream>
#include <iostream>
#include "../../Math/Vector3F.h"
#include "../../Math/Vector2F.h"
#include <unordered_map>

std::vector<std::string> object::utils::splitString(const std::string & str, const std::string & delimiter)
{
    std::vector<std::string> result;
    std::string tmp = str;
    size_t pos = 0;
    std::string token;

    while ((pos = tmp.find(delimiter)) != std::string::npos) {
        token = tmp.substr(0, pos);
        result.push_back(token);
        tmp.erase(0, pos + delimiter.length());
    }
    result.push_back(tmp);
    return result;
}

bool object::utils::loadObj(const std::string &fileName,
                            std::vector<graphics::Vertex> &vertices,
                            std::vector<unsigned int> & indices,
                            const Math::Vector3F & vertexColor)
{
    std::fstream file;

    file.open(fileName, std::ios::in);
    if (!file.is_open())
    {
        std::cout << "Enable to load file: " + fileName << std::endl;
        return false;
    }

    std::string line;
    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<Math::Vector3F> tmpVertices, tmpNormals;
    std::vector<Math::Vector2F> tmpUV;

    while (std::getline(file, line))
    {
        std::vector<std::string> vStrings = splitString(line, " ");

        if (vStrings[0] == "v")
        {
            Math::Vector3F pos{};

            pos.X = std::stof(vStrings[1]);
            pos.Y = std::stof(vStrings[2]);
            pos.Z = std::stof(vStrings[3]);
            tmpVertices.push_back(pos);
        } else if (vStrings[0] == "vt") {
            Math::Vector2F uv{};

            uv.X = std::stof(vStrings[1]);
            uv.Y = std::stof(vStrings[2]);
            tmpUV.push_back(uv);
        } else if (vStrings[0] == "vn") {
            Math::Vector3F normal{};

            normal.X = std::stof(vStrings[1]);
            normal.Y = std::stof(vStrings[2]);
            normal.Z = std::stof(vStrings[3]);
            tmpNormals.push_back(normal);
        } else if (vStrings[0] == "f") {
            for (int i = 1; i < 4; ++i)
            {
                std::vector<std::string> vLine = splitString(vStrings[i], "/");

                vertexIndices.push_back(std::stoi(vLine[0]));
                uvIndices.push_back(std::stoi(vLine[1]));
                normalIndices.push_back(std::stoi(vLine[2]));
            }
        }
    }
    file.close();

    for( unsigned int i=0; i<vertexIndices.size(); i++ ){

        // Get the indices of its attributes
        unsigned int vertexIndex = vertexIndices[i];
        unsigned int uvIndex = uvIndices[i];
        unsigned int normalIndex = normalIndices[i];

        // Get the attributes thanks to the index
        Math::Vector3F position = tmpVertices[ vertexIndex-1 ];
        Math::Vector2F uv = tmpUV[ uvIndex-1 ];
        Math::Vector3F normal = tmpNormals[ normalIndex-1 ];

        // Put the attributes in buffers
        graphics::Vertex vertex{};

        vertex.m_position = position;
        vertex.m_color = vertexColor;
        vertex.m_normal = normal;
        vertex.m_texCoord.X = uv.X;
        vertex.m_texCoord.Y = 1.0f - uv.Y; ///< need to inverse because vulkan is opposite than standar obj

        vertices.push_back(vertex);
        indices.push_back(indices.size());
    }

    return true;
}