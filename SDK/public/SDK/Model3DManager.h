//
// Created by FiercePC on 09/11/2020.
//

#ifndef GAMEENGINE_SDK_MODEL3DMANAGER_H
#define GAMEENGINE_SDK_MODEL3DMANAGER_H

#include "Model3D.h"

namespace sdk {

    class Model3DManager
    {
    public:
        static Model3D createModel3D(const std::string & levelIdentifier,
                                     const std::string & identifier,
                                     const std::string & fileModel,
                                     const Math::Vector3F & position,
                                     const Math::Vector3F & color = Math::Vector3F(1.f, 1.f, 1.f),
                                     const Math::Vector3F & scale = Math::Vector3F(1.f, 1.f, 1.f),
                                     const SRotation & rotate = SRotation{0.f, Math::Vector3F(0.f, 0.f, 0.f)});

        static Model3D createModel3DAutoName(const std::string & levelIdentifier,
                                             const std::string & fileModel,
                                             const Math::Vector3F & position,
                                             const Math::Vector3F & color = Math::Vector3F(1.f, 1.f, 1.f),
                                             const Math::Vector3F & scale = Math::Vector3F(1.f, 1.f, 1.f),
                                             const SRotation & rotate = SRotation{0.f, Math::Vector3F(0.f, 0.f, 0.f)});

        static Model3D findModel3D(const std::string & levelIdentifier,
                                   const std::string & identifier);

        static void deleteModel3D(const std::string & levelIdentifier, const std::string & modelIdentifier);
    };

}

#endif //GAMEENGINE_MODEL3DMANAGER_H
