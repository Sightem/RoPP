#include "RoPP/ropp.h"
#include "RoPP/responses.h"
#include <iostream>
#include <string>


int main()
{
    RoPP::Asset asset(2409285794);
    asset.set_cookie("cookie");

    Responses::AssetInfo AssetResponse = asset.get_asset_info();
    Responses::ResaleData ResaleResponse = asset.get_resale_data();
    
    std::cout << std::boolalpha;

    std::string PrintString = "Asset Name: " + AssetResponse.name + "\n" +
                              "Asset Description: " + AssetResponse.description + "\n" +
                              "Asset Creator: " + AssetResponse.creator.name + "\n" +
                              "Asset Creator ID: " + std::to_string(AssetResponse.creator.user_id) + "\n" +
                              "Asset Asset Type: " + AssetResponse.asset_type + "\n" +
                              "Asset Product ID: " + std::to_string(AssetResponse.product_id) + "\n" +
                              "Asset Price: " + std::to_string(AssetResponse.price) + "\n" +
                              "Asset Sales: " + std::to_string(AssetResponse.sales) + "\n" +
                              "Asset Is New: " + std::to_string(AssetResponse.is_new) + "\n" +
                              "Asset Is Limited: " + std::to_string(AssetResponse.is_limited) + "\n" +
                              "Asset Is Limited Unique: " + std::to_string(AssetResponse.is_limited_unique) + "\n" +
                              "Asset Is For Sale: " + std::to_string(AssetResponse.is_for_sale) + "\n" +
                              "Asset Creation Date: " + AssetResponse.created.to_ISO8601() + "\n" +
                              "Asset Updated Date: " + AssetResponse.updated.to_ISO8601() + "\n";

    std::cout << PrintString << std::endl;

    std::cout << "Recent Average Resale Price: " << ResaleResponse.recent_average_price << std::endl;
}