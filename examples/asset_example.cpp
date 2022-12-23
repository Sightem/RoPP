#include "../include/ropp.h"
#include "../include/responses.h"
#include <iostream>
#include <string>


int main()
{
    RoPP::Asset asset(2409285794);

    Responses::AssetInfo AssetResponse = asset.GetAssetInfo();
    Responses::ResaleData ResaleResponse = asset.GetResaleData();
    
    std::cout << "Asset Name: " << AssetResponse.Name << std::endl;
    std::cout << "Asset Description: " << AssetResponse.Description << std::endl;
    std::cout << "Asset Creator: " << AssetResponse.Creator.Username << std::endl;
    std::cout << "Asset Creator ID: " << AssetResponse.Creator.UID << std::endl;
    std::cout << "Asset Asset Type: " << AssetResponse.AssetType << std::endl;
    std::cout << "Asset Product ID: " << AssetResponse.ProductID << std::endl;
    std::cout << "Asset Price: " << AssetResponse.Price << std::endl;
    std::cout << "Asset Sales: " << AssetResponse.Sales << std::endl;
    std::cout << "Asset Is New: " << AssetResponse.IsNew << std::endl;
    std::cout << "Asset Is Limited: " << AssetResponse.IsLimited << std::endl;
    std::cout << "Asset Is Limited Unique: " << AssetResponse.IsLimitedUnique << std::endl;
    std::cout << "Asset Is For Sale: " << AssetResponse.IsForSale << std::endl;
    std::cout << "Asset Creation Date: " << AssetResponse.Created.ToISO8601() << std::endl;
    std::cout << "Asset Updated Date: " << AssetResponse.Updated.ToISO8601() << std::endl;

    std::cout << std::endl;

    std::cout << "Recent Average Resale Price: " << ResaleResponse.RecentAveragePrice << std::endl;
}