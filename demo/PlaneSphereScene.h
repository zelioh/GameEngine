//
// Created by FiercePC on 15/11/2020.
//

#ifndef GAMEENGINE_PLANESPHERESCENE_H
#define GAMEENGINE_PLANESPHERESCENE_H

#include <string>

class PlaneSphereScene {
public:
    PlaneSphereScene();

    void postInitialize();

    void setToCurrentScene();
private:
    std::string m_strIdentifier;
};


#endif //GAMEENGINE_PLANESPHERESCENE_H
