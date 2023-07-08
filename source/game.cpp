#include "../include/RoPP/ropp.h"
#include "../include/RoPP/helper.h"
#include "../include/RoPP/request.hpp"

int64_t RoPP::Game::get_universe_id()
{
    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://apis.roblox.com/universes/v1/places/" + std::to_string(this->m_PlaceID) + "/universe",
        "GET"
    ).JsonObj;

    return res["universeId"];
}

Responses::PlaceInfoResponse RoPP::Game::get_place_info()
{
    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://games.roblox.com/v1/games?universeIds=" + std::to_string(this->m_UniverseID),
        "GET"
    ).JsonObj;

    return Responses::PlaceInfoResponse(res["data"][0]);
}

Responses::ExperienceVotes RoPP::Game::get_votes()
{
    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://games.roblox.com/v1/games/votes?universeIds=" + std::to_string(this->m_UniverseID),
        "GET"
    ).JsonObj;

    return Responses::ExperienceVotes(res["data"][0]);
}

std::vector<Responses::GamePass> RoPP::Game::get_gamepasses(const std::string& sort, int limit)
{
    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://games.roblox.com/v1/games/" + std::to_string(this->m_UniverseID) + "/game-passes?sortOrder=" + sort + "&limit=" + std::to_string(limit),
        "GET"
    ).JsonObj;

    std::vector<Responses::GamePass> passes;
    for (auto& pass : res["data"])
    {
        passes.emplace_back(pass);
    }

    return passes;
}

Responses::DeveloperProductCreateResponse RoPP::Game::create_developer_product(const std::string& name, const std::string& description, long price, int64_t icon_image_asset_id)
{
    //untested
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://develop.roblox.com/v1/universes/" + std::to_string(this->m_UniverseID) + "/developerproducts?name=" + name + "&description=" + description + "&priceInRobux=" + std::to_string(price) + "&iconImageAssetId=" + std::to_string(icon_image_asset_id),
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED
    ).JsonObj;

    return Responses::DeveloperProductCreateResponse(res);
}

std::vector<Responses::GameInstance> RoPP::Game::get_game_instances(const std::string& type, const std::string& sort, int limit, bool exclude_full_games)
{
    json res;
    
    if (this->m_Cookie.empty())
    {
        res = Helper::MakeRobloxRequest
        (
            "https://games.roblox.com/v1/games/" + std::to_string(this->m_PlaceID) + "/servers/" + type + "?sortOrder=" + sort + "&excludeFullGames=" + std::to_string(exclude_full_games) + "&limit=" + std::to_string(limit),
            "GET"
        ).JsonObj;
    }
    else
    {
        res = Helper::MakeAuthedRobloxRequest
        (
            "https://games.roblox.com/v1/games/" + std::to_string(this->m_PlaceID) + "/servers/" + type + "?sortOrder=" + sort + "&excludeFullGames=" + std::to_string(exclude_full_games) + "&limit=" + std::to_string(limit),
            "GET",
            this->m_Cookie,
            CSRF_REQUIRED
        ).JsonObj;
    }

    std::vector<Responses::GameInstance> instances;
    for (auto& instance : res["data"])
    {
        instances.push_back(Responses::GameInstance(instance));
    }

    return instances;
}

Responses::GameSocialLinks RoPP::Game::get_social_links()
{
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://games.roblox.com/v1/games/" + std::to_string(this->m_UniverseID) + "/social-links/list",
        "GET",
        this->m_Cookie,
        CSRF_NOT_REQUIRED
    ).JsonObj;

    return Responses::GameSocialLinks(res);
}

std::vector<Responses::Badge> RoPP::Game::get_game_badges(const std::string& sort, int limit)
{
    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://badges.roblox.com/v1/universes/" + std::to_string(this->m_UniverseID) + "/badges?sortOrder=" + sort + "&limit=" + std::to_string(limit),
        "GET"
    ).JsonObj;

    std::vector<Responses::Badge> badges;
    for (auto& badge : res["data"])
    {
        badges.emplace_back(badge);
    }

    return badges;
}

int64_t RoPP::Game::create_game_pass(const std::string& name, const std::string& description, long price, const std::string& icon_path)
{
    Request req("https://apis.roblox.com/game-passes/v1/game-passes");
    req.set_header("User-Agent", USER_AGENT);
    req.set_cookie(".ROBLOSECURITY", this->m_Cookie);
    req.set_header("x-csrf-token", this->get_csrf());
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();

    Form form = req.form_data();
    form.append_string("Name", name);
    form.append_string("Description", description);
    form.append_string("UniverseId", std::to_string(this->m_UniverseID));
    form.append_file("File", icon_path);

    Response response = req.form(form);

    json j = json::parse(response.data);

    return j["gamePassId"];
}


int RoPP::Game::update_gamepass_price(int64_t gamepass_id, int new_price)
{
    Request req("https://apis.roblox.com/game-passes/v1/game-passes/" + std::to_string(gamepass_id) + "/details");
    req.set_header("User-Agent", USER_AGENT);
    req.set_cookie(".ROBLOSECURITY", this->m_Cookie);
    req.set_header("x-csrf-token", get_csrf());
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();

    Form form = req.form_data();
    form.append_string("IsForSale", "true");
    form.append_string("Price", std::to_string(new_price));

    Response response = req.form(form);

    return response.code;
}