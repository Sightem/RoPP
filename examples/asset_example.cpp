#include "../include/ropp.h"
#include "../include/responses.h"
#include <iostream>
#include <string>


int main()
{
    RoPP::Asset asset(2409285794);
    asset.SetCookie("cookie");

    Responses::AssetInfo AssetResponse = asset.GetAssetInfo();
    Responses::ResaleData ResaleResponse = asset.GetResaleData();
    
    std::cout << std::boolalpha;

    std::string PrintString = "Asset Name: " + AssetResponse.Name + "\n" +
                              "Asset Description: " + AssetResponse.Description + "\n" +
                              "Asset Creator: " + AssetResponse.Creator.Username + "\n" +
                              "Asset Creator ID: " + std::to_string(AssetResponse.Creator.UID) + "\n" +
                              "Asset Asset Type: " + AssetResponse.AssetType + "\n" +
                              "Asset Product ID: " + std::to_string(AssetResponse.ProductID) + "\n" +
                              "Asset Price: " + std::to_string(AssetResponse.Price) + "\n" +
                              "Asset Sales: " + std::to_string(AssetResponse.Sales) + "\n" +
                              "Asset Is New: " + std::to_string(AssetResponse.IsNew) + "\n" +
                              "Asset Is Limited: " + std::to_string(AssetResponse.IsLimited) + "\n" +
                              "Asset Is Limited Unique: " + std::to_string(AssetResponse.IsLimitedUnique) + "\n" +
                              "Asset Is For Sale: " + std::to_string(AssetResponse.IsForSale) + "\n" +
                              "Asset Creation Date: " + AssetResponse.Created.ToISO8601() + "\n" +
                              "Asset Updated Date: " + AssetResponse.Updated.ToISO8601() + "\n";

    std::cout << PrintString << std::endl;

    std::cout << "Recent Average Resale Price: " << ResaleResponse.RecentAveragePrice << std::endl;
}