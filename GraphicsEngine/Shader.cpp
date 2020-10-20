//
// Created by tangt on 13/10/2020.
//
// Class that load a shader with vertex and fragment shader path file
//

#include "Shader.h"
#include <fstream>

graphics::Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath)
{
    loadData(m_vVertexData, vertexPath);
    loadData(m_vFragmentData, fragmentPath);
    m_strName = vertexPath.substr(0, vertexPath.find("."));
}

graphics::Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath, const std::string &name):
m_strName(name)
{
    loadData(m_vVertexData, vertexPath);
    loadData(m_vFragmentData, fragmentPath);
}

const std::vector<char> & graphics::Shader::getVertexData() const
{
    return m_vVertexData;
}

const std::vector<char> & graphics::Shader::getFragmentData() const
{
    return m_vFragmentData;
}

const std::string & graphics::Shader::getName() const
{
    return m_strName;
}

void graphics::Shader::loadData(std::vector<char> &buffer, const std::string &path)
{
    std::ifstream file(path, std::ios::ate | std::ios::binary);

    if (!file.is_open())
    {
        throw std::runtime_error("Error while opening shader file: " + path);
    }

    size_t size = static_cast<size_t>(file.tellg());

    buffer.resize(size);
    file.seekg(0);
    file.read(buffer.data(), size);
    file.close();
}