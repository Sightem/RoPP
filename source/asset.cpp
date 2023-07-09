#include "../include/RoPP/ropp.h"
#include <cpr/cpr.h>

/*
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
*/

Responses::AssetInfo RoPP::Asset::get_asset_info()
{
    cpr::Response r = cpr::Get(
        cpr::Url{ "https://economy.roblox.com/v2/assets/" + std::to_string(this->m_AssetID) + "/details" } //TODO take a look at this
	);
	nlohmann::json res = nlohmann::json::parse(r.text);

	return Responses::AssetInfo(res);
}

std::vector<Responses::ResellerData> RoPP::Asset::get_asset_resellers(std::string Sort, int Limit)
{

    cpr::Response r = cpr::Get(
        cpr::Url{ "https://economy.roblox.com/v1/assets/" + std::to_string(this->m_AssetID) + "/resellers?" + Sort + "&limit=" + std::to_string(Limit) },
        cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "User-Agent", USER_AGENT } },
        cpr::Cookies{ {".ROBLOSECURITY", this->m_Cookie} }
    );
    nlohmann::json res = nlohmann::json::parse(r.text);

    std::vector<Responses::ResellerData> resellers;
    for (auto& i : res["data"]) resellers.push_back(Responses::ResellerData(i));

    return resellers;
}

Responses::ResaleData RoPP::Asset::get_resale_data()
{
    /*

    ordered_json res =  Helper::MakeAuthedRobloxRequest
    (
        "https://economy.roblox.com/v1/assets/" + std::to_string(this->m_AssetID) + "/resale-data",
        "GET",
        this->m_Cookie,
        CSRF_NOT_REQUIRED
    ).JsonObj;

    return Responses::ResaleData(res);
    */

    cpr::Response r = cpr::Get(
		cpr::Url{ "https://economy.roblox.com/v1/assets/" + std::to_string(this->m_AssetID) + "/resale-data" },
		cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "User-Agent", USER_AGENT } },
		cpr::Cookies{ {".ROBLOSECURITY", this->m_Cookie} }
	);

    nlohmann::json res = nlohmann::json::parse(r.text);

    return Responses::ResaleData(res);
}