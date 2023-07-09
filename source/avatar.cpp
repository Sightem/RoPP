#include "../include/RoPP/ropp.h"
#include "../include/RoPP/responses.h"
#include <cpr/cpr.h>

std::vector<int64_t> RoPP::Avatar::get_currently_wearing(int64_t user_id)
{
    /*
    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://avatar.roblox.com/v1/users/" + std::to_string(user_id) + "/currently-wearing",
        "GET"
    ).JsonObj;

    std::vector<int64_t> AssetIDs;
    for (auto& id : res["assetIds"]) AssetIDs.push_back(id);

    return AssetIDs;
    */

    cpr::Response r = cpr::Get
    (
		cpr::Url{ "https://avatar.roblox.com/v1/users/" + std::to_string(user_id) + "/currently-wearing" },
        cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "User-Agent", USER_AGENT } }
	);
    nlohmann::json res = nlohmann::json::parse(r.text);

    std::vector<int64_t> AssetIDs;
    for (auto& id : res["assetIds"]) AssetIDs.push_back(id);

    return AssetIDs;
}

Responses::AvatarResponse RoPP::Avatar::get_avatar(int64_t user_id)
{
    /*
    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://avatar.roblox.com/v1/users/" + std::to_string(user_id) + "/avatar",
        "GET"
    ).JsonObj;

    return Responses::AvatarResponse(res);
    */

    cpr::Response r = cpr::Get(
        cpr::Url{ "https://avatar.roblox.com/v1/users/" + std::to_string(user_id) + "/avatar" },
		cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "User-Agent", USER_AGENT } }
	);
    
    return Responses::AvatarResponse(nlohmann::json::parse(r.text));
}

Responses::OutfitDetailsResponse RoPP::Avatar::get_outfit_details(int64_t outfit_id)
{
    /*
    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://avatar.roblox.com/v1/outfits/" + std::to_string(outfit_id) + "/details",
        "GET"
    ).JsonObj;

    return Responses::OutfitDetailsResponse(res);
    */

    cpr::Response r = cpr::Get(
        cpr::Url{ "https://avatar.roblox.com/v1/outfits/" + std::to_string(outfit_id) + "/details" },
        cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "User-Agent", USER_AGENT } }
    );

    return Responses::OutfitDetailsResponse(nlohmann::json::parse(r.text));
}

Responses::GetOutfitsResponse RoPP::Avatar::get_outfits(int64_t user_id, int page, int items_per_page, bool is_editable)
{
    /*
    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://avatar.roblox.com/v1/users/" + std::to_string(user_id) + "/outfits?page=" + std::to_string(page) + "&itemsPerPage=" + std::to_string(items_per_page) + "&isEditable=" + std::to_string(is_editable),
        "GET"
    ).JsonObj;

    return Responses::GetOutfitsResponse(res);
    */

    cpr::Response r = cpr::Get(
		cpr::Url{ "https://avatar.roblox.com/v1/users/" + std::to_string(user_id) + "/outfits?page=" + std::to_string(page) + "&itemsPerPage=" + std::to_string(items_per_page) + "&isEditable=" + std::to_string(is_editable) },
		cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "User-Agent", USER_AGENT } }
	);

    return Responses::GetOutfitsResponse(nlohmann::json::parse(r.text));
}


bool RoPP::Avatar::set_body_colors(json Colors) //TODO: look at this
{
    /*
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://avatar.roblox.com/v1/avatar/set-body-colors",
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED,
        Colors
    ).JsonObj;


    return res["success"];
    */

    cpr::Response r = cpr::Post(
		cpr::Url{ "https://avatar.roblox.com/v1/avatar/set-body-colors" },
        cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "x-csrf-token", get_csrf() }, { "User-Agent", USER_AGENT } },
        cpr::Cookies{ {".ROBLOSECURITY", this->m_Cookie} }
    );

    nlohmann::json res = nlohmann::json::parse(r.text);

    return res["success"];
}

bool RoPP::Avatar::set_body_scales(json scales)
{
    /*
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://avatar.roblox.com/v1/avatar/set-scales",
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED,
        scales
    ).JsonObj;

    return res["success"];
*/

    cpr::Response r = cpr::Post(
		cpr::Url{ "https://avatar.roblox.com/v1/avatar/set-scales" },
		cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "x-csrf-token", get_csrf() }, { "User-Agent", USER_AGENT } },
		cpr::Cookies{ {".ROBLOSECURITY", this->m_Cookie} }
	);

	nlohmann::json res = nlohmann::json::parse(r.text);

	return res["success"];
}

bool RoPP::Avatar::remove_asset(int64_t asset_id)
{
    /*
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://avatar.roblox.com/v1/avatar/assets/" + std::to_string(asset_id) + "/remove",
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED
    ).JsonObj;

    return res["success"];
    */

    cpr::Response r = cpr::Post(
        cpr::Url{ "https://avatar.roblox.com/v1/avatar/assets/" + std::to_string(asset_id) + "/remove" },
        cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "x-csrf-token", get_csrf() }, { "User-Agent", USER_AGENT } },
        cpr::Cookies{ {".ROBLOSECURITY", this->m_Cookie} }
    );

    nlohmann::json res = nlohmann::json::parse(r.text);

    return res["success"];
}

bool RoPP::Avatar::set_player_avatar_type(const std::string& avatar_type)
{
    json data =
    {
        {"playerAvatarType", avatar_type}
    };

    /*
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://avatar.roblox.com/v1/avatar/set-player-avatar-type",
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED,
        data
    ).JsonObj;

    return res["success"];
    */

    cpr::Response r = cpr::Post(
		cpr::Url{ "https://avatar.roblox.com/v1/avatar/set-player-avatar-type" },
		cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "x-csrf-token", get_csrf() }, { "User-Agent", USER_AGENT } },
		cpr::Cookies{ {".ROBLOSECURITY", this->m_Cookie} }
	);
    nlohmann::json res = nlohmann::json::parse(r.text);

    return res["success"];
}

bool RoPP::Avatar::wear_asset(int64_t asset_id)
{
    /*
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://avatar.roblox.com/v1/avatar/assets/" + std::to_string(asset_id) + "/wear",
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED
    ).JsonObj;

    return res["success"];
    */

    cpr::Response r = cpr::Post(

        cpr::Url{ "https://avatar.roblox.com/v1/avatar/assets/" + std::to_string(asset_id) + "/wear" },
		cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "x-csrf-token", get_csrf() }, { "User-Agent", USER_AGENT } },
		cpr::Cookies{ {".ROBLOSECURITY", this->m_Cookie} }
	);
    nlohmann::json res = nlohmann::json::parse(r.text);

	return res["success"];
}