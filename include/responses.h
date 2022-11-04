#pragma once

#include <string>
#include "json.hpp"

using json = nlohmann::json;

struct Timestamp
{
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    
    Timestamp Parse(std::string timestamp)
    {
        Timestamp t;
        t.year = std::stoi(timestamp.substr(0, 4));
        t.month = std::stoi(timestamp.substr(5, 2));
        t.day = std::stoi(timestamp.substr(8, 2));
        t.hour = std::stoi(timestamp.substr(11, 2));
        t.minute = std::stoi(timestamp.substr(14, 2));
        t.second = std::stoi(timestamp.substr(17, 2));
        return t;
    }
};

struct AssetCreator
{
    std::string Name;
    std::string Type;
    long UID;

    AssetCreator Parse(json creator)
    {
        AssetCreator c;
        c.Name = creator["Name"];
        c.Type = creator["CreatorType"];
        c.UID = creator["Id"];
        return c;
    }
};

struct AssetInfo
{
    std::string Name;
    std::string Description;
    std::string AssetType;
    std::string CreatorName;
    std::string CreatorType;

    Timestamp Created;
    Timestamp Updated;

    AssetCreator Creator;

    int Price;

    long Sales;
    long CreatorID;
    long ProductID;

    bool IsNew;
    bool IsForSale;
    bool IsLimited;
    bool IsLimitedUnique;

    //https://github.com/ro-py/ro.py/blob/284b30dfef4c8117198b961c3b4b47c040da6af4/roblox/assets.py#L21 <3
    std::map<int, std::string> asset_type_names = 
    {
        {1, "Image"},
        {2, "T-Shirt"},
        {3, "Audio"},
        {4, "Mesh"},
        {5, "Lua"},
        {6, "HTML"},
        {7, "Text"},
        {8, "Hat"},
        {9, "Place"},
        {10, "Model"},
        {11, "Shirt"},
        {12, "Pants"},
        {13, "Decal"},
        {16, "Avatar"},
        {17, "Head"},
        {18, "Face"},
        {19, "Gear"},
        {21, "Badge"},
        {22, "Group Emblem"},
        {24, "Animation"},
        {25, "Arms"},
        {26, "Legs"},
        {27, "Torso"},
        {28, "Right Arm"},
        {29, "Left Arm"},
        {30, "Left Leg"},
        {31, "Right Leg"},
        {32, "Package"},
        {33, "YouTubeVideo"},
        {34, "Pass"},
        {35, "App"},
        {37, "Code"},
        {38, "Plugin"},
        {39, "SolidModel"},
        {40, "MeshPart"},
        {41, "Hair Accessory"},
        {42, "Face Accessory"},
        {43, "Neck Accessory"},
        {44, "Shoulder Accessory"},
        {45, "Front Accessory"},
        {46, "Back Accessory"},
        {47, "Waist Accessory"},
        {48, "Climb Animation"},
        {49, "Death Animation"},
        {50, "Fall Animation"},
        {51, "Idle Animation"},
        {52, "Jump Animation"},
        {53, "Run Animation"},
        {54, "Swim Animation"},
        {55, "Walk Animation"},
        {56, "Pose Animation"},
        {59, "LocalizationTableManifest"},
        {60, "LocalizationTableTranslation"},
        {61, "Emote Animation"},
        {62, "Video"},
        {63, "TexturePack"},
        {64, "T-Shirt Accessory"},
        {65, "Shirt Accessory"},
        {66, "Pants Accessory"},
        {67, "Jacket Accessory"},
        {68, "Sweater Accessory"},
        {69, "Shorts Accessory"},
        {70, "Left Shoe Accessory"},
        {71, "Right Shoe Accessory"},
        {72, "Dress Skirt Accessory"},
        {73, "Font Family"},
        {74, "Font Face"},
        {75, "MeshHiddenSurfaceRemoval"}
    };

    AssetInfo Parse(json Data)
    {
        AssetInfo info;

        info.Name = Data["Name"];
        info.Description = Data["Description"];
        info.AssetType = asset_type_names[Data["AssetTypeId"]];
        info.Created = Timestamp().Parse(Data["Created"]);
        info.Updated = Timestamp().Parse(Data["Updated"]);
        info.CreatorName = Data["Creator"]["Name"];
        info.CreatorType = Data["Creator"]["CreatorType"];
        info.Creator = AssetCreator().Parse(Data["Creator"]);
        info.Price = Data["PriceInRobux"];
        info.Sales = Data["Sales"];
        info.CreatorID = Data["Creator"]["Id"];
        info.IsNew = Data["IsNew"];
        info.IsForSale = Data["IsForSale"];
        info.IsLimited = Data["IsLimited"];
        info.IsLimitedUnique = Data["IsLimitedUnique"];
        info.ProductID = Data["ProductId"];

        return info;
    }
};