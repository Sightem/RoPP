#include "../include/ropp.h"
#include "../include/helper.h"
#include "../include/request.hpp"


std::vector<Responses::SearchedUser> RoPP::Other::UserSearch(string Keyword, int Limit)
{
    json res = Helper::MakeRobloxRequest
    (
        "https://users.roblox.com/v1/users/search?keyword=" + Keyword + "&limit=" + std::to_string(Limit),
        "GET"
    ).JsonObj;

    std::vector<Responses::SearchedUser> users;
    for (size_t i = 0; i < res["data"].size(); i++)
    {
        users.push_back(Responses::SearchedUser(res["data"][i]));
    }

    return users;
}

json RoPP::Other::GroupSearch(string Keyword, bool prioritizeExactMatch, int Limit)
{
    json res = Helper::MakeRobloxRequest
    (
        "https://groups.roblox.com/v1/groups/search?keyword=" + Keyword + "&prioritizeExactMatch=" + std::to_string(prioritizeExactMatch) + "&limit=" + std::to_string(Limit),
        "GET"
    ).JsonObj;

    return res;
}

std::string RoPP::Other::ValidateUsername(std::string Username)
{
    json res = Helper::MakeRobloxRequest
    (
        "https://auth.roblox.com/v2/usernames/validate?request.username=" + Username + "&request.birthday=1970-10-10",
        "GET"
    ).JsonObj;

    return res["message"];
}

long RoPP::Other::GetGameUniverseID(long PlaceID)
{
    json res = Helper::MakeRobloxRequest
    (
        "https://apis.roblox.com/universes/v1/places/" + std::to_string(PlaceID) + "/universe",
        "GET"
    ).JsonObj;

    return res["universeId"];
}

std::vector<Responses::UserPresence> RoPP::Other::GetUsersPresence(std::vector<long> UIDs)
{
    json data = 
    {
        {"userIds", UIDs}
    };

    json res;
    
    if (!this->Cookie.empty())
    {
        res = Helper::MakeAuthedRobloxRequest
        (
            "https://presence.roblox.com/v1/presence/users",
            "POST",
            this->Cookie,
            true,
            data
        ).JsonObj;
    } else
    {
        res = Helper::MakeRobloxRequest
        (
            "https://presence.roblox.com/v1/presence/users",
            "POST",
            data
        ).JsonObj;
    }

    std::vector<Responses::UserPresence> presences;
    for (size_t i = 0; i < res["userPresences"].size(); i++)
    {
        presences.push_back(Responses::UserPresence(res["userPresences"][i]));
    }

    return presences;
}
