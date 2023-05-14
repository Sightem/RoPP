#include "../include/request.hpp"
#include "../include/ropp.h"
#include "../include/responses.h"

std::vector<Responses::ThumbnailBase> RoPP::Thumbnail::get_avatar_headshots(const std::vector<int64_t>& user_ids, const std::string& size, const std::string& format, bool is_circular)
{
    //https://thumbnails.roblox.com/v1/users/avatar-headshot?userIds=2057697144,87844870&size=48x48&format=Png&isCircular=false
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

    ordered_json res = Helper::MakeRobloxRequest
    (
        url,
        "GET"
    ).JsonObj;

    std::vector<Responses::ThumbnailBase> thumbnails;
    for (size_t i = 0; i < res["data"].size(); i++)
    {
        thumbnails.push_back(Responses::ThumbnailBase(res["data"][i]));
    }

    return thumbnails;
}