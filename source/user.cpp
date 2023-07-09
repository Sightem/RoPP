#include "../include/RoPP/ropp.h"
#include "../include/RoPP/responses.h"
#include <cpr/cpr.h>

std::vector<Responses::Friend> RoPP::User::get_friends(const std::string& sort)
{
    cpr::Response r = cpr::Get
    (
		cpr::Url{ "https://friends.roblox.com/v1/users/" + std::to_string(this->user_id) + "/friends?userSort=" + sort },
		cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "User-Agent", USER_AGENT } }
	);
    nlohmann::json res = nlohmann::json::parse(r.text);

    std::vector<Responses::Friend> Friends;

    for (auto& element : res["data"])
    {
		Friends.emplace_back(element);
	}

    return Friends;
}

std::vector<Responses::Friend> RoPP::User::get_followers(const std::string& sort, int limit)
{
    cpr::Response r = cpr::Get(
        cpr::Url{ "https://friends.roblox.com/v1/users/" + std::to_string(this->user_id) + "/followers?sortOrder=" + sort + "&limit=" + std::to_string(limit) },
		cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "User-Agent", USER_AGENT } }
	);

    nlohmann::json res = nlohmann::json::parse(r.text);

	std::vector<Responses::Friend> Followers;

    for (auto& element : res["data"])
    {
		Followers.emplace_back(element);
	}

	return Followers;
}

std::vector<Responses::Friend> RoPP::User::get_followings(const std::string& sort, int limit)
{
    cpr::Response r = cpr::Get(
        cpr::Url{ "https://friends.roblox.com/v1/users/" + std::to_string(this->user_id) + "/followings?sortOrder=" + sort + "&limit=" + std::to_string(limit) },
        cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "User-Agent", USER_AGENT } }
    );

    nlohmann::json res = nlohmann::json::parse(r.text);

    std::vector<Responses::Friend> Followings;

    for (auto& element : res["data"])
    {
		Followings.emplace_back(element);
	}

    return Followings;
}

std::vector<Responses::GroupWithRole> RoPP::User::get_groups()
{
    cpr::Response r = cpr::Get(
		cpr::Url{ "https://groups.roblox.com/v1/users/" + std::to_string(this->user_id) + "/groups/roles" },
		cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "User-Agent", USER_AGENT } }
	);

    nlohmann::json res = nlohmann::json::parse(r.text);

    std::vector<Responses::GroupWithRole> Groups;

    for (auto& element : res["data"])
    {
        Groups.emplace_back(element);
    }

    return Groups;
}

std::vector<Responses::Badge> RoPP::User::get_badges()
{
    cpr::Response r = cpr::Get(
        cpr::Url{ "https://badges.roblox.com/v1/users/" + std::to_string(this->user_id) + "/badges" },
        cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "User-Agent", USER_AGENT } }
    );
    nlohmann::json res = nlohmann::json::parse(r.text);

    std::vector<Responses::Badge> Badges;

    for (auto& element : res["data"])
    {
		Badges.emplace_back(element);
	}

    return Badges;
}

std::vector<Responses::Experience> RoPP::User::get_experiences(const std::string& sort, int limit)
{
    cpr::Response r = cpr::Get(
        cpr::Url{ "https://games.roblox.com/v2/users/" + std::to_string(this->user_id) + "/games?sortOrder=" + sort + "&limit=" + std::to_string(limit) },
		cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "User-Agent", USER_AGENT } }
	);
    nlohmann::json res = nlohmann::json::parse(r.text);

	std::vector<Responses::Experience> Experiences;

    for (auto& element : res["data"])
    {
		Experiences.emplace_back(element);
	}

	return Experiences;
}

std::vector<Responses::Experience> RoPP::User::get_favorite_experiences(const std::string& sort, int limit)
{
    cpr::Response r = cpr::Get(
        cpr::Url{ "https://games.roblox.com/v2/users/" + std::to_string(this->user_id) + "/favorite/games?sortOrder=" + sort + "&limit=" + std::to_string(limit) },
        cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "User-Agent", USER_AGENT } }
    );
    nlohmann::json res = nlohmann::json::parse(r.text);

    std::vector<Responses::Experience> Experiences;

    for (auto& element : res["data"])
    {
		Experiences.emplace_back(element);
	}

    return Experiences;
}

std::vector<std::string> RoPP::User::get_past_usernames(const std::string& sort, int limit)
{
    cpr::Response r = cpr::Get(
		cpr::Url{ "https://users.roblox.com/v1/users/" + std::to_string(this->user_id) + "/username-history?limit=" + std::to_string(limit) + "&sortOrder=" + sort },
		cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "User-Agent", USER_AGENT } }
	);

    nlohmann::json res = nlohmann::json::parse(r.text);

	std::vector<std::string> PastUsernames;

    for (auto& element : res["data"])
    {
		PastUsernames.emplace_back(element["name"]);
	}

	return PastUsernames;
}

Responses::Group RoPP::User::get_primary_group()
{
    cpr::Response r = cpr::Get(
		cpr::Url{ "https://groups.roblox.com/v1/users/" + std::to_string(this->user_id) + "/groups/primary/role" },
		cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "User-Agent", USER_AGENT } }
	);

	nlohmann::json res = nlohmann::json::parse(r.text);

	return Responses::Group(res);
}

std::vector<Responses::InventoryAsset> RoPP::User::get_inventory(const std::vector<std::string>& AssetType, const std::string& Sort, int Limit)
{
    std::string AssetTypeString = "";
    for (size_t i = 0; i < AssetType.size(); i++)
    {
        AssetTypeString += AssetType[i];

        if (i != AssetType.size() - 1)
            AssetTypeString += ",";
    }

    cpr::Response r = cpr::Get(
        cpr::Url{ "https://inventory.roblox.com/v2/users/" + std::to_string(this->user_id) + "/inventory?assetTypes=" + AssetTypeString + "&sortOrder=" + Sort + "&limit=" + std::to_string(Limit) },
		cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "User-Agent", USER_AGENT } }
	);
    nlohmann::json res = nlohmann::json::parse(r.text);

    std::vector<Responses::InventoryAsset> Assets;

    for (auto& element : res["data"])
    {
        Assets.emplace_back(element);
    }

    return Assets;
}

bool RoPP::User::can_inventory_be_viewed()
{
    cpr::Response r = cpr::Get(
        cpr::Url{ "https://inventory.roblox.com/v1/users/" + std::to_string(this->user_id) + "/can-view-inventory" },
        cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "User-Agent", USER_AGENT } }
    );

    nlohmann::json res = nlohmann::json::parse(r.text);

    return res["canView"];
}

Responses::ShorthandUser RoPP::User::get_user()
{
    cpr::Response r = cpr::Get(
		cpr::Url{ "https://users.roblox.com/v1/users/" + std::to_string(this->user_id) },
		cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "User-Agent", USER_AGENT } }
	);

    nlohmann::json res = nlohmann::json::parse(r.text);

    return Responses::ShorthandUser(res);
}