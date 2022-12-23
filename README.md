

<p align="center"><b>RoPP</b></p>

<p align="center">
  <img src="https://img.shields.io/github/license/sightem/ropp">
  <img src="https://img.shields.io/github/issues/sightem/ropp">
  <img src="https://img.shields.io/github/commit-activity/w/sightem/ropp">
</p>

An API wrapper for Roblox written in C++20. This library is by far the most featureful and most maintained Roblox API wrapper made in C++ supporting not only GET requests, but many authenticated POST requests as well. The goal is to keep the syntax as intuitive as possible, optimizing all the C++*ness* away.

Contributions are always welcome. Feel free to create a Pull Request.

Quick, Simple, Example
=========
```cpp
int main()
{
    RoPP::Asset asset(2409285794);

    Responses::AssetInfo AssetResponse = asset.GetAssetInfo();
    Responses::ResaleData ResaleResponse = asset.GetResaleData();
    
    std::cout << std::boolalpha;

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
```
[*simple as.*](https://github.com/Sightem/RoPP/tree/master/examples)

Usage
=========

You can easily compile RoPP into your program by including the source files in your project. **No Building is Required**.    
They are inside the [RoPP/](https://github.com/Sightem/RoPP/tree/master/RoPP) and the [include/](https://github.com/Sightem/RoPP/tree/master/include) directories. Few examples are available in the [examples/](https://github.com/Sightem/RoPP/tree/master/examples) directory.

Documentation
=========
[TODO](https://github.com/Sightem/RoPP/wiki)

Dependencies
=========
- [libcurl](https://curl.se/libcurl/)
- [nlohmanns json](https://github.com/nlohmann/json) (included)
