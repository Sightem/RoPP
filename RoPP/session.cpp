#include "ropp.h"
#include "../include/helper.h"
#include "../include/request.hpp"
#include <exception>

std::string RoPP::Session::GetCSRF()
{
    Request req("https://auth.roblox.com/v1/authentication-ticket");
    req.set_cookie(".ROBLOSECURITY", this->Cookie);
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.post();

    return res.headers["x-csrf-token"];
}

std::string RoPP::Session::GetAuthTicket()
{
    Request req("https://auth.roblox.com/v1/authentication-ticket");
    req.set_cookie(".ROBLOSECURITY", this->Cookie);
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.post();

    string csrfToken = res.headers["x-csrf-token"];
    req.set_header("x-csrf-token", csrfToken);

    res = req.post();
    string ticket = res.headers["rbx-authentication-ticket"];
    return ticket;
}

long RoPP::Session::GetUserID()
{
    Request req("https://users.roblox.com/v1/users/authenticated");
    req.set_cookie(".ROBLOSECURITY", this->Cookie);
    req.set_header("Referexceptioner", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data)["id"];
}

std::string RoPP::Session::GetUsername()
{
    Request req("https://users.roblox.com/v1/users/authenticated");
    req.set_cookie(".ROBLOSECURITY", this->Cookie);
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data)["name"];
}

void RoPP::Session::SetCookie(std::string cookie)
{
    this->Cookie = cookie;
}

json RoPP::Session::GetBirthDate()
{
    Request req("https://accountinformation.roblox.com/v1/birthdate");
    req.set_cookie(".ROBLOSECURITY", this->Cookie);
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data);
}

std::string RoPP::Session::GetDescription()
{
    Request req("https://accountinformation.roblox.com/v1/description");
    req.set_cookie(".ROBLOSECURITY", this->Cookie);
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data)["description"];
}

json RoPP::Session::GetPhoneInfo()
{
    Request req("https://accountinformation.roblox.com/v1/phone");
    req.set_cookie(".ROBLOSECURITY", this->Cookie);
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data);
}

long RoPP::Session::GetRobuxBalance()
{
    Request req("https://economy.roblox.com/v1/users/" + std::to_string(this->GetUserID()) + "/currency");
    req.set_cookie(".ROBLOSECURITY", this->Cookie);
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data)["robux"];
}

bool RoPP::Session::HasPremium()
{
    Request req("https://premiumfeatures.roblox.com/v1/users/" + std::to_string(this->GetUserID()) + "/validate-membership");
    req.set_cookie(".ROBLOSECURITY", this->Cookie);
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data);
}

int RoPP::Session::GetFriendsCount()
{
    Request req("https://friends.roblox.com/v1/my/friends/count");
    req.set_cookie(".ROBLOSECURITY", this->Cookie);
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data)["count"];
}

json RoPP::Session::GetFriendRequests(string Sort, int Limit)
{
    Request req("https://friends.roblox.com/v1/my/friends/requests?" + Sort + "&limit=" + std::to_string(Limit));
    req.set_cookie(".ROBLOSECURITY", this->Cookie);
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data);
}

bool RoPP::Session::IsFavoriteGame(int PlaceID)
{
    RoPP::Other other;
    int UniverseID = other.GetGameUniverseID(PlaceID);

    Request req("https://games.roblox.com/v1/games/" + std::to_string(UniverseID) + "/favorites");
    req.set_cookie(".ROBLOSECURITY", this->Cookie);
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data)["isFavorited"];
}

void RoPP::Session::SetFavoriteGame(int PlaceID, bool Favorite)
{
    RoPP::Other other;
    int UniverseID = other.GetGameUniverseID(PlaceID);

    json data = 
    {
        {"isFavorited", Favorite}
    };

    json res = Helper::MakeRobloxRequest
        (
            "https://games.roblox.com/v1/games/" + std::to_string(UniverseID) + "/favorites",
            "post",
            this->Cookie,
            data
        ).JsonObj;

    if (res.contains("errors")) 
    {
        json errors = res["errors"];
        json errorObject = errors.at(0);
        throw std::logic_error(errorObject["message"].get<string>().c_str());
    }
}

double RoPP::Session::UnlockPin(int Pin)
{
    json data = 
    {
        {"pin", Pin}
    };

    json res = Helper::MakeRobloxRequest
        (
            "https://auth.roblox.com/v1/account/pin/unlock",
            "post",
            this->Cookie,
            data
        ).JsonObj;

    if (res.contains("errors"))
    {
        json errors = res["errors"];
        json errorObject = errors.at(0);
        throw std::logic_error(errorObject["message"].get<string>().c_str());
    }

    return res["unlockedUntil"]; 
}

bool RoPP::Session::LockPin()
{
    json res = Helper::MakeRobloxRequest
        (
            "https://auth.roblox.com/v1/account/pin/lock",
            "post",
            this->Cookie
        ).JsonObj;

    if (res.contains("errors"))
    {
        json errors = res["errors"];
        json errorObject = errors.at(0);
        throw std::logic_error(errorObject["message"].get<string>().c_str());
    }

    return res["success"];
}

void RoPP::Session::ChangePassword(string OldPassword, string NewPassword)
{
    json data = 
    {
        {"currentPassword", OldPassword},
        {"newPassword", NewPassword}
    };

    Helper::WebResponse res = Helper::MakeRobloxRequest
        (
            "https://auth.roblox.com/v2/user/passwords/change",
            "post",
            this->Cookie,
            data
        );

    if (res.JsonObj.contains("errors"))
    {
        json errors = res.JsonObj["errors"];
        json errorObject = errors.at(0);
        throw std::logic_error(errorObject["message"].get<string>() + std::to_string(res.Res.code));
    }

    if (!res.Res.cookies.empty())
    {
        if (res.Res.cookies.count(".ROBLOSECURITY") == 1)
        {
            this->Cookie = res.Res.cookies[".ROBLOSECURITY"];
        }
    }
}

std::string RoPP::Session::ReadCookie()
{
    return this->Cookie;
}