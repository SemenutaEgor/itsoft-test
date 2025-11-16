#pragma once
#include <string>
#include <vector>
#include <utility>
#include <fstream>
#include <iostream>

enum class ServerOpStatus
{
    Ok,
    Duplicate,
    NotFound,
    IOError
};

std::pair<ServerOpStatus, std::vector<std::string>>
GetServersList(const std::string&);

ServerOpStatus AddServer(const std::string&, const std::string&);

ServerOpStatus DeleteServer(const std::string&, const std::string&);