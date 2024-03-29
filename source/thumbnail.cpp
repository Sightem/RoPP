#include "../include/RoPP/ropp.h"
#include "../include/RoPP/responses.h"
#include <cpr/cpr.h>


std::vector<Responses::Thumbnail> RoPP::Thumbnail::get_assets_thumbnails(const std::vector<int64_t> &asset_ids, const std::string &size, const std::string &format, bool is_circular)
{
    std::string url;

    std::string asset_ids_str = "";
    for (size_t i = 0; i < asset_ids.size(); i++)
    {
        asset_ids_str += std::to_string(asset_ids[i]);
        if (i != asset_ids.size() - 1)
        {
            asset_ids_str += ",";
        }
    }

    url = "https://thumbnails.roblox.com/v1/assets?assetIds=" + asset_ids_str + "&size=" + size + "&format=" + format + "&isCircular=" + (is_circular ? "true" : "false");

    cpr::Response r = cpr::Get(cpr::Url{ url });
    nlohmann::json res = nlohmann::json::parse(r.text);

    std::vector<Responses::Thumbnail> thumbnails;
    for (size_t i = 0; i < res["data"].size(); i++)
    {
		thumbnails.push_back(Responses::Thumbnail(res["data"][i]));
	}

    return thumbnails;       
}
Responses::Thumbnail RoPP::Thumbnail::get_asset_thumbnail_3d(int64_t asset_id)
{
    cpr::Response r = cpr::Get(cpr::Url{ "https://thumbnails.roblox.com/v1/assets-thumbnail-3d?assetId=" + std::to_string(asset_id) });
    nlohmann::json res = nlohmann::json::parse(r.text);

    return Responses::Thumbnail(res["data"]);
}
std::vector<Responses::Thumbnail> RoPP::Thumbnail::get_badges_thumbnails(const std::vector<int64_t> &badge_ids, const std::string &size, const std::string &format, bool is_circular)
{
    std::string url;

    std::string badge_ids_str = "";
    for (size_t i = 0; i < badge_ids.size(); i++)
    {
        badge_ids_str += std::to_string(badge_ids[i]);
        if (i != badge_ids.size() - 1)
        {
            badge_ids_str += ",";
        }
    }

    url = "https://thumbnails.roblox.com/v1/badges/icons?badgeIds=" + badge_ids_str + "&size=" + size + "&format=" + format + "&isCircular=" + (is_circular ? "true" : "false");

    cpr::Response r = cpr::Get(cpr::Url{ url });
    nlohmann::json res = nlohmann::json::parse(r.text);

    std::vector<Responses::Thumbnail> thumbnails;
    for (size_t i = 0; i < res["data"].size(); i++)
    {
        thumbnails.push_back(Responses::Thumbnail(res["data"][i]));
    }

    return thumbnails;
}
std::vector<Responses::Thumbnail> RoPP::Thumbnail::get_bundles_thumbnails(const std::vector<int64_t> &bundle_ids, const std::string &size, const std::string &format, bool is_circular)
{
    std::string url;

    std::string bundle_ids_str = "";
    for (size_t i = 0; i < bundle_ids.size(); i++)
    {
        bundle_ids_str += std::to_string(bundle_ids[i]);
        if (i != bundle_ids.size() - 1)
        {
            bundle_ids_str += ",";
        }
    }

    url = "https://thumbnails.roblox.com/v1/bundles/thumbnails?bundleIds=" + bundle_ids_str + "&size=" + size + "&format=" + format + "&isCircular=" + (is_circular ? "true" : "false");

    cpr::Response r = cpr::Get(cpr::Url{ url });
    nlohmann::json res = nlohmann::json::parse(r.text);

    std::vector<Responses::Thumbnail> thumbnails;
    for (size_t i = 0; i < res["data"].size(); i++)
    {
        thumbnails.push_back(Responses::Thumbnail(res["data"][i]));
    }

    return thumbnails;
}
std::vector<Responses::Thumbnail> RoPP::Thumbnail::get_gamepasses_thumbails(const std::vector<int64_t> &gamepass_ids, const std::string &size, const std::string &format, bool is_circular)
{
    std::string url;

    std::string gamepass_ids_str = "";
    for (size_t i = 0; i < gamepass_ids.size(); i++)
    {
        gamepass_ids_str += std::to_string(gamepass_ids[i]);
        if (i != gamepass_ids.size() - 1)
        {
            gamepass_ids_str += ",";
        }
    }

    url = "https://thumbnails.roblox.com/v1/game-passes?gamePassIds=" + gamepass_ids_str + "&size=" + size + "&format=" + format + "&isCircular=" + (is_circular ? "true" : "false");

    cpr::Response r = cpr::Get(cpr::Url{ url });
    nlohmann::json res = nlohmann::json::parse(r.text);

    std::vector<Responses::Thumbnail> thumbnails;
    for (size_t i = 0; i < res["data"].size(); i++)
    {
        thumbnails.push_back(Responses::Thumbnail(res["data"][i]));
    }

    return thumbnails;
}
std::vector<Responses::Thumbnail> RoPP::Thumbnail::get_games_icons(const std::vector<int64_t> &place_ids, const std::string &return_policy, const std::string &size, const std::string &format, bool is_circular)
{
    std::string url;

    std::string place_ids_str = "";
    for (size_t i = 0; i < place_ids.size(); i++)
    {
        place_ids_str += std::to_string(place_ids[i]);
        if (i != place_ids.size() - 1)
        {
            place_ids_str += ",";
        }
    }

    url = "https://thumbnails.roblox.com/v1/places/gameicons?placeIds=" + place_ids_str + "&returnPolicy=" + return_policy + "&size=" + size + "&format=" + format + "&isCircular=" + (is_circular ? "true" : "false");

    cpr::Response r = cpr::Get(cpr::Url{ url });
    nlohmann::json res = nlohmann::json::parse(r.text);

    std::vector<Responses::Thumbnail> thumbnails;
    for (size_t i = 0; i < res["data"].size(); i++)
    {
        thumbnails.push_back(Responses::Thumbnail(res["data"][i]));
    }

    return thumbnails;
}

std::vector<Responses::Thumbnail> RoPP::Thumbnail::get_groups_emblems(const std::vector<int64_t> &group_ids, const std::string &size, const std::string &format, bool is_circular)
{
    std::string url;

    std::string group_ids_str = "";
    for (size_t i = 0; i < group_ids.size(); i++)
    {
        group_ids_str += std::to_string(group_ids[i]);
        if (i != group_ids.size() - 1)
        {
            group_ids_str += ",";
        }
    }

    url = "https://thumbnails.roblox.com/v1/groups/icons?groupIds=" + group_ids_str + "&size=" + size + "&format=" + format + "&isCircular=" + (is_circular ? "true" : "false");

    cpr::Response r = cpr::Get(cpr::Url{ url });
    nlohmann::json res = nlohmann::json::parse(r.text);

    std::vector<Responses::Thumbnail> thumbnails;
    for (size_t i = 0; i < res["data"].size(); i++)
    {
        thumbnails.push_back(Responses::Thumbnail(res["data"][i]));
    }

    return thumbnails;
}

std::vector<Responses::Thumbnail> RoPP::Thumbnail::get_avatar_headshots(const std::vector<int64_t> &user_ids, const std::string &size, const std::string &format, bool is_circular)
{
    std::string url;

    std::string user_ids_str = "";
    for (size_t i = 0; i < user_ids.size(); i++)
    {
        user_ids_str += std::to_string(user_ids[i]);
        if (i != user_ids.size() - 1)
        {
            user_ids_str += ",";
        }
    }

    url = "https://thumbnails.roblox.com/v1/users/avatar-headshot?userIds=" + user_ids_str + "&size=" + size + "&format=" + format + "&isCircular=" + (is_circular ? "true" : "false");

    cpr::Response r = cpr::Get(cpr::Url{ url });
    nlohmann::json res = nlohmann::json::parse(r.text);

    std::vector<Responses::Thumbnail> thumbnails;
    for (size_t i = 0; i < res["data"].size(); i++)
    {
        thumbnails.push_back(Responses::Thumbnail(res["data"][i]));
    }

    return thumbnails;
}