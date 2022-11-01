#include "ropp.h"
#include "../include/helper.h"
#include "../include/request.hpp"

json RoPP::Group::GetGroupInfo()
{
    return Helper::MakeRobloxRequest
    (
        "https://groups.roblox.com/v1/groups/" + std::to_string(this->GID),
        "GET"
    ).JsonObj;
}

json RoPP::Group::GetGroupOwner()
{
    return GetGroupInfo()["owner"];
}

std::string RoPP::Group::GetGroupName()
{
    return GetGroupInfo()["name"];
}

std::string RoPP::Group::GetGroupDescription()
{
    return GetGroupInfo()["description"];
}

json RoPP::Group::GetGroupShout()
{
    return GetGroupInfo()["shout"];
}

long RoPP::Group::GetMemberCount()
{
    return GetGroupInfo()["memberCount"];
}

long RoPP::Group::GetOwnerID()
{
    return GetGroupInfo()["owner"]["userId"];
}

std::string RoPP::Group::GetOwnerName()
{
    return GetGroupInfo()["owner"]["username"];
}

std::string RoPP::Group::GetOwnerDisplayName()
{
    return GetGroupInfo()["owner"]["displayName"];
}

json RoPP::Group::GetNameHistory(string Sort, int Limit)
{
    return Helper::MakeRobloxRequest
    (
        "https://groups.roblox.com/v1/groups/" + std::to_string(this->GID) + "/name-history?sortOrder=" + Sort + "&limit=" + std::to_string(Limit),
        "GET"
    ).JsonObj;
}

json RoPP::Group::GetGroupWall(string Sort, int Limit)
{
    return Helper::MakeRobloxRequest
    (
        "https://groups.roblox.com/v1/groups/" + std::to_string(this->GID) + "/wall/posts?sortOrder=" + Sort + "&limit=" + std::to_string(Limit),
        "GET"
    ).JsonObj;
}

bool RoPP::Group::IsPublicEntryAllowed()
{
    return GetGroupInfo()["publicEntryAllowed"];
}

bool RoPP::Group::IsBuildersClubOnly()
{
    return GetGroupInfo()["isBuildersClubOnly"];
}

json RoPP::Group::GetGames(string AccessFilter, string Sort, int Limit)
{
    return Helper::MakeRobloxRequest
    (
        "https://games.roblox.com/v2/groups/" + std::to_string(this->GID) + "/games?accessFilter=" + AccessFilter + "&sortOrder=" + Sort + "&limit=" + std::to_string(Limit),
        "GET"
    ).JsonObj;
}