

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
