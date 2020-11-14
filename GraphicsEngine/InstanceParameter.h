//
// Created by tangt on 07/10/2020.
//
// This class is use for parameter a graphics::Instance inside the motor
//

#ifndef GAMEENGINE_INSTANCEPARAMETER_H
#define GAMEENGINE_INSTANCEPARAMETER_H

#include <string>
#include "public/GraphicsEngine/GraphicsEngine.h"

namespace graphics {

    class GRAPHICS_ENGINE_EXPORT InstanceParameter {
    public:
        InstanceParameter() = default; ///< Default constrcutor

        void setApplicationName(const std::string &applicationName); ///< Sets the application name
        const std::string &getApplicationName() const; ///< Gets the application name
        void setProjectMajorVersion(uint16_t projectMajorVersion); ///< Sets the project version major indice
        uint16_t getProjectMajorVersion() const; ///< Gets the project version major indice
        void setProjectMinorVersion(uint16_t projectMinorVersion);  ///< Sets the project version minor indice
        uint16_t getProjectMinorVersion() const; ///< Gets the project version minor indice
        void setProjectPatchVersion(uint16_t projectPatchVersion); ///< Sets the project version patch indice
        uint16_t getProjectPatchVersion() const; ///< Gets the project version patch indice

        void setProjectVersions(uint16_t major, uint16_t minor, uint16_t patch); ///< Sets all project versions indices

    protected:
    private:
        std::string m_strApplicationName;
        uint16_t m_iProjectMajorVersion;
        uint16_t m_iProjectMinorVersion;
        uint16_t m_iProjectPatchVersion;
    };
}
#endif //GAMEENGINE_INSTANCEPARAMETER_H
