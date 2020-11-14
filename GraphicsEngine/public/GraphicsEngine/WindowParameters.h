//
// Created by tangt on 26/10/2020.
//
// Class use for parameters the window
//

#ifndef GAMEENGINE_WINDOWPARAMETERS_H
#define GAMEENGINE_WINDOWPARAMETERS_H

#include <string>
#include "public/GraphicsEngine/GraphicsEngine.h"

namespace graphics {

    class GRAPHICS_ENGINE_EXPORT WindowParameters {

    public:

        WindowParameters() = default; ///< Default constructor
        /**
         * Constructor with full parameters
         * @param name              Name of the window in the title bar
         * @param isFullScreen      Set the window in fullscreen
         * @param isBorderLess      Set the window borderless
         * @param hasSysmenu        Set if the window have a system menu
         * @param canMinimize       Set if the window can be minimized
         * @param canMaximaze       Set if the window can be maximazed
         * @param canResize         Set if the window can be resized
         * @param width             Set window width. If window width > monitor width so the monitor width will be use
         * @param height            Set window height. If window height > monitor height so the monitor height will be use
         * @param left              Set window left position onto the monitor. Default 0
         * @param top               Set window top position onto the monitor Default 0
         */
        WindowParameters(const std::string &name,
                         bool isFullScreen,
                         bool isBorderLess,
                         bool hasSysmenu,
                         bool hasTitleBar,
                         bool canMinimize,
                         bool canMaximaze,
                         bool canResize,
                         bool clipCursorToWindow,
                         int width, int height,
                         int left = 0, int top = 0);

        std::string m_strName;
        bool m_bIsFullScreen;
        bool m_bIsBorderLess;
        bool m_bHasSysMenu;
        bool m_bHasTitleBar;
        bool m_bCanMinize;
        bool m_bCanMaximaze;
        bool m_bCanResize;
        bool m_bClipCursorToWindow;
        int m_iWidth;
        int m_iHeight;
        int m_iLeft;
        int m_iTop;
    };
}

#endif //GAMEENGINE_WINDOWPARAMETERS_H
