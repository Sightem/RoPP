#include "ropp.h"
#include "../include/request.hpp"

json RoPP::Asset::GetAssetInfo()
{
    Request req("https://economy.roblox.com/v2/assets/" + std::to_string(this->AID) + "/details");
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();

    Response res = req.get();

    return json::parse(res.data);
}

std::string RoPP::Asset::GetName()
{
    return GetAssetInfo()["Name"];
}

std::string RoPP::Asset::GetType()
{
    return asset_type_names[GetAssetInfo()["AssetTypeId"]];
}

std::string RoPP::Asset::GetDescription()
{
    return GetAssetInfo()["Description"];
}

std::string RoPP::Asset::GetCreatorName()
{
    return GetAssetInfo()["Creator"]["Name"];
}

long RoPP::Asset::GetCreatorID()
{
    return GetAssetInfo()["Creator"]["Id"];
}

long RoPP::Asset::GetPrice()
{
    return GetAssetInfo()["PriceInRobux"];
}

long RoPP::Asset::GetSales()
{
    return GetAssetInfo()["Sales"];
}

std::string RoPP::Asset::GetCreationDate()
{
    return GetAssetInfo()["Created"];
}

std::string RoPP::Asset::GetUpdatedDate()
{
    return GetAssetInfo()["Updated"];
}

json RoPP::Asset::GetAssetCreator()
{
    return GetAssetInfo()["Creator"];
}

bool RoPP::Asset::IsForSale()
{
    return GetAssetInfo()["IsForSale"];
}

bool RoPP::Asset::IsLimited()
{
    return GetAssetInfo()["IsLimited"];
}

bool RoPP::Asset::IsLimitedUnique()
{
    return GetAssetInfo()["IsLimitedUnique"];
}

bool RoPP::Asset::IsNew()
{
    return GetAssetInfo()["IsNew"];
}