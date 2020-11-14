//
// Created by FiercePC on 14/11/2020.
//

#ifndef GAMEENGINE_HIDENGINE_H
#define GAMEENGINE_HIDENGINE_H

#if defined (_WIN32)
#   if defined(gameEngine_EXPORTS)
#       define  HID_EXPORT __declspec(dllexport)
#   else
#       define  HID_EXPORT __declspec(dllimport)
#   endif /* gameEngine_EXPORTS */
#else /* defined (_WIN32) */
#   define HID_EXPORT
#endif

#endif //GAMEENGINE_HIDENGINE_H
