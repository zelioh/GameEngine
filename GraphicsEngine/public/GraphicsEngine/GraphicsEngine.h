//
// Created by FiercePC on 14/11/2020.
//

#ifndef GAMEENGINE_GRAPHICSENGINE_H
#define GAMEENGINE_GRAPHICSENGINE_H

#if defined (_WIN32)
#   if defined(gameEngine_EXPORTS)
#       define  GRAPHICS_ENGINE_EXPORT __declspec(dllexport)
#   else
#       define  GRAPHICS_ENGINE_EXPORT __declspec(dllimport)
#   endif /* gameEngine_EXPORTS */
#else /* defined (_WIN32) */
#   define GRAPHICS_ENGINE_EXPORT
#endif

#endif //GAMEENGINE_GRAPHICSENGINE_H
