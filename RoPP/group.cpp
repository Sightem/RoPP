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

json RoPP::Group::GetNameHistory(string Sort, int Limit)
{
    Request req("https://groups.roblox.com/v1/groups/" + std::to_string(this->GID) + "/name-history?sortOrder=" + Sort + "&limit=" + std::to_string(Limit));
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data);
}

json RoPP::Group::GetGroupWall(string Sort, int Limit)
{
    Request req("https://groups.roblox.com/v1/groups/" + std::to_string(this->GID) + "/wall/posts?sortOrder=" + Sort + "&limit=" + std::to_string(Limit));
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data);
}

bool RoPP::Group::IsGroupLocked()
{
    Request req("https://groups.roblox.com/v1/groups/" + std::to_string(this->GID));
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data)["isLocked"];
}

bool RoPP::Group::IsPublicEntryAllowed()
{
    Request req("https://groups.roblox.com/v1/groups/" + std::to_string(this->GID));
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data)["publicEntryAllowed"];
}

bool RoPP::Group::IsBuildersClubOnly()
{
    Request req("https://groups.roblox.com/v1/groups/" + std::to_string(this->GID));
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data)["isBuildersClubOnly"];
}