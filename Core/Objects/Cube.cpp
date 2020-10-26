//
// Created by tangt on 26/10/2020.
//
// Represent a cube into the game
//

#include "Cube.h"

object::Cube::Cube(const std::string & identifier, const Math::Vector3F &position, const Math::Vector3F &color):
GameObject(identifier, position, color)
{
    //
    // Vertices top face
    m_vertices.push_back(graphics::Vertex(
                    Math::Vector3F(-0.5f, -0.5f, 0.5f),
                    m_color,
                    Math::Vector2F(0.f, 0.f)
                    ));
    m_vertices.push_back(graphics::Vertex(
                    Math::Vector3F(0.5f, -0.5f, 0.5f),
                    m_color,
                    Math::Vector2F(1.f, 0.f)
                    ));
    m_vertices.push_back(graphics::Vertex(
            Math::Vector3F(0.5f, 0.5f, 0.5f),
            m_color,
            Math::Vector2F(1.f, 1.f)
    ));
    m_vertices.push_back(graphics::Vertex(
            Math::Vector3F(-0.5f, 0.5f, 0.5f),
            m_color,
            Math::Vector2F(0.f, 1.f)
    ));

    //
    // Vertices down face
    m_vertices.push_back(graphics::Vertex(
            Math::Vector3F(-0.5f, -0.5f, -0.5f),
            m_color,
            Math::Vector2F(0.f, 0.f)
    ));
    m_vertices.push_back(graphics::Vertex(
            Math::Vector3F(0.5f, -0.5f, -0.5f),
            m_color,
            Math::Vector2F(1.f, 0.f)
    ));
    m_vertices.push_back(graphics::Vertex(
            Math::Vector3F(0.5f, 0.5f, -0.5f),
            m_color,
            Math::Vector2F(1.f, 1.f)
    ));
    m_vertices.push_back(graphics::Vertex(
            Math::Vector3F(-0.5f, 0.5f, -0.5f),
            m_color,
            Math::Vector2F(0.f, 1.f)
    ));

    //
    // Indices
    m_indices = {
         0, 1, 2,
         2, 3, 0,
         1, 5, 6,
         6, 2, 1,
         3, 2, 6,
         6, 7, 3,
         4, 0, 3,
         3, 7, 4,
         0, 4, 5,
         5, 1, 0,
         4, 5, 6,
         6, 7, 4
    };
}

const std::vector<graphics::Vertex> & object::Cube::getVertices() const
{
    return m_vertices;
}

const std::vector<uint32_t> & object::Cube::getIndices() const
{
    return m_indices;
}