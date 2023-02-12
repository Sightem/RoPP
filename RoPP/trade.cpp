#include "../include/ropp.h"
#include "../include/helper.h"
#include "../include/request.hpp"
#include "../include/responses.h"


void RoPP::Trade::AcceptTrade(long TradeID)
{
    Helper::MakeAuthedRobloxRequest
    (
        "https://trades.roblox.com/v1/trades/" + std::to_string(TradeID) + "/accept",
        "POST",
        this->Cookie,
        CSRF_REQUIRED
    );
}

void RoPP::Trade::DeclineTrade (long TradeID)
{
    Helper::MakeAuthedRobloxRequest
    (
        "https://trades.roblox.com/v1/trades/" + std::to_string(TradeID) + "/decline",
        "POST",
        this->Cookie,
        CSRF_REQUIRED
    );
}

std::vector<Responses::TradeData> RoPP::Trade::GetTrades(std::string tradeStatusType, std::string Sort, int Limit)
{
    json res = Helper::MakeAuthedRobloxRequest
    (
        "https://trades.roblox.com/v1/trades/" + tradeStatusType + "?sortOrder=" + Sort + "&limit=" + std::to_string(Limit),
        "GET",
        this->Cookie,
        CSRF_REQUIRED
    ).JsonObj;

    std::vector<Responses::TradeData> Trades;
    if (res.contains("data"))
    {
        for (auto& i : res["data"])
        {
            Trades.emplace_back(i);
        }
    }

    return Trades;
}

json RoPP::Trade::GetTradeInfo(long TradeID)
{
    return Helper::MakeAuthedRobloxRequest
    (
        "https://trades.roblox.com/v1/trades/" + std::to_string(TradeID),
        "GET",
        this->Cookie,
        CSRF_REQUIRED
    ).JsonObj;
}

Responses::CanTradeWithResponse RoPP::Trade::CanTradeWith(long UserID)
{
    json res = Helper::MakeAuthedRobloxRequest
    (
        "https://trades.roblox.com/v1/users/" + std::to_string(UserID) + "/can-trade-with",
        "GET",
        this->Cookie,
        CSRF_REQUIRED
    ).JsonObj;

    return Responses::CanTradeWithResponse(res);
}

int RoPP::Trade::SendTradeRequest(long TargetUID, json UserOffer, json UserRequest)
{
    RoPP::Session Session(this->Cookie);

    json data =
    {
        {"offers", {
            {
                {"userId", TargetUID},
                {"userAssetIds", UserRequest["userAssetIds"]},
                {"robux", UserRequest["robux"]}
            },
            {
                {"userId", Session.GetUserID()},
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
        CSRF_REQUIRED,
        data
    ).JsonObj["id"];
}
