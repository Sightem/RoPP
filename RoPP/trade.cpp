#include "../include/ropp.h"
#include "../include/helper.h"
#include "../include/request.hpp"
#include "../include/responses.h"


void RoPP::Trade::accept_trade(int64_t trade_id)
{
    Helper::MakeAuthedRobloxRequest
    (
        "https://trades.roblox.com/v1/trades/" + std::to_string(trade_id) + "/accept",
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED
    );
}

void RoPP::Trade::decline_trade(int64_t trade_id)
{
    Helper::MakeAuthedRobloxRequest
    (
        "https://trades.roblox.com/v1/trades/" + std::to_string(trade_id) + "/decline",
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED
    );
}

std::vector<Responses::TradeData> RoPP::Trade::get_trades(std::string trade_status_type, std::string sort, int32_t limit)
{
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://trades.roblox.com/v1/trades/" + trade_status_type + "?sortOrder=" + sort + "&limit=" + std::to_string(limit),
        "GET",
        this->m_Cookie,
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

json RoPP::Trade::get_trade_info(int64_t trade_id)
{
    return Helper::MakeAuthedRobloxRequest
    (
        "https://trades.roblox.com/v1/trades/" + std::to_string(trade_id),
        "GET",
        this->m_Cookie,
        CSRF_REQUIRED
    ).JsonObj;
}

Responses::CanTradeWithResponse RoPP::Trade::can_trade_with(int64_t user_id)
{
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://trades.roblox.com/v1/users/" + std::to_string(user_id) + "/can-trade-with",
        "GET",
        this->m_Cookie,
        CSRF_REQUIRED
    ).JsonObj;

    return Responses::CanTradeWithResponse(res);
}

int RoPP::Trade::send_trade_request(int64_t target_uid, json user_offer, json user_request)
{
    RoPP::Session Session(this->m_Cookie);

    json data =
    {
        {"offers", {
            {
                {"userId", target_uid},
                {"userAssetIds", user_offer["userAssetIds"]},
                {"robux", user_request["robux"]}
            },
            {
                {"userId", Session.GetUserID()},
                {"userAssetIds", user_offer["userAssetIds"]},
                {"robux", user_request["robux"]}
            }
        }}
    };

    return Helper::MakeAuthedRobloxRequest
    (
        "https://trades.roblox.com/v1/trades/send",
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED,
        data
    ).JsonObj["id"];
}
