//
// Created by FiercePC on 15/11/2020.
//

#ifndef GAMEENGINE_COLLISIONSPHERESCENE_H
#define GAMEENGINE_COLLISIONSPHERESCENE_H

#include <string>

class CollisionSphereScene
{
public:
    CollisionSphereScene();

    void postInitialize();

    void setToCurrentScene();
private:
    std::string m_strIdentifier;
};


#endif //GAMEENGINE_COLLISIONSPHERESCENE_H
