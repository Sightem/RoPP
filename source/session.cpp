#include "../include/RoPP/ropp.h"
#include "../include/RoPP/responses.h"
#include <cpr/cpr.h>

Responses::BirthdateResponse RoPP::Session::get_birth_date()
{
    cpr::Response r = cpr::Get(
        cpr::Url{ "https://accountinformation.roblox.com/v1/birthdate" },
        cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "x-csrf-token", get_csrf() }, { "User-Agent", USER_AGENT } },
        cpr::Cookies{ {".ROBLOSECURITY", this->m_Cookie} }
    );

    return Responses::BirthdateResponse(nlohmann::json::parse(r.text));
}

std::string RoPP::Session::get_description()
{
    cpr::Response r = cpr::Get(
        cpr::Url{ "https://accountinformation.roblox.com/v1/description" },
        cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "x-csrf-token", get_csrf() }, { "User-Agent", USER_AGENT } },
        cpr::Cookies{ {".ROBLOSECURITY", this->m_Cookie} }
    );


    return nlohmann::json::parse(r.text)["description"];
}

Responses::PhoneInfo RoPP::Session::get_phone_info()
{
    /*
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://accountinformation.roblox.com/v1/phone",
        "GET",
        this->m_Cookie,
        CSRF_REQUIRED
    ).JsonObj;

    return Responses::PhoneInfo(res);
    */

    cpr::Response r = cpr::Get(
		cpr::Url{ "https://accountinformation.roblox.com/v1/phone" },
		cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "x-csrf-token", get_csrf() }, { "User-Agent", USER_AGENT } },
		cpr::Cookies{ {".ROBLOSECURITY", this->m_Cookie} }
	);

    return Responses::PhoneInfo(nlohmann::json::parse(r.text));
}

long RoPP::Session::get_robux_balance()
{
    cpr::Response r = cpr::Get(
        cpr::Url{ "https://economy.roblox.com/v1/users/" + std::to_string(this->get_user_id()) + "/currency" },
		cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "x-csrf-token", get_csrf() }, { "User-Agent", USER_AGENT } },
		cpr::Cookies{ {".ROBLOSECURITY", this->m_Cookie} }
	);

	return nlohmann::json::parse(r.text)["robux"];
}

bool RoPP::Session::has_premium()
{
    cpr::Response r = cpr::Get(
		cpr::Url{ "https://premiumfeatures.roblox.com/v1/users/" + std::to_string(this->get_user_id()) + "/validate-membership" },
        cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "User-Agent", USER_AGENT } },
        cpr::Cookies{ {".ROBLOSECURITY", this->m_Cookie} }
    );

    return nlohmann::json::parse(r.text);
}

int RoPP::Session::get_friends_count()
{
    cpr::Response r = cpr::Get(
        cpr::Url{ "https://friends.roblox.com/v1/my/friends/count" },
		cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "User-Agent", USER_AGENT } },
		cpr::Cookies{ {".ROBLOSECURITY", this->m_Cookie} }
	);

    return nlohmann::json::parse(r.text)["count"];

}

Responses::FriendRequestsResponse RoPP::Session::get_friend_requests(const std::string& sort, int limit)
{
    /*
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://friends.roblox.com/v1/my/friends/requests?" + sort + "&limit=" + std::to_string(limit),
        "GET",
        this->m_Cookie,
        CSRF_REQUIRED
    ).JsonObj;

    return Responses::FriendRequestsResponse(res);
    */

    cpr::Response r = cpr::Get(
		cpr::Url{ "https://friends.roblox.com/v1/my/friends/requests?" + sort + "&limit=" + std::to_string(limit) },
		cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "x-csrf-token", get_csrf() }, { "User-Agent", USER_AGENT } },
		cpr::Cookies{ {".ROBLOSECURITY", this->m_Cookie} }
	);

	return Responses::FriendRequestsResponse(nlohmann::json::parse(r.text));
}

Responses::TransactionTotalsResponse RoPP::Session::get_transaction_totals(const std::string &time_frame)
{
    cpr::Response r = cpr::Get(
    cpr::Url{ "https://economy.roblox.com/v2/users/" + std::to_string(this->get_user_id()) + "/transaction-totals?timeFrame=" + time_frame + "&transactionType=summary" },
		cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "User-Agent", USER_AGENT } },
		cpr::Cookies{ {".ROBLOSECURITY", this->m_Cookie} }
	);

	return Responses::TransactionTotalsResponse(nlohmann::json::parse(r.text));
}

bool RoPP::Session::is_favorite_game(int64_t place_id)
{
    int64_t universe_id = RoPP::Other().get_game_universe_id(place_id);

    /*
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://games.roblox.com/v1/games/" + std::to_string(universe_id) + "/favorites",
        "GET",
        this->m_Cookie,
        CSRF_NOT_REQUIRED
    ).JsonObj;

    return res["isFavorited"];
    */

    cpr::Response r = cpr::Get(
    cpr::Url{ "https://games.roblox.com/v1/games/" + std::to_string(universe_id) + "/favorites" },
		cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "User-Agent", USER_AGENT } },
		cpr::Cookies{ {".ROBLOSECURITY", this->m_Cookie} }
	);

	return nlohmann::json::parse(r.text)["isFavorited"];
}

void RoPP::Session::set_favorite_game(int64_t place_id, bool favorite)
{
    int64_t universe_id = RoPP::Other().get_game_universe_id(place_id);

    json data = 
    {
        {"isFavorited", favorite}
    };
    /*
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://games.roblox.com/v1/games/" + std::to_string(universe_id) + "/favorites",
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED,
        data
    ).JsonObj;
    */

    cpr::Response r = cpr::Post(
    cpr::Url{ "https://games.roblox.com/v1/games/" + std::to_string(universe_id) + "/favorites" },
		cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "x-csrf-token", get_csrf() }, { "User-Agent", USER_AGENT } },
		cpr::Cookies{ {".ROBLOSECURITY", this->m_Cookie} },
		cpr::Body{ data.dump() }
	);
}

double RoPP::Session::unlock_pin(int pin)
{
    json data = 
    {
        {"pin", pin}
    };
    /*

    ordered_json res = Helper::MakeAuthedRobloxRequest
        (
            "https://auth.roblox.com/v1/account/pin/unlock",
            "POST",
            this->m_Cookie,
            CSRF_NOT_REQUIRED,
            data
        ).JsonObj;


    return res["unlockedUntil"]; 
    */
    
    cpr::Response r = cpr::Post(
    cpr::Url{ "https://auth.roblox.com/v1/account/pin/unlock" },
		cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "User-Agent", USER_AGENT } },
		cpr::Cookies{ {".ROBLOSECURITY", this->m_Cookie} },
		cpr::Body{ data.dump() }
	);

	return nlohmann::json::parse(r.text)["unlockedUntil"];


}

bool RoPP::Session::lock_pin()
{
    /*
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://auth.roblox.com/v1/account/pin/lock",
        "POST",
        this->m_Cookie,
        CSRF_NOT_REQUIRED
    ).JsonObj;

    return res["success"];
    */

    cpr::Response r = cpr::Post(
        cpr::Url{ "https://auth.roblox.com/v1/account/pin/lock" },
		cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "User-Agent", USER_AGENT } },
		cpr::Cookies{ {".ROBLOSECURITY", this->m_Cookie} }
	);

	return nlohmann::json::parse(r.text)["success"];

}

void RoPP::Session::change_password(const std::string& old_password, const std::string& new_password)
{
    json data =
    {
        {"currentPassword", old_password},
        {"newPassword", new_password}
    };

    /*
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
    */

    cpr::Response r = cpr::Post(
        cpr::Url{ "https://auth.roblox.com/v2/user/passwords/change" },
        cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "x-csrf-token", get_csrf() }, { "User-Agent", USER_AGENT } },
        cpr::Cookies{ {".ROBLOSECURITY", this->m_Cookie} },
        cpr::Body{ data.dump() }
    );

    std::vector<cpr::Cookie> cookies;
    std::copy(r.cookies.begin(), r.cookies.end(), std::back_inserter(cookies));

    if (!cookies.empty())
    {
        //check if the cookie is in the vector, if it is, set it
        auto it = std::find_if(cookies.begin(), cookies.end(), [](const cpr::Cookie& c) { return c.GetValue() == ".ROBLOSECURITY"; });
        if (it != cookies.end())
        {
            m_Cookie = it->GetValue(); //TODO: look at this again
        }
    }

}


bool RoPP::Session::send_friend_request(int64_t uid)
{
    json data = 
    {
        {"friendshipOriginSourceType", "Unknown"}
    };

    /*
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://friends.roblox.com/v1/users/" + std::to_string(uid) + "/request-friendship",
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED,
        data
    ).JsonObj;

    return res["success"];
    */

    cpr::Response r = cpr::Post(
		cpr::Url{ "https://friends.roblox.com/v1/users/" + std::to_string(uid) + "/request-friendship" },
		cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "x-csrf-token", get_csrf() }, { "User-Agent", USER_AGENT } },
		cpr::Cookies{ {".ROBLOSECURITY", this->m_Cookie} },
		cpr::Body{ data.dump() }
	);

	return nlohmann::json::parse(r.text)["success"];
}

void RoPP::Session::accept_friend_request(int64_t user_id)
{
    /*
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://friends.roblox.com/v1/users/" + std::to_string(user_id) + "/accept-friend-request",
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED
    ).JsonObj;
    */

    cpr::Response r = cpr::Post(
        cpr::Url{ "https://friends.roblox.com/v1/users/" + std::to_string(user_id) + "/accept-friend-request" },
        cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "x-csrf-token", get_csrf() }, { "User-Agent", USER_AGENT } },
        cpr::Cookies{ {".ROBLOSECURITY", this->m_Cookie} }
    );
}

void RoPP::Session::decline_friend_request(int64_t user_id)
{
    /*
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://friends.roblox.com/v1/users/" + std::to_string(user_id) + "/accept-friend-request",
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED
    ).JsonObj;
    */

    cpr::Response r = cpr::Post(
		cpr::Url{ "https://friends.roblox.com/v1/users/" + std::to_string(user_id) + "/decline-friend-request" },
		cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "x-csrf-token", get_csrf() }, { "User-Agent", USER_AGENT } },
		cpr::Cookies{ {".ROBLOSECURITY", this->m_Cookie} }
	);
}

void RoPP::Session::decline_all_friend_requests()
{
    /*
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://friends.roblox.com/v1/user/friend-requests/decline-all",
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED
    ).JsonObj;
    */

    cpr::Response r = cpr::Post(

        cpr::Url{ "https://friends.roblox.com/v1/user/friend-requests/decline-all" },
        cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "x-csrf-token", get_csrf() }, { "User-Agent", USER_AGENT } },
        cpr::Cookies{ {".ROBLOSECURITY", this->m_Cookie} }
	);
}

void RoPP::Session::block_user(int64_t user_id)
{
    cpr::Response r = cpr::Post(
        cpr::Url{ "https://accountsettings.roblox.com/v1/users/" + std::to_string(user_id) + "/block" },
		cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "User-Agent", USER_AGENT } },
		cpr::Cookies{ {".ROBLOSECURITY", this->m_Cookie} }
    );
}

void RoPP::Session::unblock_user(int64_t user_id)
{
    cpr::Response r = cpr::Post(
        cpr::Url{ "https://accountsettings.roblox.com/v1/users/" + std::to_string(user_id) + "/unblock" },
        cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "User-Agent", USER_AGENT } },
        cpr::Cookies{ {".ROBLOSECURITY", this->m_Cookie} }
    );
}

void RoPP::Session::set_description(const std::string& description)
{
    json data = 
    {
        {"description", description}
    };

    cpr::Response r = cpr::Post(
        cpr::Url{ "https://accountinformation.roblox.com/v1/description" },
        cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "x-csrf-token", get_csrf() }, { "User-Agent", USER_AGENT } },
        cpr::Cookies{ {".ROBLOSECURITY", this->m_Cookie} },
        cpr::Body{ data.dump() }
    );
}

void RoPP::Session::set_gender(const std::string& gender)
{
    json data = 
    {
        {"gender", gender}
    };

    /*
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://accountinformation.roblox.com/v1/gender",
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED,
        data
    ).JsonObj;
    */

    cpr::Response r = cpr::Post(
        cpr::Url {"https://accountinformation.roblox.com/v1/gender"},
        cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "x-csrf-token", get_csrf() }, { "User-Agent", USER_AGENT } },
        cpr::Cookies{ {".ROBLOSECURITY", this->m_Cookie} },
        cpr::Body{ data.dump() }
    );
}

void RoPP::Session::set_displayname(const std::string &displayname)
{
    json data = 
    {
        {"newDisplayName", displayname}
    };

    /*
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://users.roblox.com/v1/users/" + std::to_string(this->get_user_id()) + "/display-names",
        "PATCH",
        this->m_Cookie,
        CSRF_REQUIRED,
        data
    ).JsonObj;    
    */

    cpr::Response r = cpr::Patch(
		cpr::Url{ "https://users.roblox.com/v1/users/" + std::to_string(this->get_user_id()) + "/display-names" },
		cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "x-csrf-token", get_csrf() }, { "User-Agent", USER_AGENT } },
		cpr::Cookies{ {".ROBLOSECURITY", this->m_Cookie} },
		cpr::Body{ data.dump() }
	);
}

std::vector<Responses::FriendsOnline> RoPP::Session::get_friends_online()
{
    /*
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
    */

    cpr::Response r = cpr::Get(
		cpr::Url{ "https://friends.roblox.com/v1/users/" + std::to_string(this->get_user_id()) + "/friends/online" },
		cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "x-csrf-token", get_csrf() }, {"User-Agent", USER_AGENT} },
		cpr::Cookies{ {".ROBLOSECURITY", this->m_Cookie} }
	);

    std::vector<Responses::FriendsOnline> Friends;
    json res = json::parse(r.text);
    for (size_t i = 0; i < res["data"].size(); i++)
    {
		Friends.push_back(Responses::FriendsOnline(res["data"][i]));
	}

	return Friends;
}

Responses::ShorthandUser RoPP::Session::get_user()
{
    cpr::Response r = cpr::Get(
        cpr::Url{ "https://users.roblox.com/v1/users/" + std::to_string(this->get_user_id()) },
		cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, {"User-Agent", USER_AGENT} },
		cpr::Cookies{ {".ROBLOSECURITY", this->m_Cookie} }
	);

    return Responses::ShorthandUser(json::parse(r.text));
}

int64_t RoPP::Session::get_user_id()
{
    cpr::Response r = cpr::Get(
        cpr::Url{ "https://users.roblox.com/v1/users/authenticated" },
        cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "x-csrf-token", this->get_csrf() }, {"User-Agent", USER_AGENT} },
        cpr::Cookies{ {".ROBLOSECURITY", this->m_Cookie} }
    );

    return nlohmann::json::parse(r.text)["id"];
}