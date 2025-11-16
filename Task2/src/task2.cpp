

#include "task2.hpp"

std::pair<ServerOpStatus, std::vector<std::string>>
GetServersList(const std::string &filepath)
{
    std::vector<std::string> servers;

    std::ifstream in(filepath);
    if (!in.is_open())
    {

        std::ofstream create(filepath);
        if (!create.is_open())
        {
            return {ServerOpStatus::IOError, {}};
        }

        return {ServerOpStatus::Ok, {}};
    }

    std::string line;
    while (std::getline(in, line))
    {
        if (!line.empty())
            servers.push_back(line);
    }

    if (in.bad())
        return {ServerOpStatus::IOError, {}};

    return {ServerOpStatus::Ok, servers};
}

ServerOpStatus AddServer(const std::string &filepath, const std::string &ip)
{
    auto [status, servers] = GetServersList(filepath);
    if (status != ServerOpStatus::Ok)
        return status;

    for (const auto &s : servers)
    {
        if (s == ip)
        {
            return ServerOpStatus::Duplicate;
        }
    }

    servers.push_back(ip);

    std::ofstream out(filepath, std::ios::trunc);
    if (!out.is_open())
        return ServerOpStatus::IOError;

    for (const auto &s : servers)
    {
        out << s << "\n";
        if (!out.good())
        {
            return ServerOpStatus::IOError;
        }
    }

    return ServerOpStatus::Ok;
}

ServerOpStatus DeleteServer(const std::string &filepath, const std::string &ip)
{
    auto [status, servers] = GetServersList(filepath);
    if (status != ServerOpStatus::Ok)
        return status;

    int index = -1;

    for (size_t i = 0; i < servers.size(); ++i)
    {
        if (servers[i] == ip)
        {
            index = static_cast<int>(i);
            break;
        }
    }

    if (index == -1)
    {
        return ServerOpStatus::NotFound;
    }
    servers.erase(servers.begin() + index);

    std::ofstream out(filepath, std::ios::trunc);
    if (!out.is_open())
        return ServerOpStatus::IOError;

    for (const auto &s : servers)
    {
        out << s << "\n";
        if (!out.good())
        {
            return ServerOpStatus::IOError;
        }
    }

    return ServerOpStatus::Ok;
}
