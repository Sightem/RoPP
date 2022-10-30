#include "ropp.h"
#include "../include/helper.h"
#include "../include/request.hpp"

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

    std::string csrfToken = res.headers["x-csrf-token"];
    req.set_header("x-csrf-token", csrfToken);

    res = req.post();
    std::string ticket = res.headers["rbx-authentication-ticket"];
    return ticket;
}

long RoPP::Session::GetUserID()
{
    //example of how to use the helper function to convert old code to new
   json res = Helper::MakeRobloxRequest
    (
        "https://users.roblox.com/v1/users/authenticated",
        "get",
        this->Cookie
    ).JsonObj;

    return res["id"];
}

std::string RoPP::Session::GetUsername()
{
    json res = Helper::MakeRobloxRequest
    (
        "https://users.roblox.com/v1/users/authenticated",
        "get",
        this->Cookie
    ).JsonObj;

    return res["name"];
}

void RoPP::Session::SetCookie(std::string cookie)
{
    this->Cookie = cookie;
}

json RoPP::Session::GetBirthDate()
{
    json res = Helper::MakeRobloxRequest
    (
        "https://accountinformation.roblox.com/v1/birthdate",
        "get",
        this->Cookie
    ).JsonObj;

    return res;
}

std::string RoPP::Session::GetDescription()
{
    json res = Helper::MakeRobloxRequest
    (
        "https://accountinformation.roblox.com/v1/description",
        "get",
        this->Cookie
    ).JsonObj;

    return res["description"];
}

json RoPP::Session::GetPhoneInfo()
{
    json res = Helper::MakeRobloxRequest
    (
        "https://accountinformation.roblox.com/v1/phone",
        "get",
        this->Cookie
    ).JsonObj;

    return res;
}

long RoPP::Session::GetRobuxBalance()
{
    json res = Helper::MakeRobloxRequest
    (
        "https://economy.roblox.com/v1/users/" + std::to_string(this->GetUserID()) + "/currency",
        "get",
        this->Cookie
    ).JsonObj;

    return res["robux"];
}

bool RoPP::Session::HasPremium()
{
    json res = Helper::MakeRobloxRequest
    (
        "https://premiumfeatures.roblox.com/v1/users/" + std::to_string(this->GetUserID()) + "/validate-membership",
        "get",
        this->Cookie
    ).JsonObj;

    return res;
}

int RoPP::Session::GetFriendsCount()
{
    json res = Helper::MakeRobloxRequest
    (
        "https://friends.roblox.com/v1/my/friends/count",
        "GET",
        this->Cookie
    ).JsonObj;

    return res["count"];
}

json RoPP::Session::GetFriendRequests(string Sort, int Limit)
{
    json res = Helper::MakeRobloxRequest
    (
        "https://friends.roblox.com/v1/my/friends/requests?" + Sort + "&limit=" + std::to_string(Limit),
        "GET",
        this->Cookie
    ).JsonObj;

    return res;
}

bool RoPP::Session::IsFavoriteGame(int PlaceID)
{
    RoPP::Other other;
    int UniverseID = other.GetGameUniverseID(PlaceID);

   json res = Helper::MakeRobloxRequest
    (
        "https://games.roblox.com/v1/games/" + std::to_string(UniverseID) + "/favorites",
        "GET",
        this->Cookie
    ).JsonObj;

    return res["isFavorited"];
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

bool RoPP::Session::SendFriendRequest(long UID)
{
    json data = 
    {
        {"friendshipOriginSourceType", "Unknown"}
    };

    json res = Helper::MakeRobloxRequest
        (
            "https://friends.roblox.com/v1/users/" + std::to_string(UID) + "/request-friendship",
            "post",
            this->Cookie,
            data
        ).JsonObj;

    return res["success"];
}

void RoPP::Session::AcceptFriendRequest(long UID)
{
    json res = Helper::MakeRobloxRequest
        (
            "https://friends.roblox.com/v1/users/" + std::to_string(UID) + "/accept-friendship-request",
            "post",
            this->Cookie
        ).JsonObj;
}

void RoPP::Session::DeclineFriendRequest(long UID)
{
    json res = Helper::MakeRobloxRequest
        (
            "https://friends.roblox.com/v1/users/" + std::to_string(UID) + "/decline-friendship-request",
            "post",
            this->Cookie
        ).JsonObj;
}

void RoPP::Session::DeclineAllFriendRequests()
{
    json res = Helper::MakeRobloxRequest
        (
            "https://friends.roblox.com/v1/user/friend-requests/decline-all",
            "post",
            this->Cookie
        ).JsonObj;
}

void RoPP::Session::BlockUser(long UID)
{
    json res = Helper::MakeRobloxRequest
        (
            "https://accountsettings.roblox.com/v1/users/" + std::to_string(UID) + "/block",
            "post",
            this->Cookie
        ).JsonObj;
}

void RoPP::Session::UnblockUser(long UID)
{
    json res = Helper::MakeRobloxRequest
        (
            "https://accountsettings.roblox.com/v1/users/" + std::to_string(UID) + "/unblock",
            "post",
            this->Cookie
        ).JsonObj;
}

void RoPP::Session::SetDescription(string Description)
{
    json data = 
    {
        {"description", Description}
    };

    json res = Helper::MakeRobloxRequest
        (
            "https://accountinformation.roblox.com/v1/description",
            "post",
            this->Cookie,
            data
        ).JsonObj;
}

void RoPP::Session::SetGender(string Gender)
{
    json data = 
    {
        {"gender", Gender}
    };

    json res = Helper::MakeRobloxRequest
    (
        "https://accountinformation.roblox.com/v1/gender",
        "post",
        this->Cookie,
        data
    ).JsonObj;
} 