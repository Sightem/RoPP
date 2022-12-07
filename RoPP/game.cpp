#include "../include/ropp.h"
#include "../include/helper.h"
#include "../include/request.hpp"

long RoPP::Game::GetUniverseID()
{
    json res = Helper::MakeRobloxRequest
    (
        "https://apis.roblox.com/universes/v1/places/" + std::to_string(this->PlaceID) + "/universe",
        "GET"
    ).JsonObj;

    return res["universeId"];
}

Responses::PlaceInfoResponse RoPP::Game::GetPlaceInfo()
{
    json res = Helper::MakeRobloxRequest
    (
        "https://games.roblox.com/v1/games?universeIds=" + std::to_string(this->UniverseID),
        "GET"
    ).JsonObj;

    return Responses::PlaceInfoResponse().Parse(res["data"][0]);
}

Responses::ExperienceVotes RoPP::Game::GetVotes()
{
    json res = Helper::MakeRobloxRequest
    (
        "https://games.roblox.com/v1/games/votes?universeIds=" + std::to_string(this->UniverseID),
        "GET"
    ).JsonObj;

    return Responses::ExperienceVotes().Parse(res["data"][0]);
}

Responses::ExperienceBadgesResponse RoPP::Game::GetGamepassInfo(std::string Sort, int Limit)
{
    json res = Helper::MakeRobloxRequest
    (
        "https://games.roblox.com/v1/games/" + std::to_string(this->UniverseID) + "/game-passes?sortOrder=" + Sort + "&limit=" + std::to_string(Limit),
        "GET"
    ).JsonObj;

    return Responses::ExperienceBadgesResponse().Parse(res);
}