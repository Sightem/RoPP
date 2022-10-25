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
    Request req("https://games.roblox.com/v1/games?universeIds=" + std::to_string(GetUniverseID()));
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();

    Response res = req.get();

    return json::parse(res.data);
}