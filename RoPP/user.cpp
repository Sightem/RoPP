#include "../include/ropp.h"
#include "../include/helper.h"
#include "../include/request.hpp"
#include "../include/responses.h"

std::vector<Responses::User> RoPP::User::GetFriends(std::string Sort)
{
    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://friends.roblox.com/v1/users/" + std::to_string(this->UID) + "/friends?userSort=" + Sort,
        "GET"
    ).JsonObj;
    
    std::vector<Responses::User> Friends;

    for (auto& element : res["data"])
    {
        Friends.emplace_back(element);
    }

    return Friends;
}

std::vector<Responses::User> RoPP::User::GetFollowers(std::string Sort, int Limit)
{
    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://friends.roblox.com/v1/users/" + std::to_string(this->UID) + "/followers?sortOrder=" + Sort + "&limit=" + std::to_string(Limit),
        "GET"
    ).JsonObj;

    std::vector<Responses::User> Followers;

    for (auto& element : res["data"])
    {
        Followers.emplace_back(element);
    }

    return Followers;
}

std::vector<Responses::User> RoPP::User::GetFollowings(std::string Sort, int Limit)
{
    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://friends.roblox.com/v1/users/" + std::to_string(this->UID) + "/followings?sortOrder=" + Sort + "&limit=" + std::to_string(Limit),
        "GET"
    ).JsonObj;

    std::vector<Responses::User> Followings;

    for (auto& element : res["data"])
    {
        Followings.emplace_back(element);
    }

    return Followings;
}

std::vector<Responses::GroupWithRole> RoPP::User::GetGroups()
{
    ordered_json res = Helper::MakeRobloxRequest
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
    ordered_json res = Helper::MakeRobloxRequest
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

std::vector<Responses::Experience> RoPP::User::GetExperiences(string Sort, int limit)
{
    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://games.roblox.com/v2/users/" + std::to_string(this->UID) + "/games?sortOrder=" + Sort + "&limit=" + std::to_string(limit),
        "GET"
    ).JsonObj;

    std::vector<Responses::Experience> Experiences;

    for (auto& element : res["data"])
    {
        Experiences.emplace_back(element);
    }

    return Experiences;
    
}

std::vector<Responses::Experience> RoPP::User::GetFavoriteExperiences(string Sort, int limit)
{
    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://games.roblox.com/v2/users/" + std::to_string(this->UID) + "/favorite/games?sortOrder=" + Sort + "&limit=" + std::to_string(limit),
        "GET"
    ).JsonObj;

    std::vector<Responses::Experience> Experiences;

    for (auto& element : res["data"])
    {
        Experiences.emplace_back(element);
    }

    return Experiences;
}

std::vector<std::string> RoPP::User::GetPastUsernames(std::string Sort, int limit)
{
    ordered_json res = Helper::MakeRobloxRequest
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
    ordered_json res = Helper::MakeRobloxRequest
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

    ordered_json res = Helper::MakeRobloxRequest
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
    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://inventory.roblox.com/v1/users/" + std::to_string(this->UID) + "/can-view-inventory",
        "GET"
    ).JsonObj;

    return res["canView"];
}

Responses::User RoPP::User::GetUser()
{
    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://users.roblox.com/v1/users/" + std::to_string(this->UID),
        "GET"
    ).JsonObj;

    return Responses::User(res);
}