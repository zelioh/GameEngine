//
// Created by FiercePC on 10/11/2020.
//

#include "Core_utils.h"
#include <cassert>
#include <iostream>

void core::assert::assertExpression(bool expression)
{
    assert(expression);
}

void core::assert::assertExpressionWithMessage(bool expression, const std::string &message)
{
    if (!expression) {
        core::console::message(core::console::Type::error, message);
    }
    assert(expression);
}

void core::assert::assertAlways()
{
    assert(false);
}

void core::assert::assertAlwaysWithMessage(const std::string &message)
{
    core::console::message(core::console::Type::error, message);
    assert(false);
}

void core::console::message(const Type & type, const std::string &message)
{
    std::string header;

    if (type == Type::log) {
        header = "[LOG]: ";
    } else if (type == Type::warning) {
        header = "[WARNING]: ";
    } else if (type == Type::debug) {
        header = "[DEBUG]: ";
    } else if (type == Type::error) {
        std::cerr << "[ERROR]: " << message << std::endl;
        return;
    }
    std::cout << header << message << std::endl;
}