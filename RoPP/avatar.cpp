#include "ropp.h"
#include "../include/helper.h"
#include "../include/request.hpp"
#include "../include/responses.h"

Responses::CurrentlyWearing RoPP::Avatar::GetCurrentlyWearing(long UserID)
{
    json res = Helper::MakeRobloxRequest
    (
        "https://avatar.roblox.com/v1/users/" + std::to_string(UserID) + "/currently-wearing",
        "GET"
    ).JsonObj;

    return Responses::CurrentlyWearing().Parse(res);
}

Responses::AvatarResponse RoPP::Avatar::GetAvatar(long UserID)
{
    json res = Helper::MakeRobloxRequest
    (
        "https://avatar.roblox.com/v1/users/" + std::to_string(UserID) + "/avatar",
        "GET"
    ).JsonObj;

    return Responses::AvatarResponse().Parse(res);
}

Responses::OutfitDetailsResponse RoPP::Avatar::GetOutfitDetails(long OutfitID)
{
    json res = Helper::MakeRobloxRequest
    (
        "https://avatar.roblox.com/v1/outfits/" + std::to_string(OutfitID) + "/details",
        "GET"
    ).JsonObj;

    return Responses::OutfitDetailsResponse().Parse(res);
}

Responses::GetOutfitsResponse RoPP::Avatar::GetOutfits(long UserID, int Page, int ItemsPerPage, bool IsEditable)
{
    json res = Helper::MakeRobloxRequest
    (
        "https://avatar.roblox.com/v1/users/" + std::to_string(UserID) + "/outfits?page=" + std::to_string(Page) + "&itemsPerPage=" + std::to_string(ItemsPerPage) + "&isEditable=" + std::to_string(IsEditable),
        "GET"
    ).JsonObj;

    return Responses::GetOutfitsResponse().Parse(res);
}