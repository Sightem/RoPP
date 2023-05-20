#include "../include/ropp.h"
#include "../include/helper.h"
#include "../include/request.hpp"
#include "../include/responses.h"

Responses::BirthdateResponse RoPP::Session::get_birth_date()
{
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://accountinformation.roblox.com/v1/birthdate",
        "GET",
        this->m_Cookie,
        CSRF_REQUIRED
    ).JsonObj;

    return Responses::BirthdateResponse(res);
}

std::string RoPP::Session::get_description()
{
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://accountinformation.roblox.com/v1/description",
        "GET",
        this->m_Cookie,
        CSRF_REQUIRED
    ).JsonObj;

    return res["description"];
}

Responses::PhoneInfo RoPP::Session::get_phone_info()
{
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://accountinformation.roblox.com/v1/phone",
        "GET",
        this->m_Cookie,
        CSRF_REQUIRED
    ).JsonObj;

    return Responses::PhoneInfo(res);
}

long RoPP::Session::get_robux_balance()
{
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://economy.roblox.com/v1/users/" + std::to_string(this->get_user_id()) + "/currency",
        "GET",
        this->m_Cookie,
        CSRF_REQUIRED
    ).JsonObj;

    return res["robux"];
}

bool RoPP::Session::has_premium()
{
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://premiumfeatures.roblox.com/v1/users/" + std::to_string(this->get_user_id()) + "/validate-membership",
        "GET",
        this->m_Cookie,
        CSRF_NOT_REQUIRED
    ).JsonObj;

    return res;
}

int RoPP::Session::get_friends_count()
{
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://friends.roblox.com/v1/my/friends/count",
        "GET",
        this->m_Cookie,
        CSRF_NOT_REQUIRED
    ).JsonObj;

    return res["count"];
}

Responses::FriendRequestsResponse RoPP::Session::get_friend_requests(const std::string& sort, int limit)
{
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://friends.roblox.com/v1/my/friends/requests?" + sort + "&limit=" + std::to_string(limit),
        "GET",
        this->m_Cookie,
        CSRF_REQUIRED
    ).JsonObj;

    return Responses::FriendRequestsResponse(res);
}

bool RoPP::Session::is_favorite_game(int64_t place_id)
{
    int64_t universe_id = RoPP::Other().get_game_universe_id(place_id);

    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://games.roblox.com/v1/games/" + std::to_string(universe_id) + "/favorites",
        "GET",
        this->m_Cookie,
        CSRF_NOT_REQUIRED
    ).JsonObj;

    return res["isFavorited"];
}

void RoPP::Session::set_favorite_game(int64_t place_id, bool favorite)
{
    int64_t universe_id = RoPP::Other().get_game_universe_id(place_id);

    json data = 
    {
        {"isFavorited", favorite}
    };

    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://games.roblox.com/v1/games/" + std::to_string(universe_id) + "/favorites",
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED,
        data
    ).JsonObj;
}

double RoPP::Session::unlock_pin(int pin)
{
    json data = 
    {
        {"pin", pin}
    };

    ordered_json res = Helper::MakeAuthedRobloxRequest
        (
            "https://auth.roblox.com/v1/account/pin/unlock",
            "POST",
            this->m_Cookie,
            CSRF_NOT_REQUIRED,
            data
        ).JsonObj;


    return res["unlockedUntil"]; 
}

bool RoPP::Session::lock_pin()
{
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://auth.roblox.com/v1/account/pin/lock",
        "POST",
        this->m_Cookie,
        CSRF_NOT_REQUIRED
    ).JsonObj;

    return res["success"];
}

void RoPP::Session::change_password(const std::string& old_password, const std::string& new_password)
{
    json data = 
    {
        {"currentPassword", old_password},
        {"newPassword", new_password}
    };

    Helper::WebResponse res = Helper::MakeAuthedRobloxRequest
    (
        "https://auth.roblox.com/v2/user/passwords/change",
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED,
        data
    );

    if (!res.Res.cookies.empty())
    {
        if (res.Res.cookies.count(".ROBLOSECURITY") == 1)
        {
            this->m_Cookie = res.Res.cookies[".ROBLOSECURITY"];
        }
    }
}

bool RoPP::Session::send_friend_request(int64_t uid)
{
    json data = 
    {
        {"friendshipOriginSourceType", "Unknown"}
    };

    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://friends.roblox.com/v1/users/" + std::to_string(uid) + "/request-friendship",
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED,
        data
    ).JsonObj;

    return res["success"];
}

void RoPP::Session::accept_friend_request(int64_t user_id)
{
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://friends.roblox.com/v1/users/" + std::to_string(user_id) + "/accept-friend-request",
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED
    ).JsonObj;
}

void RoPP::Session::decline_friend_request(int64_t user_id)
{
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://friends.roblox.com/v1/users/" + std::to_string(user_id) + "/accept-friend-request",
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED
    ).JsonObj;
}

void RoPP::Session::decline_all_friend_requests()
{
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://friends.roblox.com/v1/user/friend-requests/decline-all",
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED
    ).JsonObj;
}

void RoPP::Session::block_user(int64_t user_id)
{
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://accountsettings.roblox.com/v1/users/" + std::to_string(user_id) + "/block",
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED
    ).JsonObj;
}

void RoPP::Session::unblock_user(int64_t user_id)
{
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://accountsettings.roblox.com/v1/users/" + std::to_string(user_id) + "/unblock",
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED
    ).JsonObj;
}

void RoPP::Session::set_description(const std::string& description)
{
    json data = 
    {
        {"description", description}
    };

    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://accountinformation.roblox.com/v1/description",
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED,
        data
    ).JsonObj;
}

void RoPP::Session::set_gender(std::string gender)
{
    json data = 
    {
        {"gender", gender}
    };

    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://accountinformation.roblox.com/v1/gender",
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED,
        data
    ).JsonObj;
}

void RoPP::Session::set_displayname(const std::string &displayname)
{
    json data = 
    {
        {"newDisplayName", displayname}
    };

    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://users.roblox.com/v1/users/" + std::to_string(this->get_user_id()) + "/display-names",
        "PATCH",
        this->m_Cookie,
        CSRF_REQUIRED,
        data
    ).JsonObj;    
}

std::vector<Responses::FriendsOnline> RoPP::Session::get_friends_online()
{
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://friends.roblox.com/v1/users/" + std::to_string(this->get_user_id()) + "/friends/online",
        "GET",
        this->m_Cookie,
        CSRF_REQUIRED
    ).JsonObj;

    std::vector<Responses::FriendsOnline> Friends;
    for (size_t i = 0; i < res["data"].size(); i++)
    {
        Friends.push_back(Responses::FriendsOnline(res["data"][i]));
    }

    return Friends;
}

Responses::User RoPP::Session::get_user()
{
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://users.roblox.com/v1/users/" + std::to_string(this->get_user_id()),
        "GET",
        this->m_Cookie,
        CSRF_REQUIRED
    ).JsonObj;

    return Responses::User(res);
}

int64_t RoPP::Session::get_user_id()
{
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://users.roblox.com/v1/users/authenticated",
        "GET",
        this->m_Cookie,
        CSRF_REQUIRED
    ).JsonObj;
    
    return res["id"];
}