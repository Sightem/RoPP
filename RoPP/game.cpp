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

    return Responses::PlaceInfoResponse(res["data"][0]);
}

Responses::ExperienceVotes RoPP::Game::GetVotes()
{
    json res = Helper::MakeRobloxRequest
    (
        "https://games.roblox.com/v1/games/votes?universeIds=" + std::to_string(this->UniverseID),
        "GET"
    ).JsonObj;

    return Responses::ExperienceVotes(res["data"][0]);
}

std::vector<Responses::GamePass> RoPP::Game::GetGamepasses(std::string Sort, int Limit)
{
    json res = Helper::MakeRobloxRequest
    (
        "https://games.roblox.com/v1/games/" + std::to_string(this->UniverseID) + "/game-passes?sortOrder=" + Sort + "&limit=" + std::to_string(Limit),
        "GET"
    ).JsonObj;

    std::vector<Responses::GamePass> passes;
    for (auto& pass : res["data"])
    {
        passes.emplace_back(pass);
    }

    return passes;
}

Responses::DeveloperProductCreateResponse RoPP::Game::CreateDeveloperProduct(std::string Name, std::string Description, long Price, long IconImageAssetID)
{
    //untested
    json res = Helper::MakeAuthedRobloxRequest
    (
        "https://develop.roblox.com/v1/universes/" + std::to_string(this->UniverseID) + "/developerproducts?name=" + Name + "&description=" + Description + "&priceInRobux=" + std::to_string(Price) + "&iconImageAssetId=" + std::to_string(IconImageAssetID),
        "POST",
        this->Cookie,
        true
    ).JsonObj;

    return Responses::DeveloperProductCreateResponse(res);
}

std::vector<Responses::GameInstance> RoPP::Game::GetGameInstances(string Type, string Sort, int Limit, bool ExcludeFullGames)
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
            this->Cookie,
            true
        ).JsonObj;
    }

    std::vector<Responses::GameInstance> instances;
    for (auto& instance : res["data"])
    {
        instances.push_back(Responses::GameInstance(instance));
    }

    return instances;
}

Responses::GameSocialLinks RoPP::Game::GetSocialLinks()
{
    json res = Helper::MakeAuthedRobloxRequest
    (
        "https://games.roblox.com/v1/games/" + std::to_string(this->UniverseID) + "/social-links/list",
        "GET",
        this->Cookie,
        false
    ).JsonObj;

    return Responses::GameSocialLinks(res);
}

std::vector<Responses::Badge> RoPP::Game::GetGameBadges(std::string Sort, int Limit)
{
    json res = Helper::MakeRobloxRequest
    (
        "https://badges.roblox.com/v1/universes/" + std::to_string(this->UniverseID) + "/badges?sortOrder=" + Sort + "&limit=" + std::to_string(Limit),
        "GET"
    ).JsonObj;

    std::vector<Responses::Badge> badges;
    for (auto& badge : res["data"])
    {
        badges.emplace_back(badge);
    }

    return badges;
}