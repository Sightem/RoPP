#include "../include/ropp.h"
#include "../include/helper.h"
#include "../include/request.hpp"
#include "../include/responses.h"

std::vector<Responses::User> RoPP::User::get_friends(const std::string& sort)
{
    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://friends.roblox.com/v1/users/" + std::to_string(this->user_id) + "/friends?userSort=" + sort,
        "GET"
    ).JsonObj;
    
    std::vector<Responses::User> Friends;

    for (auto& element : res["data"])
    {
        Friends.emplace_back(element);
    }

    return Friends;
}

std::vector<Responses::User> RoPP::User::get_followers(const std::string& sort, int limit)
{
    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://friends.roblox.com/v1/users/" + std::to_string(this->user_id) + "/followers?sortOrder=" + sort + "&limit=" + std::to_string(limit),
        "GET"
    ).JsonObj;

    std::vector<Responses::User> Followers;

    for (auto& element : res["data"])
    {
        Followers.emplace_back(element);
    }

    return Followers;
}

std::vector<Responses::User> RoPP::User::get_followings(const std::string& sort, int limit)
{
    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://friends.roblox.com/v1/users/" + std::to_string(this->user_id) + "/followings?sortOrder=" + sort + "&limit=" + std::to_string(limit),
        "GET"
    ).JsonObj;

    std::vector<Responses::User> Followings;

    for (auto& element : res["data"])
    {
        Followings.emplace_back(element);
    }

    return Followings;
}

std::vector<Responses::GroupWithRole> RoPP::User::get_groups()
{
    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://groups.roblox.com/v1/users/" + std::to_string(this->user_id) + "/groups/roles",
        "GET"
    ).JsonObj;

    std::vector<Responses::GroupWithRole> Groups;

    for (auto& element : res["data"])
    {
        Groups.emplace_back(element);
    }

    return Groups;
}

std::vector<Responses::Badge> RoPP::User::get_badges()
{
    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://badges.roblox.com/v1/users/" + std::to_string(this->user_id) + "/badges",
        "GET"
    ).JsonObj;

    std::vector<Responses::Badge> Badges;

    for (auto& element : res["data"])
    {
        Badges.emplace_back(element);
    }

    return Badges;
}

std::vector<Responses::Experience> RoPP::User::get_experiences(const std::string& sort, int limit)
{
    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://games.roblox.com/v2/users/" + std::to_string(this->user_id) + "/games?sortOrder=" + sort + "&limit=" + std::to_string(limit),
        "GET"
    ).JsonObj;

    std::vector<Responses::Experience> Experiences;

    for (auto& element : res["data"])
    {
        Experiences.emplace_back(element);
    }

    return Experiences;
    
}

std::vector<Responses::Experience> RoPP::User::get_favorite_experiences(const std::string& sort, int limit)
{
    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://games.roblox.com/v2/users/" + std::to_string(this->user_id) + "/favorite/games?sortOrder=" + sort + "&limit=" + std::to_string(limit),
        "GET"
    ).JsonObj;

    std::vector<Responses::Experience> Experiences;

    for (auto& element : res["data"])
    {
        Experiences.emplace_back(element);
    }

    return Experiences;
}

std::vector<std::string> RoPP::User::get_past_usernames(const std::string& sort, int limit)
{
    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://users.roblox.com/v1/users/" + std::to_string(this->user_id) + "/username-history?limit=" + std::to_string(limit) + "&sortOrder=" + sort,
        "GET"
    ).JsonObj;

    std::vector<std::string> PastUsernames;

    for (auto& element : res["data"])
    {
        PastUsernames.emplace_back(element["name"]);
    }

    return PastUsernames;
}

Responses::Group RoPP::User::get_primary_group()
{
    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://groups.roblox.com/v1/users/" + std::to_string(this->user_id) + "/groups/primary/role",
        "GET"
    ).JsonObj;

    return Responses::Group(res);
}

std::vector<Responses::InventoryAsset> RoPP::User::get_inventory(const std::vector<std::string>& AssetType, const std::string& Sort, int Limit)
{
    std::string AssetTypeString = "";
    for (size_t i = 0; i < AssetType.size(); i++)
    {
        AssetTypeString += AssetType[i];

        if (i != AssetType.size() - 1)
            AssetTypeString += ",";
    }

    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://inventory.roblox.com/v2/users/" + std::to_string(this->user_id) + "/inventory?assetTypes=" + AssetTypeString + "&sortOrder=" + Sort + "&limit=" + std::to_string(Limit),
        "GET"
    ).JsonObj;

    std::vector<Responses::InventoryAsset> Assets;

    for (auto& element : res["data"])
    {
        Assets.emplace_back(element);
    }

    return Assets;
}

bool RoPP::User::can_inventory_be_viewed()
{
    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://inventory.roblox.com/v1/users/" + std::to_string(this->user_id) + "/can-view-inventory",
        "GET"
    ).JsonObj;

    return res["canView"];
}

Responses::User RoPP::User::get_user()
{
    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://users.roblox.com/v1/users/" + std::to_string(this->user_id),
        "GET"
    ).JsonObj;

    return Responses::User(res);
}