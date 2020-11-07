//
// Created by tangt on 04/11/2020.
//

#ifndef GAMEENGINE_MODEL3DMANAGER_H
#define GAMEENGINE_MODEL3DMANAGER_H

#include <unordered_map>
#include <string>
#include "Vector3F.h"
#include "LogicalDevice.h"
#include "SRotation.h"

namespace object {

    class Model3D;
    class GameObject;

    class Model3DManager
    {
    public:

        friend class Scene;

        static Model3DManager * getInstance();

        /**
         * Create a model3D instance. If the identifier already existe in the pool return the existing instance
         * @param identifier    Identifier in the pool of the model3D
         * @param position      Position of the model3D in the world
         * @param color         Color of the model3D
         * @param scale         Scale of the model3D
         * @return  instance of Model3D
         */
        Model3D * createModel3D(const std::string & levelIdentifier,
                          const std::string & identifier,
                          const std::string & fileName,
                          const Math::Vector3F & position,
                          const Math::Vector3F & color = Math::Vector3F(1.f, 1.f, 1.f),
                          const Math::Vector3F & scale = Math::Vector3F(1.f, 1.f, 1.f),
                          const SRotation & rotate = {0.f, Math::Vector3F(0.f, 0.f, 0.f)});

        /**
         * Work like createModel3D but the identifier is create automaticly
         * with the patern MODEL_XXX where XXX is it number in the pool
         * @param position  Position of the model3D in the world
         * @param color     Color of the model3D
         * @param scale     Scale of the model3D
         * @return  instance of Model3D
         */
        Model3D * createModel3DAutoName(const std::string & levelIdentifier,
                                  const std::string & fileName,
                                  const Math::Vector3F & position,
                                  const Math::Vector3F & color = Math::Vector3F(1.f, 1.f, 1.f),
                                  const Math::Vector3F & scale = Math::Vector3F(1.f, 1.f, 1.f),
                                  const SRotation & rotate = {0.f, Math::Vector3F(0.f, 0.f, 0.f)});
        /**
         * Find a Model3D instance in the pool. Assert if the model3D doesn't exist
         * @param identifier    Model3D identifier in the pool
         * @return Model3D instance if find else nullptr
         */
        Model3D * findModel3D(const std::string & model3DIdentifier, const std::string & levelIdentifier);

        /**
         * Delete a Model3D instance in the pool
         * @param identifier    Identifier of the Model3D
         * @return true if success else false if the Model3D identifier doesn't exist in the pool
         */
        bool deleteModel3D(const std::string & identifier,
                        const std::string & levelIdentifier);

        void release(); ///< Release all element in the pool

    private:
        Model3DManager() = default;

        std::vector<GameObject *> getObjectOfLevel(const std::string & levelIdentifier);

        std::unordered_map<std::string, std::unordered_map<std::string, Model3D *>> m_pool;
    };

}

#endif //GAMEENGINE_MODEL3DMANAGER_H
