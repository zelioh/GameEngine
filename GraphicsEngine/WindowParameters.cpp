//
// Created by tangt on 26/10/2020.
//
// Class use for parameters the window
//

#include "WindowParameters.h"

graphics::WindowParameters::WindowParameters(const std::string &name,
                                             bool isFullScreen,
                                             bool isBorderLess,
                                             bool hasSysmenu,
                                             bool hasTitleBar,
                                             bool canMinimize,
                                             bool canMaximaze,
                                             bool canResize,
                                             int width,
                                             int height,
                                             int left /* =0 */,
                                             int top/* =0 */):
m_strName(name),
m_bIsFullScreen(isFullScreen),
m_bIsBorderLess(isBorderLess),
m_bHasSysMenu(hasSysmenu),
m_bHasTitleBar(hasTitleBar),
m_bCanMinize(canMinimize),
m_bCanMaximaze(canMaximaze),
m_bCanResize(canResize),
m_iWidth(width),
m_iHeight(height),
m_iLeft(left),
m_iTop(top)
{
}