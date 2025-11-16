#include "task3.hpp"

MessageType MessageTypeFromString(std::string_view text) noexcept
{
    if (text == "system")
    {
        return MessageType::system;
    }
    if (text == "server")
    {
        return MessageType::server;
    }
    if (text == "session")
    {
        return MessageType::session;
    }

    return MessageType::none;
}

std::string_view ToString(MessageType type) noexcept
{
    switch (type)
    {
    case MessageType::system:
        return "system";
    case MessageType::server:
        return "server";
    case MessageType::session:
        return "session";
    case MessageType::none:
    default:
        return "none";
    }
}
