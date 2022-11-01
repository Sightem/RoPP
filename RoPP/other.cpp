#include "ropp.h"
#include "../include/helper.h"
#include "../include/request.hpp"


json RoPP::Other::UserSearch(string Keyword, int Limit)
{
    json res = Helper::MakeRobloxRequest
    (
        "https://users.roblox.com/v1/users/search?keyword=" + Keyword + "&limit=" + std::to_string(Limit),
        "GET"
    ).JsonObj;

    return res;
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

int RoPP::Other::GetGameUniverseID(int PlaceID)
{
    json res = Helper::MakeRobloxRequest
    (
        "https://api.roblox.com/universes/get-universe-containing-place?placeid=" + std::to_string(PlaceID),
        "GET"
    ).JsonObj;

    return res["UniverseId"];
}