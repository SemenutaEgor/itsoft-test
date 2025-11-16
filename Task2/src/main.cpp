#include "task2.hpp"

std::string getStatusString(ServerOpStatus status)
{
    switch (status)
    {
    case ServerOpStatus::Duplicate:
        return "Duplicate";
    case ServerOpStatus::NotFound:
        return "NotFound";
    case ServerOpStatus::IOError:
        return "IOError";
    default:
        return "Ok";
    }
}

int main()
{
    const std::string filepath = "servers.txt";

    auto printServersList = [filepath]()
    {
        auto [status, list] = GetServersList(filepath);

        if (status != ServerOpStatus::Ok)
        {
            std::cerr << "Error reading IP list: " << getStatusString(status) << std::endl;
            return;
        }

        std::cout << "Servers loaded:\n";
        for (const auto &s : list)
        {
            std::cout << "  " << s << "\n";
        }
    };

    printServersList();

    auto status_add = AddServer(filepath, "192.168.1.100");
    if (status_add != ServerOpStatus::Ok)
    {
        std::cerr << "Error adding IP: " << getStatusString(status_add) << std::endl;
    }

    printServersList();

    return 0;
}