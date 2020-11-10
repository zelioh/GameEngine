//
// Created by FiercePC on 10/11/2020.
//

#ifndef GAMEENGINE_CORE_UTILS_H
#define GAMEENGINE_CORE_UTILS_H

#include <string>

namespace core
{
    namespace assert
    {
        inline void assertExpression(bool expression);
        inline void assertExpressionWithMessage(bool expression, const std::string & message);
        inline void assertAlways();
        inline void assertAlwaysWithMessage(const std::string & message);
    }

    namespace console
    {
        enum class Type
        {
            log,
            error,
            warning,
            debug
        };

        inline void message(const Type & type, const std::string & message);
    }
}

#define ASSERT(expression) core::assert::assertExpression(expression)
#define ASSERT_MESSAGE(expression, message) core::assert::assertExpressionWithMessage(expression, message)
#define ASSERT_ALWAYS() core::assert::assertAlways()
#define ASSERT_ALWAYS_MESSAGE(message) core::assert::assertAlwaysWithMessage(message)

#define LOG_MESSAGE(str) core::console::message(core::console::Type::log, str)
#define ERROR_MESSAGE(str) core::console::message(core::console::Type::error, str)
#define WARNING_MESSAGE(str) core::console::message(core::console::Type::warning, str)
#define DEBUG_MESSAGE(str) core::console::message(core::console::Type::debug, str)

#include "Core_utils.inl"

#endif //GAMEENGINE_CORE_UTILS_H
