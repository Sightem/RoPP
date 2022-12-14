#include "../include/ropp.h"
#include "../include/helper.h"
#include "../include/request.hpp"
#include "../include/responses.h"

std::vector<long> RoPP::Avatar::GetCurrentlyWearing(long UserID)
{
    json res = Helper::MakeRobloxRequest
    (
        "https://avatar.roblox.com/v1/users/" + std::to_string(UserID) + "/currently-wearing",
        "GET"
    ).JsonObj;

    std::vector<long> AssetIDs;
    for (auto& id : res["assetIds"]) AssetIDs.push_back(id);

    return AssetIDs;
}

Responses::AvatarResponse RoPP::Avatar::GetAvatar(long UserID)
{
    json res = Helper::MakeRobloxRequest
    (
        "https://avatar.roblox.com/v1/users/" + std::to_string(UserID) + "/avatar",
        "GET"
    ).JsonObj;

    return Responses::AvatarResponse(res);
}

Responses::OutfitDetailsResponse RoPP::Avatar::GetOutfitDetails(long OutfitID)
{
    json res = Helper::MakeRobloxRequest
    (
        "https://avatar.roblox.com/v1/outfits/" + std::to_string(OutfitID) + "/details",
        "GET"
    ).JsonObj;

    return Responses::OutfitDetailsResponse(res);
}

Responses::GetOutfitsResponse RoPP::Avatar::GetOutfits(long UserID, int Page, int ItemsPerPage, bool IsEditable)
{
    json res = Helper::MakeRobloxRequest
    (
        "https://avatar.roblox.com/v1/users/" + std::to_string(UserID) + "/outfits?page=" + std::to_string(Page) + "&itemsPerPage=" + std::to_string(ItemsPerPage) + "&isEditable=" + std::to_string(IsEditable),
        "GET"
    ).JsonObj;

    return Responses::GetOutfitsResponse(res);
}

bool RoPP::Avatar::SetBodyColors(json Colors)
{
    json res = Helper::MakeAuthedRobloxRequest
    (
        "https://avatar.roblox.com/v1/avatar/set-body-colors",
        "POST",
        this->Cookie,
        true,
        Colors
    ).JsonObj;

    return res["success"];
}

bool RoPP::Avatar::SetBodyScales(json Scales)
{
    json res = Helper::MakeAuthedRobloxRequest
    (
        "https://avatar.roblox.com/v1/avatar/set-scales",
        "POST",
        this->Cookie,
        true,
        Scales
    ).JsonObj;

    return res["success"];
}

bool RoPP::Avatar::RemoveAsset(long AssetID)
{
    json res = Helper::MakeAuthedRobloxRequest
    (
        "https://avatar.roblox.com/v1/avatar/assets/" + std::to_string(AssetID) + "/remove",
        "POST",
        this->Cookie,
        true
    ).JsonObj;

    return res["success"];
}

bool RoPP::Avatar::SetPlayerAvatarType(std::string_view AvatarType)
{
    json data =
    {
        {"playerAvatarType", AvatarType}
    };

    json res = Helper::MakeAuthedRobloxRequest
    (
        "https://avatar.roblox.com/v1/avatar/set-player-avatar-type",
        "POST",
        this->Cookie,
        true,
        data
    ).JsonObj;

    return res["success"];
}

bool RoPP::Avatar::WearAsset(long AssetID)
{
    json res = Helper::MakeAuthedRobloxRequest
    (
        "https://avatar.roblox.com/v1/avatar/assets/" + std::to_string(AssetID) + "/wear",
        "POST",
        this->Cookie,
        true
    ).JsonObj;

    return res["success"];
}