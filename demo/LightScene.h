//
// Created by FiercePC on 15/11/2020.
//

#ifndef GAMEENGINE_LIGHTSCENE_H
#define GAMEENGINE_LIGHTSCENE_H

#include <string>

class LightScene {
public:
    LightScene();

    void postInitialize();
    void preUpdate(float deltaTime);

    void setToCurrentScene();
private:
    std::string m_strIdentifier;
    bool m_bTopReach;
};


#endif //GAMEENGINE_LIGHTSCENE_H
