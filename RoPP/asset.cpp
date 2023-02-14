#include "../include/ropp.h"
#include "../include/helper.h"

json RoPP::Asset::buy_asset()
{
    Responses::AssetInfo info = this->get_asset_info();
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://economy.roblox.com/v1/purchases/products/" + std::to_string(info.product_id),
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED,
        {
            {"expectedCurrency", 1},
            {"expectedPrice", info.price},
            {"expectedSellerId", info.creator_id}
        }
    ).JsonObj;

    return res;
}

Responses::AssetInfo RoPP::Asset::get_asset_info()
{
    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://economy.roblox.com/v2/assets/" + std::to_string(this->m_AssetID) + "/details",
        "GET",
        this->m_Cookie
    ).JsonObj;

    return Responses::AssetInfo(res);
}

std::vector<Responses::ResellerData> RoPP::Asset::get_asset_resellers(std::string Sort, int Limit)
{
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://economy.roblox.com/v1/assets/" + std::to_string(this->m_AssetID) + "/resellers?" + Sort + "&limit=" + std::to_string(Limit),
        "GET",
        this->m_Cookie,
        CSRF_NOT_REQUIRED
    ).JsonObj;
    
    std::vector<Responses::ResellerData> resellers;
    for (auto& i : res["data"]) resellers.push_back(Responses::ResellerData(i));

    return resellers;
}

Responses::ResaleData RoPP::Asset::get_resale_data()
{
    ordered_json res =  Helper::MakeAuthedRobloxRequest
    (
        "https://economy.roblox.com/v1/assets/" + std::to_string(this->m_AssetID) + "/resale-data",
        "GET",
        this->m_Cookie,
        CSRF_NOT_REQUIRED
    ).JsonObj;

    return Responses::ResaleData(res);
}