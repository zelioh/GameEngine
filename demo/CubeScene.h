//
// Created by FiercePC on 15/11/2020.
//

#ifndef GAMEENGINE_CUBESCENE_H
#define GAMEENGINE_CUBESCENE_H

#include <string>

class CubeScene
{
public:
    CubeScene();

    void postInitialize();
    void preUpdate(float deltaTime);

    void setToCurrentScene();
private:
    std::string m_strIdentifier;
};


#endif //GAMEENGINE_CUBESCENE_H
