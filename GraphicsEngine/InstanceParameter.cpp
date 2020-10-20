//
// Created by tangt on 07/10/2020.
//
// This class is use for parameter a graphics::Instance inside the motor
//

#include "InstanceParameter.h"

void graphics::InstanceParameter::setApplicationName(const std::string &applicationName)
{
    m_strApplicationName = applicationName;
}

const std::string & graphics::InstanceParameter::getApplicationName() const
{
    return m_strApplicationName;
}

void graphics::InstanceParameter::setProjectMajorVersion(uint16_t projectMajorVersion)
{
    m_iProjectMajorVersion = projectMajorVersion;
}

uint16_t graphics::InstanceParameter::getProjectMajorVersion() const
{
    return m_iProjectMajorVersion;
}

void graphics::InstanceParameter::setProjectMinorVersion(uint16_t projectMinorVersion)
{
    m_iProjectMinorVersion = projectMinorVersion;
}

uint16_t graphics::InstanceParameter::getProjectMinorVersion() const
{
    return m_iProjectMinorVersion;
}

void graphics::InstanceParameter::setProjectPatchVersion(uint16_t projectPatchVersion)
{
    m_iProjectPatchVersion = projectPatchVersion;
}

uint16_t graphics::InstanceParameter::getProjectPatchVersion() const
{
    return m_iProjectPatchVersion;
}

void graphics::InstanceParameter::setProjectVersions(uint16_t major, uint16_t minor, uint16_t patch)
{
    m_iProjectMajorVersion = major;
    m_iProjectMinorVersion = minor;
    m_iProjectPatchVersion = patch;
}