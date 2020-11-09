//
// Created by FiercePC on 09/11/2020.
//

#ifndef GAMEENGINE_SDK_CUBE_H
#define GAMEENGINE_SDK_CUBE_H

namespace object
{
    class Cube;
}

namespace sdk {

    class Cube
    {
        friend class CubeManager;

    private:
        Cube(object::Cube * engineCube);

        ::object::Cube * m_pCube;
    };

}


#endif //GAMEENGINE_CUBE_H
