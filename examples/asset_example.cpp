#include "../include/json.hpp"
#include "../RoPP/ropp.h"
#include <iostream>
#include <string>


int main()
{
    RoPP::Asset asset(22546563);

    std::cout << "Asset Name: " << asset.GetName() << std::endl;
    std::cout << "Asset Description: " << asset.GetDescription() << std::endl;
    std::cout << "Asset Creator: " << asset.GetCreatorName() << std::endl;
    std::cout << "Asset Creator ID: " << asset.GetCreatorID() << std::endl;
    std::cout << "Asset Price: " << asset.GetPrice() << std::endl;
    std::cout << "Asset Sales: " << asset.GetSales() << std::endl;
    std::cout << "Asset Is New: " << asset.IsNew() << std::endl;
    std::cout << "Asset Is Limited: " << asset.IsLimited() << std::endl;
    std::cout << "Asset Is Limited Unique: " << asset.IsLimitedUnique() << std::endl;
    std::cout << "Asset Is For Sale: " << asset.IsForSale() << std::endl;
    std::cout << "Asset Creation Date: " << asset.GetCreationDate() << std::endl;
    std::cout << "Asset Updated Date: " << asset.GetUpdatedDate() << std::endl;
    std::cout << "Asset Type: " << asset.GetType() << std::endl;
}