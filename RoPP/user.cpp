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

Responses::UserGroupsResponse RoPP::User::GetGroups()
{
    json res = Helper::MakeRobloxRequest
    (
        "https://groups.roblox.com/v1/users/" + std::to_string(this->UID) + "/groups/roles",
        "GET"
    ).JsonObj;

    return Responses::UserGroupsResponse().Parse(res);
}

Responses::UserBadgesResponse RoPP::User::GetBadges()
{
    json res = Helper::MakeRobloxRequest
    (
        "https://badges.roblox.com/v1/users/" + std::to_string(this->UID) + "/badges",
        "GET"
    ).JsonObj;

    return Responses::UserBadgesResponse(res);
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

Responses::PastUsernames RoPP::User::GetPastUsernames(string Sort, int limit)
{
    json res = Helper::MakeRobloxRequest
    (
        "https://users.roblox.com/v1/users/" + std::to_string(this->UID) + "/username-history?limit=" + std::to_string(limit) + "&sortOrder=" + Sort,
        "GET"
    ).JsonObj;

    return Responses::PastUsernames().Parse(res);
}

Responses::Group RoPP::User::GetPrimaryGroup()
{
    json res = Helper::MakeRobloxRequest
    (
        "https://groups.roblox.com/v1/users/" + std::to_string(this->UID) + "/groups/primary/role",
        "GET"
    ).JsonObj;

    return Responses::Group().Parse(res);
}

Responses::InventoryResponse RoPP::User::GetInventory(std::vector<string> AssetType, string Sort, int Limit)
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

    return Responses::InventoryResponse().Parse(res);
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