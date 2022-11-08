#include "ropp.h"
#include "../include/helper.h"
#include "../include/request.hpp"
#include "../include/responses.h"

using namespace Responses;

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
   json res = Helper::MakeAuthedRobloxRequest
    (
        "https://users.roblox.com/v1/users/authenticated",
        "GET",
        this->Cookie
    ).JsonObj;

    return res["id"];
}

std::string RoPP::Session::GetUsername()
{
    json res = Helper::MakeAuthedRobloxRequest
    (
        "https://users.roblox.com/v1/users/authenticated",
        "GET",
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
    json res = Helper::MakeAuthedRobloxRequest
    (
        "https://accountinformation.roblox.com/v1/birthdate",
        "GET",
        this->Cookie
    ).JsonObj;

    return res;
}

std::string RoPP::Session::GetDescription()
{
    json res = Helper::MakeAuthedRobloxRequest
    (
        "https://accountinformation.roblox.com/v1/description",
        "GET",
        this->Cookie
    ).JsonObj;

    return res["description"];
}

json RoPP::Session::GetPhoneInfo()
{
    json res = Helper::MakeAuthedRobloxRequest
    (
        "https://accountinformation.roblox.com/v1/phone",
        "GET",
        this->Cookie
    ).JsonObj;

    return res;
}

long RoPP::Session::GetRobuxBalance()
{
    json res = Helper::MakeAuthedRobloxRequest
    (
        "https://economy.roblox.com/v1/users/" + std::to_string(this->GetUserID()) + "/currency",
        "GET",
        this->Cookie
    ).JsonObj;

    return res["robux"];
}

bool RoPP::Session::HasPremium()
{
    json res = Helper::MakeAuthedRobloxRequest
    (
        "https://premiumfeatures.roblox.com/v1/users/" + std::to_string(this->GetUserID()) + "/validate-membership",
        "GET",
        this->Cookie
    ).JsonObj;

    return res;
}

int RoPP::Session::GetFriendsCount()
{
    json res = Helper::MakeAuthedRobloxRequest
    (
        "https://friends.roblox.com/v1/my/friends/count",
        "GET",
        this->Cookie
    ).JsonObj;

    return res["count"];
}

json RoPP::Session::GetFriendRequests(string Sort, int Limit)
{
    json res = Helper::MakeAuthedRobloxRequest
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

   json res = Helper::MakeAuthedRobloxRequest
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

    json res = Helper::MakeAuthedRobloxRequest
        (
            "https://games.roblox.com/v1/games/" + std::to_string(UniverseID) + "/favorites",
            "POST",
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

    json res = Helper::MakeAuthedRobloxRequest
        (
            "https://auth.roblox.com/v1/account/pin/unlock",
            "POST",
            this->Cookie,
            data
        ).JsonObj;


    return res["unlockedUntil"]; 
}

bool RoPP::Session::LockPin()
{
    json res = Helper::MakeAuthedRobloxRequest
        (
            "https://auth.roblox.com/v1/account/pin/lock",
            "POST",
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

    Helper::WebResponse res = Helper::MakeAuthedRobloxRequest
        (
            "https://auth.roblox.com/v2/user/passwords/change",
            "POST",
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

    json res = Helper::MakeAuthedRobloxRequest
        (
            "https://friends.roblox.com/v1/users/" + std::to_string(UID) + "/request-friendship",
            "POST",
            this->Cookie,
            data
        ).JsonObj;

    return res["success"];
}

void RoPP::Session::AcceptFriendRequest(long UID)
{
    json res = Helper::MakeAuthedRobloxRequest
        (
            "https://friends.roblox.com/v1/users/" + std::to_string(UID) + "/accept-friendship-request",
            "POST",
            this->Cookie
        ).JsonObj;
}

void RoPP::Session::DeclineFriendRequest(long UID)
{
    json res = Helper::MakeAuthedRobloxRequest
        (
            "https://friends.roblox.com/v1/users/" + std::to_string(UID) + "/decline-friendship-request",
            "POST",
            this->Cookie
        ).JsonObj;
}

void RoPP::Session::DeclineAllFriendRequests()
{
    json res = Helper::MakeAuthedRobloxRequest
        (
            "https://friends.roblox.com/v1/user/friend-requests/decline-all",
            "POST",
            this->Cookie
        ).JsonObj;
}

void RoPP::Session::BlockUser(long UID)
{
    json res = Helper::MakeAuthedRobloxRequest
        (
            "https://accountsettings.roblox.com/v1/users/" + std::to_string(UID) + "/block",
            "POST",
            this->Cookie
        ).JsonObj;
}

void RoPP::Session::UnblockUser(long UID)
{
    json res = Helper::MakeAuthedRobloxRequest
        (
            "https://accountsettings.roblox.com/v1/users/" + std::to_string(UID) + "/unblock",
            "POST",
            this->Cookie
        ).JsonObj;
}

void RoPP::Session::SetDescription(string Description)
{
    json data = 
    {
        {"description", Description}
    };

    json res = Helper::MakeAuthedRobloxRequest
        (
            "https://accountinformation.roblox.com/v1/description",
            "POST",
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

    json res = Helper::MakeAuthedRobloxRequest
    (
        "https://accountinformation.roblox.com/v1/gender",
        "POST",
        this->Cookie,
        data
    ).JsonObj;
}

json RoPP::Session::BuyAsset(long AssetID)
{
    RoPP::Asset asset(AssetID);
    AssetInfo info = asset.GetAssetInfo();

    json data = 
    {
        {"expectedCurrency", 1},
        {"expectedPrice", info.Price},
        {"expectedSellerId", info.CreatorID},
    };

    json res = Helper::MakeAuthedRobloxRequest
    (
        "https://economy.roblox.com/v1/purchases/products/" + std::to_string(info.ProductID),
        "POST",
        this->Cookie,
        data
    ).JsonObj;

    return res;
}

json RoPP::Session::GetAvatar()
{
    return Helper::MakeAuthedRobloxRequest
    (
        "https://avatar.roblox.com/v1/users/" + std::to_string(this->GetUserID()) + "/avatar",
        "GET",
        this->Cookie
    ).JsonObj;
}

json RoPP::Session::GetTrades(string tradeStatusType, string Sort, int Limit)
{
    return Helper::MakeAuthedRobloxRequest
    (
        "https://trades.roblox.com/v1/trades/" + tradeStatusType + "?sortOrder=" + Sort + "&limit=" + std::to_string(Limit),
        "GET",
        this->Cookie
    ).JsonObj;
}

json RoPP::Session::GetTradeInfo(long TradeID)
{
    return Helper::MakeAuthedRobloxRequest
    (
        "https://trades.roblox.com/v1/trades/" + std::to_string(TradeID),
        "GET",
        this->Cookie
    ).JsonObj;
}

void RoPP::Session::AcceptTrade(long TradeID)
{
    Helper::MakeAuthedRobloxRequest
    (
        "https://trades.roblox.com/v1/trades/" + std::to_string(TradeID) + "/accept",
        "POST",
        this->Cookie
    );
}

void RoPP::Session::DeclineTrade (long TradeID)
{
    Helper::MakeAuthedRobloxRequest
    (
        "https://trades.roblox.com/v1/trades/" + std::to_string(TradeID) + "/decline",
        "POST",
        this->Cookie
    );
}

json RoPP::Session::CanTradeWith(long UID)
{
    return Helper::MakeAuthedRobloxRequest
    (
        "https://trades.roblox.com/v1/users/" + std::to_string(UID) + "/can-trade-with",
        "GET",
        this->Cookie
    ).JsonObj;
}

int RoPP::Session::GetTradeCount(string TradeStatusType)
{
    return Helper::MakeAuthedRobloxRequest
    (
        "https://trades.roblox.com/v1/trades/" + TradeStatusType + "/count",
        "GET",
        this->Cookie
    ).JsonObj["count"];
}

int RoPP::Session::SendTradeRequest(long TargetUID, json UserOffer, json UserRequest)
{
    json data =
    {
        {"offers", {
            {
                {"userId", TargetUID},
                {"userAssetIds", UserRequest["userAssetIds"]},
                {"robux", UserRequest["robux"]}
            },
            {
                {"userId", this->GetUserID()},
                {"userAssetIds", UserOffer["userAssetIds"]},
                {"robux", UserOffer["robux"]}
            }
        }}
    };

    return Helper::MakeAuthedRobloxRequest
    (
        "https://trades.roblox.com/v1/trades/send",
        "POST",
        this->Cookie,
        data
    ).JsonObj["id"];
}

FriendsOnlineResponse RoPP::Session::GetFriendsOnline()
{
    json res = Helper::MakeAuthedRobloxRequest
    (
        "https://friends.roblox.com/v1/users/" + std::to_string(this->GetUserID()) + "/friends/online",
        "GET",
        this->Cookie
    ).JsonObj;

    return FriendsOnlineResponse().Parse(res);
}


json RoPP::Session::GetUsersPresence(std::vector<long> UIDs)
{
    json data = 
    {
        {"userIds", UIDs}
    };

    json res = Helper::MakeAuthedRobloxRequest
    (
        "https://presence.roblox.com/v1/presence/users",
        "POST",
        this->Cookie,
        data
    ).JsonObj;

    return res;
}