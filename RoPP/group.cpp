#include "ropp.h"
#include "../include/helper.h"
#include "../include/request.hpp"

Responses::Group RoPP::Group::GetGroupInfo()
{
    json res = Helper::MakeRobloxRequest
    (
        "https://groups.roblox.com/v1/groups/" + std::to_string(this->GID),
        "GET"
    ).JsonObj;

    //listen, i know this is bad, but it was either this or creating a new and almost identical group class
    json hack = 
    {
        {"group", res}
    };

    return Responses::Group().Parse(hack);
}

Responses::NameHistoryResponse RoPP::Group::GetNameHistory(string Sort, int Limit)
{
    json res = Helper::MakeRobloxRequest
    (
        "https://groups.roblox.com/v1/groups/" + std::to_string(this->GID) + "/name-history?sortOrder=" + Sort + "&limit=" + std::to_string(Limit),
        "GET"
    ).JsonObj;

    return Responses::NameHistoryResponse().Parse(res);
}

Responses::GroupWallResponse RoPP::Group::GetGroupWall(string Sort, int Limit)
{
    json res = Helper::MakeRobloxRequest
    (
        "https://groups.roblox.com/v1/groups/" + std::to_string(this->GID) + "/wall/posts?sortOrder=" + Sort + "&limit=" + std::to_string(Limit),
        "GET"
    ).JsonObj;

    return Responses::GroupWallResponse().Parse(res);

}

Responses::GroupExperiencesResponse RoPP::Group::GetGames(string AccessFilter, string Sort, int Limit)
{
    json res = Helper::MakeRobloxRequest
    (
        "https://games.roblox.com/v2/groups/" + std::to_string(this->GID) + "/games?accessFilter=" + AccessFilter + "&sortOrder=" + Sort + "&limit=" + std::to_string(Limit),
        "GET"
    ).JsonObj;

    return Responses::GroupExperiencesResponse().Parse(res);
}