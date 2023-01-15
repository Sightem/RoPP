#include "../include/ropp.h"
#include "../include/helper.h"
#include "../include/request.hpp"

Responses::Group RoPP::Group::GetGroupInfo()
{
    json res = Helper::MakeRobloxRequest
    (
        "https://groups.roblox.com/v1/groups/" + std::to_string(this->GroupID),
        "GET"
    ).JsonObj;

    return Responses::Group(res);
}

Responses::NameHistoryResponse RoPP::Group::GetNameHistory(string Sort, int Limit)
{
    json res = Helper::MakeRobloxRequest
    (
        "https://groups.roblox.com/v1/groups/" + std::to_string(this->GroupID) + "/name-history?sortOrder=" + Sort + "&limit=" + std::to_string(Limit),
        "GET"
    ).JsonObj;

    return Responses::NameHistoryResponse().Parse(res);
}

std::vector<Responses::GroupWallPost> RoPP::Group::GetGroupWall(std::string Sort, int Limit)
{
    json res = Helper::MakeRobloxRequest
    (
        "https://groups.roblox.com/v1/groups/" + std::to_string(this->GroupID) + "/wall/posts?sortOrder=" + Sort + "&limit=" + std::to_string(Limit),
        "GET"
    ).JsonObj;

    std::vector<Responses::GroupWallPost> posts;
    for (auto& element : res["data"])
    {
        posts.emplace_back(element);
    }

    return posts;
}

Responses::GroupExperiencesResponse RoPP::Group::GetGames(string AccessFilter, string Sort, int Limit)
{
    json res = Helper::MakeRobloxRequest
    (
        "https://games.roblox.com/v2/groups/" + std::to_string(this->GroupID) + "/games?accessFilter=" + AccessFilter + "&sortOrder=" + Sort + "&limit=" + std::to_string(Limit),
        "GET"
    ).JsonObj;

    return Responses::GroupExperiencesResponse().Parse(res);
}