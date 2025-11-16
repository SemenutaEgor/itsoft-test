#pragma once

#include <string_view>

enum class MessageType
{
    system,
    server,
    session,
    none
};

MessageType MessageTypeFromString(std::string_view) noexcept;

std::string_view ToString(MessageType) noexcept;
