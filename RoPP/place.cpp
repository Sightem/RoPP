#include "ropp.h"
#include "../include/helper.h"
#include "../include/request.hpp"

long RoPP::Place::GetUniverseID()
{
    json res = Helper::MakeRobloxRequest
    (
        "https://apis.roblox.com/universes/v1/places/" + std::to_string(this->PID) + "/universe",
        "GET"
    ).JsonObj;

    return res["universeId"];
}

Responses::PlaceInfoResponse RoPP::Place::GetPlaceInfo()
{
    json res = Helper::MakeRobloxRequest
    (
        "https://games.roblox.com/v1/games?universeIds=" + std::to_string(this->UniverseID),
        "GET"
    ).JsonObj;

    return Responses::PlaceInfoResponse().Parse(res["data"][0]);
}

long RoPP::Place::GetDownVotes()
{
    Request req("https://games.roblox.com/v1/games/votes?universeIds=" + std::to_string(this->UniverseID));
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data)["data"][0]["downVotes"];
}

json RoPP::Place::GetGamepassInfo(std::string Sort, int Limit)
{
    Request req("https://games.roblox.com/v1/games/" + std::to_string(this->UniverseID) + "/game-passes?sortOrder=" + Sort + "&limit=" + std::to_string(Limit));
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data);
}