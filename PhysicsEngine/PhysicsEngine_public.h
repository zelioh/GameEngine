//
// Created by FiercePC on 14/11/2020.
//

#ifndef GAMEENGINE_PHYSICSENGINE_PUBLIC_H
#define GAMEENGINE_PHYSICSENGINE_PUBLIC_H

#if defined (_WIN32)
#   if defined(gameEngine_EXPORTS)
#       define  PHYSICS_ENGINE_EXPORT __declspec(dllexport)
#   else
#       define  PHYSICS_ENGINE_EXPORT __declspec(dllimport)
#   endif /* gameEngine_EXPORTS */
#else /* defined (_WIN32) */
#   define PHYSICS_ENGINE_EXPORT
#endif

#endif //GAMEENGINE_PHYSICSENGINE_PUBLIC_H
