> [!WARNING]  
> This project has been on hold for quite a while due to there not being much use for it, hence demotivating me. I plan on coming back to this later in 2025

<p align="center"><b>RoPP</b></p>

<p align="center">
  <img src="https://img.shields.io/github/license/sightem/ropp">
  <img src="https://img.shields.io/github/issues/sightem/ropp">
  <img src="https://img.shields.io/github/commit-activity/w/sightem/ropp">
</p>

An API wrapper for Roblox written in C++20. This library is by far the most featureful and most maintained Roblox API wrapper made in C++ supporting not only GET requests, but many authenticated POST requests as well. The goal is to keep the syntax as intuitive as possible, optimizing all the C++*ness* away.

Contributions are always welcome. Feel free to create a Pull Request.

Quick and Simple Example
=========
```cpp
#include "RoPP/ropp.h"
#include "RoPP/responses.h"
#include <iostream>

int main()
{
    RoPP::Asset asset(2409285794);
    asset.set_cookie("cookie");

    Responses::AssetInfo AssetResponse = asset.get_asset_info();
    Responses::ResaleData ResaleResponse = asset.get_resale_data();
    
    std::cout << std::boolalpha;

    std::cout << "Asset Name: " << AssetResponse.name << std::endl;
    std::cout << "Asset Description: " << AssetResponse.description << std::endl;
    std::cout << "Asset Creator: " << AssetResponse.creator.name << std::endl;
    std::cout << "Asset Creator ID: " << AssetResponse.creator.user_id << std::endl;
    std::cout << "Asset Asset Type: " << AssetResponse.asset_type << std::endl;
    std::cout << "Asset Product ID: " << AssetResponse.product_id << std::endl;
    std::cout << "Asset Price: " << AssetResponse.price << std::endl;
    std::cout << "Asset Sales: " << AssetResponse.sales << std::endl;
    std::cout << "Asset Is New: " << AssetResponse.is_new << std::endl;
    std::cout << "Asset Is Limited: " << AssetResponse.is_limited << std::endl;
    std::cout << "Asset Is Limited Unique: " << AssetResponse.is_limited_unique << std::endl;
    std::cout << "Asset Is For Sale: " << AssetResponse.is_for_sale << std::endl;
    std::cout << "Asset Creation Date: " << AssetResponse.created.to_ISO8601() << std::endl;
    std::cout << "Asset Updated Date: " << AssetResponse.updated.to_ISO8601() << std::endl;

    std::cout << std::endl;

    std::cout << "Recent Average Resale Price: " << ResaleResponse.recent_average_price << std::endl;
}
```
[*simple as.*](https://github.com/Sightem/RoPP/tree/master/examples)

Usage
=========

You can easily compile RoPP into your program by including the source files in your project. **No Binary is Required**.    
They are inside the [RoPP/](https://github.com/Sightem/RoPP/tree/master/RoPP) and the [include/](https://github.com/Sightem/RoPP/tree/master/include) directories. Few examples are available in the [examples/](https://github.com/Sightem/RoPP/tree/master/examples) directory.

Documentation
=========
[TODO](https://github.com/Sightem/RoPP/wiki)

Dependencies
=========
- [libcurl](https://curl.se/libcurl/)
- [nlohmanns json](https://github.com/nlohmann/json) (included)
