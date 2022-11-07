#include "ropp.h"
#include "../include/helper.h"
#include "../include/request.hpp"
#include "../include/responses.h"

using namespace Responses;

AssetInfo RoPP::Asset::GetAssetInfo()
{
    AssetInfo AssetInfo;
    Request req("https://economy.roblox.com/v2/assets/" + std::to_string(this->AID) + "/details");
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();

    Response res = req.get();

    return AssetInfo.Parse(json::parse(res.data));
}

void RoPP::Asset::SetCookie(string Cookie)
{
    this->Cookie = Cookie;
}

Resellers RoPP::Asset::GetAssetResellers(string Sort, int Limit)
{
    json res = Helper::MakeAuthedRobloxRequest
    (
        "https://economy.roblox.com/v1/assets/" + std::to_string(this->AID) + "/resellers?" + Sort + "&limit=" + std::to_string(Limit),
        "GET",
        this->Cookie
    ).JsonObj;
    
    return Resellers().Parse(res);
}

ResaleData RoPP::Asset::GetResaleData()
{
    json res =  Helper::MakeAuthedRobloxRequest
    (
        "https://economy.roblox.com/v1/assets/" + std::to_string(this->AID) + "/resale-data",
        "GET",
        this->Cookie
    ).JsonObj;

    return ResaleData().Parse(res);
}