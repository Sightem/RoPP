#include "ropp.h"
#include "../include/request.hpp"

json RoPP::Group::GetGroupInfo()
{
    Request req("https://groups.roblox.com/v1/groups/" + std::to_string(this->GID));
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data);
}

json RoPP::Group::GetGroupOwner()
{
    Request req("https://groups.roblox.com/v1/groups/" + std::to_string(this->GID));
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data)["owner"];
}

std::string RoPP::Group::GetGroupName()
{
    Request req("https://groups.roblox.com/v1/groups/" + std::to_string(this->GID));
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data)["name"];
}

std::string RoPP::Group::GetGroupDescription()
{
    Request req("https://groups.roblox.com/v1/groups/" + std::to_string(this->GID));
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data)["description"];
}

json RoPP::Group::GetGroupShout()
{
    Request req("https://groups.roblox.com/v1/groups/" + std::to_string(this->GID));
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data)["shout"];
}

long RoPP::Group::GetMemberCount()
{
    Request req("https://groups.roblox.com/v1/groups/" + std::to_string(this->GID));
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data)["memberCount"];
}

long RoPP::Group::GetOwnerID()
{
    Request req("https://groups.roblox.com/v1/groups/" + std::to_string(this->GID));
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data)["owner"]["userId"];
}

std::string RoPP::Group::GetOwnerName()
{
    Request req("https://groups.roblox.com/v1/groups/" + std::to_string(this->GID));
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data)["owner"]["username"];
}

std::string RoPP::Group::GetOwnerDisplayName()
{
    Request req("https://groups.roblox.com/v1/groups/" + std::to_string(this->GID));
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data)["owner"]["displayName"];
}