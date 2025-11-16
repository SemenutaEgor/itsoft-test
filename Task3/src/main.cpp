#include <iostream>
#include "task3.hpp"

int main()
{
    for (std::string s : {"system", "server", "session", "foo"})
    {
        MessageType t = MessageTypeFromString(s);
        std::cout << "input: " << s << " -> enum: " << ToString(t) << "\n";
    }

    MessageType types[] = {
        MessageType::system,
        MessageType::server,
        MessageType::session,
        MessageType::none};

    std::cout << "\nAll enums:\n";
    for (auto t : types)
    {
        std::cout << "  " << ToString(t) << "\n";
    }

    return 0;
}
