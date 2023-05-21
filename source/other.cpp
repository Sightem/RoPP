#include "../include/ropp.h"
#include "../include/helper.h"
#include "../include/request.hpp"
#include "ropp.h"


std::vector<Responses::SearchedUser> RoPP::Other::user_search(std::string keyword, int32_t limit)
{
    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://users.roblox.com/v1/users/search?keyword=" + keyword + "&limit=" + std::to_string(limit),
        "GET"
    ).JsonObj;

    std::vector<Responses::SearchedUser> users;
    for (size_t i = 0; i < res["data"].size(); i++)
    {
        users.push_back(Responses::SearchedUser(res["data"][i]));
    }

    return users;
}

json RoPP::Other::group_search(std::string keyword, bool prioritize_exact_match, int32_t limit)
{
    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://groups.roblox.com/v1/groups/search?keyword=" + keyword + "&prioritizeExactMatch=" + std::to_string(prioritize_exact_match) + "&limit=" + std::to_string(limit),
        "GET"
    ).JsonObj;

    return res;
}

std::string RoPP::Other::validate_username(const std::string& username)
{
    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://auth.roblox.com/v2/usernames/validate?request.username=" + username + "&request.birthday=1970-10-10",
        "GET"
    ).JsonObj;

    return res["message"];
}

void RoPP::Other::validate_display_name(const std::string &display_name)
{
    int64_t user_id = this->get_uid_from_cookie(this->m_Cookie);

    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://users.roblox.com/v1/users/" + std::to_string(user_id) + "/display-names/validate?displayName=" + display_name,
        "GET",
        this->m_Cookie,
        CSRF_NOT_REQUIRED
    ).JsonObj;
}

int64_t RoPP::Other::get_game_universe_id(int64_t place_id)
{
    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://apis.roblox.com/universes/v1/places/" + std::to_string(place_id) + "/universe",
        "GET"
    ).JsonObj;

    return res["universeId"];
}

std::vector<Responses::UserPresence> RoPP::Other::get_users_presence(const std::vector<int64_t>& user_ids)
{
    json data = 
    {
        {"userIds", user_ids}
    };

    json res;
    
    if (!this->m_Cookie.empty())
    {
        res = Helper::MakeAuthedRobloxRequest
        (
            "https://presence.roblox.com/v1/presence/users",
            "POST",
            this->m_Cookie,
            CSRF_REQUIRED,
            data
        ).JsonObj;
    } else
    {
        res = Helper::MakeRobloxRequest
        (
            "https://presence.roblox.com/v1/presence/users",
            "POST",
            data
        ).JsonObj;
    }

    std::vector<Responses::UserPresence> presences;
    for (size_t i = 0; i < res["userPresences"].size(); i++)
    {
        presences.push_back(Responses::UserPresence(res["userPresences"][i]));
    }

    return presences;
}

int64_t RoPP::Other::get_uid_from_cookie(const std::string& cookie)
{
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://users.roblox.com/v1/users/authenticated",
        "GET",
        cookie,
        CSRF_NOT_REQUIRED
    ).JsonObj;

    return res["id"];
}

int64_t RoPP::Other::get_user_id_from_username(const std::string &username)
{
    json data =
    {
        {"usernames", {username}},
        {"excludeBannedUsers", true}
    };

    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://users.roblox.com/v1/usernames/users",
        "POST",
        data
    ).JsonObj;

    return res["data"][0]["id"];
}

std::string RoPP::Other::get_username_from_cookie(const std::string &cookie)
{
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://users.roblox.com/v1/users/authenticated",
        "GET",
        cookie,
        CSRF_NOT_REQUIRED
    ).JsonObj;

    return res["name"];
}

Responses::GamePassProductInfoResponse RoPP::Other::get_gamepass_product_info(int64_t gamepass_id)
{
    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://economy.roblox.com/v1/game-pass/" + std::to_string(gamepass_id) + "/game-pass-product-info",
        "GET"
    ).JsonObj;

    return Responses::GamePassProductInfoResponse(res);
}

void RoPP::Other::buy_gamepass(int64_t gamepass_id)
{
    Responses::GamePassProductInfoResponse info = this->get_gamepass_product_info(gamepass_id);

    Helper::MakeAuthedRobloxRequest
    (
        "https://economy.roblox.com/v1/purchases/products/" + std::to_string(info.product_id),
        "OPTIONS",
        this->m_Cookie,
        CSRF_REQUIRED
    );
}