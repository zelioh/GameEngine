//
// Created by FiercePC on 14/11/2020.
//

#ifndef GAMEENGINE_MATHENGINE_H
#define GAMEENGINE_MATHENGINE_H

#if defined (_WIN32)
#   if defined(gameEngine_EXPORTS)
#       define  MATH_EXPORT __declspec(dllexport)
#   else
#       define  MATH_EXPORT __declspec(dllimport)
#   endif /* gameEngine_EXPORTS */
#else /* defined (_WIN32) */
#   define MATH_EXPORT
#endif

#endif //GAMEENGINE_MATHENGINE_H
