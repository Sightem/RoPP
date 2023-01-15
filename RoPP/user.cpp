#include "../include/ropp.h"
#include "../include/helper.h"
#include "../include/request.hpp"
#include "../include/responses.h"

Responses::FriendsResponse RoPP::User::GetFriends(string Sort)
{
   json res = Helper::MakeRobloxRequest
    (
        "https://friends.roblox.com/v1/users/" + std::to_string(this->UID) + "/friends?userSort=" + Sort,
        "GET"
    ).JsonObj;

    return Responses::FriendsResponse().Parse(res);
}

Responses::FollowersResponse RoPP::User::GetFollowers(string Sort, int Limit)
{
    json res = Helper::MakeRobloxRequest
    (
        "https://friends.roblox.com/v1/users/" + std::to_string(this->UID) + "/followers?sortOrder=" + Sort + "&limit=" + std::to_string(Limit),
        "GET"
    ).JsonObj;

    return Responses::FollowersResponse().Parse(res);
}

Responses::FollowingsResponse RoPP::User::GetFollowings(string Sort, int Limit)
{
    json res = Helper::MakeRobloxRequest
    (
        "https://friends.roblox.com/v1/users/" + std::to_string(this->UID) + "/followings?sortOrder=" + Sort + "&limit=" + std::to_string(Limit),
        "GET"
    ).JsonObj;

    return Responses::FollowingsResponse().Parse(res);
}

std::vector<Responses::GroupWithRole> RoPP::User::GetGroups()
{
    json res = Helper::MakeRobloxRequest
    (
        "https://groups.roblox.com/v1/users/" + std::to_string(this->UID) + "/groups/roles",
        "GET"
    ).JsonObj;

    std::vector<Responses::GroupWithRole> Groups;

    for (auto& element : res["data"])
    {
        Groups.emplace_back(element);
    }

    return Groups;
}

std::vector<Responses::Badge> RoPP::User::GetBadges()
{
    json res = Helper::MakeRobloxRequest
    (
        "https://badges.roblox.com/v1/users/" + std::to_string(this->UID) + "/badges",
        "GET"
    ).JsonObj;

    std::vector<Responses::Badge> Badges;

    for (auto& element : res["data"])
    {
        Badges.emplace_back(element);
    }

    return Badges;
}

Responses::UserExperienceResponse RoPP::User::GetExperiences(string Sort, int limit)
{
    json res = Helper::MakeRobloxRequest
    (
        "https://games.roblox.com/v2/users/" + std::to_string(this->UID) + "/games?sortOrder=" + Sort + "&limit=" + std::to_string(limit),
        "GET"
    ).JsonObj;

    return Responses::UserExperienceResponse().Parse(res);
}

Responses::UserFavoriteExperiences RoPP::User::GetFavoriteExperiences(string Sort, int limit)
{
    json res = Helper::MakeRobloxRequest
    (
        "https://games.roblox.com/v2/users/" + std::to_string(this->UID) + "/favorite/games?sortOrder=" + Sort + "&limit=" + std::to_string(limit),
        "GET"
    ).JsonObj;

    return Responses::UserFavoriteExperiences().Parse(res);
}

std::vector<std::string> RoPP::User::GetPastUsernames(std::string Sort, int limit)
{
    json res = Helper::MakeRobloxRequest
    (
        "https://users.roblox.com/v1/users/" + std::to_string(this->UID) + "/username-history?limit=" + std::to_string(limit) + "&sortOrder=" + Sort,
        "GET"
    ).JsonObj;

    std::vector<std::string> PastUsernames;

    for (auto& element : res["data"])
    {
        PastUsernames.emplace_back(element["name"]);
    }

    return PastUsernames;
}

Responses::Group RoPP::User::GetPrimaryGroup()
{
    json res = Helper::MakeRobloxRequest
    (
        "https://groups.roblox.com/v1/users/" + std::to_string(this->UID) + "/groups/primary/role",
        "GET"
    ).JsonObj;

    return Responses::Group(res);
}

std::vector<Responses::InventoryAsset> RoPP::User::GetInventory(std::vector<string> AssetType, string Sort, int Limit)
{
    string AssetTypeString = "";
    for (size_t i = 0; i < AssetType.size(); i++)
    {
        AssetTypeString += AssetType[i];

        if (i != AssetType.size() - 1)
            AssetTypeString += ",";
    }

    json res = Helper::MakeRobloxRequest
    (
        "https://inventory.roblox.com/v2/users/" + std::to_string(this->UID) + "/inventory?assetTypes=" + AssetTypeString + "&sortOrder=" + Sort + "&limit=" + std::to_string(Limit),
        "GET"
    ).JsonObj;

    std::vector<Responses::InventoryAsset> Assets;

    for (auto& element : res["data"])
    {
        Assets.emplace_back(element);
    }

    return Assets;
}

bool RoPP::User::CanInventoryBeViewed()
{
    json res = Helper::MakeRobloxRequest
    (
        "https://inventory.roblox.com/v1/users/" + std::to_string(this->UID) + "/can-view-inventory",
        "GET"
    ).JsonObj;

    return res["canView"];
}

Responses::User RoPP::User::GetUser()
{
    json res = Helper::MakeRobloxRequest
    (
        "https://users.roblox.com/v1/users/" + std::to_string(this->UID),
        "GET"
    ).JsonObj;

    return Responses::User(res);
}