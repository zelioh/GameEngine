//
// Created by tangt on 13/10/2020.
//
// Class that load a shader with vertex and fragment shader path file
//

#ifndef GAMEENGINE_SHADER_H
#define GAMEENGINE_SHADER_H

#include <string>
#include <vector>
#include "public/GraphicsEngine/GraphicsEngine.h"

namespace graphics {

    class GRAPHICS_ENGINE_EXPORT Shader {
    public:
        Shader() = default;
        /**
         * Create Shader with files path
         * @param vertexPath    Path to the vertex file path
         * @param fragmentPath  Path to the fragment file path
         */
        Shader(const std::string &vertexPath, const std::string &fragmentPath);

        Shader(const std::string &vertexPath, const std::string &fragmentPath, const std::string &name);

        const std::vector<char> &getVertexData() const; ///< Return the vertexData
        const std::vector<char> &getFragmentData() const; ///< Return the fragmentData
        const std::string &getName() const; ///< Return the name of the shader

    private:
        void loadData(std::vector<char> &buffer, const std::string &path);

    private:
        std::vector<char> m_vVertexData;
        std::vector<char> m_vFragmentData;
        std::string m_strName;
    };

}

#endif //GAMEENGINE_SHADER_H
