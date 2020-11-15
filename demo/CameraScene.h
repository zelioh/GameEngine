//
// Created by FiercePC on 15/11/2020.
//

#ifndef GAMEENGINE_CAMERASCENE_H
#define GAMEENGINE_CAMERASCENE_H

#include <string>

class CameraScene
{
public:
    CameraScene();

    void postInitialize();
    void preUpdate(float deltaTime);

    void setToCurrentScene();
private:
    std::string m_strIdentifier;
};


#endif //GAMEENGINE_CAMERASCENE_H
