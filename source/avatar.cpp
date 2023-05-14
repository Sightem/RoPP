#include "../include/ropp.h"
#include "../include/helper.h"
#include "../include/responses.h"

std::vector<int64_t> RoPP::Avatar::get_currently_wearing(int64_t user_id)
{
    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://avatar.roblox.com/v1/users/" + std::to_string(user_id) + "/currently-wearing",
        "GET"
    ).JsonObj;

    std::vector<int64_t> AssetIDs;
    for (auto& id : res["assetIds"]) AssetIDs.push_back(id);

    return AssetIDs;
}

Responses::AvatarResponse RoPP::Avatar::get_avatar(int64_t user_id)
{
    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://avatar.roblox.com/v1/users/" + std::to_string(user_id) + "/avatar",
        "GET"
    ).JsonObj;

    return Responses::AvatarResponse(res);
}

Responses::OutfitDetailsResponse RoPP::Avatar::get_outfit_details(int64_t outfit_id)
{
    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://avatar.roblox.com/v1/outfits/" + std::to_string(outfit_id) + "/details",
        "GET"
    ).JsonObj;

    return Responses::OutfitDetailsResponse(res);
}

Responses::GetOutfitsResponse RoPP::Avatar::get_outfits(int64_t user_id, int page, int items_per_page, bool is_editable)
{
    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://avatar.roblox.com/v1/users/" + std::to_string(user_id) + "/outfits?page=" + std::to_string(page) + "&itemsPerPage=" + std::to_string(items_per_page) + "&isEditable=" + std::to_string(is_editable),
        "GET"
    ).JsonObj;

    return Responses::GetOutfitsResponse(res);
}

bool RoPP::Avatar::set_body_colors(json Colors)
{
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://avatar.roblox.com/v1/avatar/set-body-colors",
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED,
        Colors
    ).JsonObj;

    return res["success"];
}

bool RoPP::Avatar::set_body_scales(json scales)
{
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://avatar.roblox.com/v1/avatar/set-scales",
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED,
        scales
    ).JsonObj;

    return res["success"];
}

bool RoPP::Avatar::remove_asset(int64_t asset_id)
{
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://avatar.roblox.com/v1/avatar/assets/" + std::to_string(asset_id) + "/remove",
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED
    ).JsonObj;

    return res["success"];
}

bool RoPP::Avatar::set_player_avatar_type(std::string_view avatar_type)
{
    json data =
    {
        {"playerAvatarType", avatar_type}
    };

    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://avatar.roblox.com/v1/avatar/set-player-avatar-type",
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED,
        data
    ).JsonObj;

    return res["success"];
}

bool RoPP::Avatar::wear_asset(int64_t asset_id)
{
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://avatar.roblox.com/v1/avatar/assets/" + std::to_string(asset_id) + "/wear",
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED
    ).JsonObj;

    return res["success"];
}