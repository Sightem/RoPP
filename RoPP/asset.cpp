#include "../include/ropp.h"
#include "../include/helper.h"
#include "../include/request.hpp"
#include "../include/responses.h"

json RoPP::Asset::BuyAsset()
{
    Responses::AssetInfo info = this->GetAssetInfo();
    json res = Helper::MakeAuthedRobloxRequest
    (
        "https://economy.roblox.com/v1/purchases/products/" + std::to_string(info.ProductID),
        "POST",
        this->Cookie,
        {
            {"expectedCurrency", 1},
            {"expectedPrice", info.Price},
            {"expectedSellerId", info.CreatorID}
        }
    ).JsonObj;

    return res;
}

Responses::AssetInfo RoPP::Asset::GetAssetInfo()
{
    json res = Helper::MakeRobloxRequest
    (
        "https://economy.roblox.com/v2/assets/" + std::to_string(this->AssetID) + "/details",
        "GET",
        this->Cookie
    ).JsonObj;

    return Responses::AssetInfo(res);
}

Responses::Resellers RoPP::Asset::GetAssetResellers(string Sort, int Limit)
{
    json res = Helper::MakeAuthedRobloxRequest
    (
        "https://economy.roblox.com/v1/assets/" + std::to_string(this->AssetID) + "/resellers?" + Sort + "&limit=" + std::to_string(Limit),
        "GET",
        this->Cookie
    ).JsonObj;
    
    return Responses::Resellers().Parse(res);
}

Responses::ResaleData RoPP::Asset::GetResaleData()
{
    json res =  Helper::MakeAuthedRobloxRequest
    (
        "https://economy.roblox.com/v1/assets/" + std::to_string(this->AssetID) + "/resale-data",
        "GET",
        this->Cookie
    ).JsonObj;

    return Responses::ResaleData().Parse(res);
}