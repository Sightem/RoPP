#include "../include/RoPP/ropp.h"
#include <cpr/cpr.h>

int64_t RoPP::Game::get_universe_id()
{
    /*
    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://apis.roblox.com/universes/v1/places/" + std::to_string(this->m_PlaceID) + "/universe",
        "GET"
    ).JsonObj;
    */

    cpr::Response r = cpr::Get(
		cpr::Url{ "https://apis.roblox.com/universes/v1/places/" + std::to_string(this->m_PlaceID) + "/universe" },
        cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "User-Agent", USER_AGENT } }
    );
    nlohmann::json res = nlohmann::json::parse(r.text);

    return res["universeId"];
}

Responses::PlaceInfoResponse RoPP::Game::get_place_info()
{
    /*
    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://games.roblox.com/v1/games?universeIds=" + std::to_string(this->m_UniverseID),
        "GET"
    ).JsonObj;
    */

    cpr::Response r = cpr::Get(
        cpr::Url{ "https://games.roblox.com/v1/games?universeIds=" + std::to_string(this->m_UniverseID) },
		cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "User-Agent", USER_AGENT } }
	);
    nlohmann::json res = nlohmann::json::parse(r.text);

    return Responses::PlaceInfoResponse(res["data"][0]);
}

Responses::ExperienceVotes RoPP::Game::get_votes()
{
    /*
    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://games.roblox.com/v1/games/votes?universeIds=" + std::to_string(this->m_UniverseID),
        "GET"
    ).JsonObj;
    */

    cpr::Response r = cpr::Get(
		cpr::Url{ "https://games.roblox.com/v1/games/votes?universeIds=" + std::to_string(this->m_UniverseID) },
        cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "User-Agent", USER_AGENT } }
    );

    nlohmann::json res = nlohmann::json::parse(r.text);

    return Responses::ExperienceVotes(res["data"][0]);
}

std::vector<Responses::GamePass> RoPP::Game::get_gamepasses(const std::string& sort, int limit)
{
    /*
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
    */

    cpr::Response r = cpr::Get(

        cpr::Url{ "https://games.roblox.com/v1/games/" + std::to_string(this->m_UniverseID) + "/game-passes?sortOrder=" + sort + "&limit=" + std::to_string(limit) },
		cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "User-Agent", USER_AGENT } }
	);
    nlohmann::json res = nlohmann::json::parse(r.text);

	std::vector<Responses::GamePass> passes;
    for (auto& pass : res["data"])
    {
		passes.emplace_back(pass);
	}

	return passes;
}

std::vector<Responses::GameInstance> RoPP::Game::get_game_instances(const std::string& type, const std::string& sort, int limit, bool exclude_full_games)
{

    json res;
    
    if (this->m_Cookie.empty())
    {
        /*
        
        res = Helper::MakeRobloxRequest
        (
            "https://games.roblox.com/v1/games/" + std::to_string(this->m_PlaceID) + "/servers/" + type + "?sortOrder=" + sort + "&excludeFullGames=" + std::to_string(exclude_full_games) + "&limit=" + std::to_string(limit),
            "GET"
        ).JsonObj;
        */

        cpr::Response r = cpr::Get(
			cpr::Url{ "https://games.roblox.com/v1/games/" + std::to_string(this->m_PlaceID) + "/servers/" + type + "?sortOrder=" + sort + "&excludeFullGames=" + std::to_string(exclude_full_games) + "&limit=" + std::to_string(limit) },
			cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "User-Agent", USER_AGENT } }
		);

        res = nlohmann::json::parse(r.text);
    }
    else
    {
        /* 
        res = Helper::MakeAuthedRobloxRequest
        (
            "https://games.roblox.com/v1/games/" + std::to_string(this->m_PlaceID) + "/servers/" + type + "?sortOrder=" + sort + "&excludeFullGames=" + std::to_string(exclude_full_games) + "&limit=" + std::to_string(limit),
            "GET",
            this->m_Cookie,
            CSRF_REQUIRED
        ).JsonObj;
        */

        cpr::Response r = cpr::Get(

            cpr::Url{ "https://games.roblox.com/v1/games/" + std::to_string(this->m_PlaceID) + "/servers/" + type + "?sortOrder=" + sort + "&excludeFullGames=" + std::to_string(exclude_full_games) + "&limit=" + std::to_string(limit) },
            cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "x-csrf-token", this->get_csrf() }, { "User-Agent", USER_AGENT } },
            cpr::Cookies{ {".ROBLOSECURITY", this->m_Cookie} }
		);

        res = nlohmann::json::parse(r.text);
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
    /*
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://games.roblox.com/v1/games/" + std::to_string(this->m_UniverseID) + "/social-links/list",
        "GET",
        this->m_Cookie,
        CSRF_NOT_REQUIRED
    ).JsonObj;
    */

    cpr::Response r = cpr::Get(

        cpr::Url{ "https://games.roblox.com/v1/games/" + std::to_string(this->m_UniverseID) + "/social-links/list" },
        cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "User-Agent", USER_AGENT } },
        cpr::Cookies{ {".ROBLOSECURITY", this->m_Cookie} }
    );

    nlohmann::json res = nlohmann::json::parse(r.text);

    return Responses::GameSocialLinks(res);
}

std::vector<Responses::Badge> RoPP::Game::get_game_badges(const std::string& sort, int limit)
{
    /*
    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://badges.roblox.com/v1/universes/" + std::to_string(this->m_UniverseID) + "/badges?sortOrder=" + sort + "&limit=" + std::to_string(limit),
        "GET"
    ).JsonObj;
    */

    cpr::Response r = cpr::Get(

		cpr::Url{ "https://badges.roblox.com/v1/universes/" + std::to_string(this->m_UniverseID) + "/badges?sortOrder=" + sort + "&limit=" + std::to_string(limit) },
		cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "User-Agent", USER_AGENT } }
	);

    nlohmann::json res = nlohmann::json::parse(r.text);

    std::vector<Responses::Badge> badges;
    for (auto& badge : res["data"])
    {
        badges.emplace_back(badge);
    }

    return badges;
}

int64_t RoPP::Game::create_game_pass(const std::string& name, const std::string& description, long price, const std::string& icon_path)
{
    cpr::Response r = cpr::Post(
        cpr::Url{ "https://apis.roblox.com/game-passes/v1/game-passes" },
        cpr::Header{ {"Content-Type", "multipart/form-data"}, { "Referer", "https://www.roblox.com/" }, { "x-csrf-token", get_csrf() }, { "User-Agent", USER_AGENT } },
        cpr::Cookies{ {".ROBLOSECURITY", this->m_Cookie} },
        cpr::Multipart{ {"Name", name}, { "Description", description }, { "UniverseId", std::to_string(this->m_UniverseID) }, { "File", cpr::File{icon_path} } }
    );

    return nlohmann::json::parse(r.text)["gamePassId"];
}


int RoPP::Game::update_gamepass_price(int64_t gamepass_id, int new_price)
{
    cpr::Response r = cpr::Post(
        cpr::Url{ "https://apis.roblox.com/game-passes/v1/game-passes/" + std::to_string(gamepass_id) + "/details" },
        cpr::Header{ {"Content-Type", "multipart/form-data"}, { "Referer", "https://www.roblox.com/" }, { "x-csrf-token", get_csrf() }, { "User-Agent", USER_AGENT } },
        cpr::Cookies{ {".ROBLOSECURITY", this->m_Cookie} },
        cpr::Multipart{ {"IsForSale", "true"}, { "Price", std::to_string(new_price) } }
    );

    return r.status_code;
}