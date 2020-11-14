//
// Created by FiercePC on 14/11/2020.
//

#ifndef GAMEENGINE_SDK_H
#define GAMEENGINE_SDK_H

#if defined (_WIN32)
#   if defined(gameEngine_EXPORTS)
#       define  SDK_EXPORT __declspec(dllexport)
#   else
#       define  SDK_EXPORT __declspec(dllimport)
#   endif /* gameEngine_EXPORTS */
#else /* defined (_WIN32) */
#   define SDK_EXPORT
#endif

#endif //GAMEENGINE_SDK_H
