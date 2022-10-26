#include "ropp.h"
#include "../include/request.hpp"

int RoPP::Place::GetUniverseID()
{
    Request req("https://api.roblox.com/universes/get-universe-containing-place?placeid=" + std::to_string(this->PID));
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();

    Response res = req.get();

    return json::parse(res.data)["UniverseId"];
}

json RoPP::Place::GetPlaceInfo()
{
    Request req("https://games.roblox.com/v1/games?universeIds=" + std::to_string(this->UniverseID));
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();

    Response res = req.get();

    return json::parse(res.data);
}

std::string RoPP::Place::GetPlaceName()
{
    return GetPlaceInfo()["data"][0]["name"];
}

std::string RoPP::Place::GetPlaceDescription()
{
    return GetPlaceInfo()["data"][0]["description"];
}

std::string RoPP::Place::GetCreatorName()
{
    return GetPlaceInfo()["data"][0]["creator"]["name"];
}

std::string RoPP::Place::GetCreatorType()
{
    return GetPlaceInfo()["data"][0]["creator"]["type"];
}

std::string RoPP::Place::GetUpdatedDate()
{
    return GetPlaceInfo()["data"][0]["updated"];
}

std::string RoPP::Place::GetCreationDate()
{
    return GetPlaceInfo()["data"][0]["created"];
}

std::string RoPP::Place::GetGenre()
{
    return GetPlaceInfo()["data"][0]["genre"];
}

json RoPP::Place::GetPlaceCreator()
{
    return GetPlaceInfo()["data"][0]["creator"];
}

json RoPP::Place::GetAllowedGear()
{
    return GetPlaceInfo()["data"][0]["allowedGearGenres"];
}

int RoPP::Place::GetCreatorID()
{
    return GetPlaceInfo()["data"][0]["creator"]["id"];
}

int RoPP::Place::GetPrice()
{
    return GetPlaceInfo()["data"][0]["price"];
}

long RoPP::Place::GetPlaceVisits()
{
    return GetPlaceInfo()["data"][0]["visits"];
}

long RoPP::Place::GetCurrentPlayers()
{
    return GetPlaceInfo()["data"][0]["playing"];
}

int RoPP::Place::GetMaxPlayers()
{
    return GetPlaceInfo()["data"][0]["maxPlayers"];
}

long RoPP::Place::GetFavoriteCount()
{
    return GetPlaceInfo()["data"][0]["favoritedCount"];
}

bool RoPP::Place::IsCopyable()
{
    return GetPlaceInfo()["data"][0]["copyingAllowed"];
}

bool RoPP::Place::IsVIPServerAllowed()
{
    return GetPlaceInfo()["data"][0]["createVipServersAllowed"];
}