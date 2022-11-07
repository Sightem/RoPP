#include "ropp.h"
#include "../include/helper.h"
#include "../include/request.hpp"
#include "../include/responses.h"

using namespace Responses;

FriendsResponse RoPP::User::GetFriends(string Sort)
{
   json res = Helper::MakeRobloxRequest
    (
        "https://friends.roblox.com/v1/users/" + std::to_string(this->UID) + "/friends?userSort=" + Sort,
        "GET"
    ).JsonObj;

    return FriendsResponse().Parse(res);
}

FollowersResponse RoPP::User::GetFollowers(string Sort, int Limit)
{
    json res = Helper::MakeRobloxRequest
    (
        "https://friends.roblox.com/v1/users/" + std::to_string(this->UID) + "/followers?sortOrder=" + Sort + "&limit=" + std::to_string(Limit),
        "GET"
    ).JsonObj;

    return FollowersResponse().Parse(res);
}

FollowingsResponse RoPP::User::GetFollowings(string Sort, int Limit)
{
    json res = Helper::MakeRobloxRequest
    (
        "https://friends.roblox.com/v1/users/" + std::to_string(this->UID) + "/followings?sortOrder=" + Sort + "&limit=" + std::to_string(Limit),
        "GET"
    ).JsonObj;

    return FollowingsResponse().Parse(res);
}

UserGroupsResponse RoPP::User::GetGroups()
{
    json res = Helper::MakeRobloxRequest
    (
        "https://groups.roblox.com/v1/users/" + std::to_string(this->UID) + "/groups/roles",
        "GET"
    ).JsonObj;

    return UserGroupsResponse().Parse(res);
}

int RoPP::User::GetGroupsCount()
{
    json res = Helper::MakeRobloxRequest
    (
        "https://groups.roblox.com/v1/users/" + std::to_string(this->UID) + "/groups/roles",
        "GET"
    ).JsonObj;

    return res["data"].size();
}

UserBadgesResponse RoPP::User::GetBadges()
{
    json res = Helper::MakeRobloxRequest
    (
        "https://badges.roblox.com/v1/users/" + std::to_string(this->UID) + "/badges",
        "GET"
    ).JsonObj;

    return UserBadgesResponse().Parse(res);
}

int RoPP::User::GetBadgesCount()
{
    json res = Helper::MakeRobloxRequest
    (
        "https://badges.roblox.com/v1/users/" + std::to_string(this->UID) + "/badges",
        "GET"
    ).JsonObj;

    return res["data"].size();
}

UserExperienceResponse RoPP::User::GetExperiences(string Sort, int limit)
{
    json res = Helper::MakeRobloxRequest
    (
        "https://games.roblox.com/v2/users/" + std::to_string(this->UID) + "/games?sortOrder=" + Sort + "&limit=" + std::to_string(limit),
        "GET"
    ).JsonObj;

    return UserExperienceResponse().Parse(res);
}

UserFavoriteExperiences RoPP::User::GetFavoriteExperiences(string Sort, int limit)
{
    json res = Helper::MakeRobloxRequest
    (
        "https://games.roblox.com/v2/users/" + std::to_string(this->UID) + "/favorite/games?sortOrder=" + Sort + "&limit=" + std::to_string(limit),
        "GET"
    ).JsonObj;

    return UserFavoriteExperiences().Parse(res);
}

json RoPP::User::GetPresence()
{
    json data = 
    {
        {"userIds", {this->UID}}
    };

    json res = Helper::MakeRobloxRequest
    (
        "https://presence.roblox.com/v1/presence/users",
        "POST",
        data
    ).JsonObj;

    return res;
}

PastUsernames RoPP::User::GetPastUsernames(string Sort, int limit)
{
    json res = Helper::MakeRobloxRequest
    (
        "https://users.roblox.com/v1/users/" + std::to_string(this->UID) + "/username-history?limit=" + std::to_string(limit) + "&sortOrder=" + Sort,
        "GET"
    ).JsonObj;

    return PastUsernames().Parse(res);
}

json RoPP::User::GetPrimaryGroup()
{
    json res = Helper::MakeRobloxRequest
    (
        "https://groups.roblox.com/v1/users/" + std::to_string(this->UID) + "/primary-group",
        "GET"
    ).JsonObj;

    return res;
}

json RoPP::User::GetInventory(string AssetType, string Sort, int Limit)
{
    json res = Helper::MakeRobloxRequest
    (
        "https://inventory.roblox.com/v1/users/" + std::to_string(this->UID) + "/assets/" + AssetType + "?sortOrder=" + Sort + "&limit=" + std::to_string(Limit),
        "GET"
    ).JsonObj;

    return res;
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

json RoPP::User::GetCurrentlyWearing()
{
    return Helper::MakeRobloxRequest
    (
        "https://avatar.roblox.com/v1/users/" + std::to_string(this->UID) + "/currently-wearing",
        "GET"
    ).JsonObj;;
}

json RoPP::User::GetAvatar()
{
    return Helper::MakeRobloxRequest
    (
        "https://avatar.roblox.com/v1/users/" + std::to_string(this->UID) + "/avatar",
        "GET"
    ).JsonObj;;
}