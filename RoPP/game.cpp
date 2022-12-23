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

Responses::GamePassesResponse RoPP::Game::GetGamepasses(std::string Sort, int Limit)
{
    json res = Helper::MakeRobloxRequest
    (
        "https://games.roblox.com/v1/games/" + std::to_string(this->UniverseID) + "/game-passes?sortOrder=" + Sort + "&limit=" + std::to_string(Limit),
        "GET"
    ).JsonObj;

    return Responses::GamePassesResponse().Parse(res);
}

Responses::DeveloperProductCreateResponse RoPP::Game::CreateDeveloperProduct(std::string Name, std::string Description, long Price, long IconImageAssetID)
{
    //untested
    json res = Helper::MakeAuthedRobloxRequest
    (
        "https://develop.roblox.com/v1/universes/" + std::to_string(this->UniverseID) + "/developerproducts?name=" + Name + "&description=" + Description + "&priceInRobux=" + std::to_string(Price) + "&iconImageAssetId=" + std::to_string(IconImageAssetID),
        "POST",
        this->Cookie
    ).JsonObj;

    return Responses::DeveloperProductCreateResponse(res);
}

Responses::GameInstancesResponse RoPP::Game::GetGameInstances(string Type, string Sort, int Limit, bool ExcludeFullGames)
{
    json res;
    
    if (this->Cookie.empty())
    {
        res = Helper::MakeRobloxRequest
        (
            "https://games.roblox.com/v1/games/" + std::to_string(this->PlaceID) + "/servers/" + Type + "?sortOrder=" + Sort + "&excludeFullGames=" + std::to_string(ExcludeFullGames) + "&limit=" + std::to_string(Limit),
            "GET"
        ).JsonObj;
    }
    else
    {
        res = Helper::MakeAuthedRobloxRequest
        (
            "https://games.roblox.com/v1/games/" + std::to_string(this->PlaceID) + "/servers/" + Type + "?sortOrder=" + Sort + "&excludeFullGames=" + std::to_string(ExcludeFullGames) + "&limit=" + std::to_string(Limit),
            "GET",
            this->Cookie
        ).JsonObj;
    }

    return Responses::GameInstancesResponse().Parse(res);
}

Responses::GameSocialLinks RoPP::Game::GetSocialLinks()
{
    json res = Helper::MakeAuthedRobloxRequest
    (
        "https://games.roblox.com/v1/games/" + std::to_string(this->UniverseID) + "/social-links/list",
        "GET",
        this->Cookie
    ).JsonObj;

    return Responses::GameSocialLinks(res);
}

Responses::GameBadges RoPP::Game::GetGameBadges(string Sort, int Limit)
{
    json res = Helper::MakeRobloxRequest
    (
        "https://badges.roblox.com/v1/universes/" + std::to_string(this->UniverseID) + "/badges?sortOrder=" + Sort + "&limit=" + std::to_string(Limit),
        "GET"
    ).JsonObj;

    return Responses::GameBadges(res);
}