#include <string>

#include "ropp.h"
#include "../include/request.hpp"

json RoPP::User::GetFriends(string Sort)
{
    Request req("https://friends.roblox.com/v1/users/" + std::to_string(this->UID) + "/friends?userSort=" + Sort);
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data);
}

json RoPP::User::GetFollowers(string Sort, int Limit)
{
    Request req("https://friends.roblox.com/v1/users/" + std::to_string(this->UID) + "/followers?sortOrder=" + Sort + "&limit=" + std::to_string(Limit));
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data);
}

json RoPP::User::GetFollowings(string Sort, int Limit)
{
    Request req("https://friends.roblox.com/v1/users/" + std::to_string(this->UID) + "/followings?sortOrder=" + Sort + "&limit=" + std::to_string(Limit));
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data);
}

int RoPP::User::GetFriendsCount()
{
    Request req("https://friends.roblox.com/v1/users/" + std::to_string(this->UID) + "/friends/count");
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data)["count"];
}

int RoPP::User::GetFollowersCount()
{
    Request req("https://friends.roblox.com/v1/users/" + std::to_string(this->UID) + "/followers/count");
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data)["count"];
}

int RoPP::User::GetFollowingsCount()
{
    Request req("https://friends.roblox.com/v1/users/" + std::to_string(this->UID) + "/followings/count");
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data)["count"];
}

json RoPP::User::GetFriendsOnline()
{
    Request req("https://friends.roblox.com/v1/users/" + std::to_string(this->UID) + "/friends/online");
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data);
}

std::string RoPP::User::GetUsername()
{
    Request req("https://users.roblox.com/v1/users/" + std::to_string(this->UID));
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data)["name"];
}

std::string RoPP::User::GetDisplayName()
{
    Request req("https://users.roblox.com/v1/users/" + std::to_string(this->UID));
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data)["displayName"];
}

std::string RoPP::User::GetDescription()
{
    Request req("https://users.roblox.com/v1/users/" + std::to_string(this->UID));
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data)["description"];
}

json RoPP::User::GetGroups()
{
    Request req("https://groups.roblox.com/v1/users/" + std::to_string(this->UID) + "/groups/roles");
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data);
}

int RoPP::User::GetGroupsCount()
{
    Request req("https://groups.roblox.com/v1/users/" + std::to_string(this->UID) + "/groups/roles");
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    //Count the number of groups by counting the occurences of "group" in the string
    std::string word = "group";
    int count = 0;
    for (size_t pos = res.data.find(word); pos != std::string::npos; pos = res.data.find(word, pos + word.length()))
    {
        ++count;
    }

    return count;
}

json RoPP::User::GetBadges()
{
    Request req("https://badges.roblox.com/v1/users/" + std::to_string(this->UID) + "/badges");
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data);
}

int RoPP::User::GetBadgesCount()
{
    Request req("https://badges.roblox.com/v1/users/" + std::to_string(this->UID) + "/badges");
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    std::string word = "awarder";
    int count = 0;
    for (size_t pos = res.data.find(word); pos != std::string::npos; pos = res.data.find(word, pos + word.length()))
    {
        ++count;
    }

    return count;
}

std::string RoPP::User::GetCreationDate()
{
    Request req("https://users.roblox.com/v1/users/" + std::to_string(this->UID));
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data)["created"];
}

json RoPP::User::GetExperiences(string Sort, int limit)
{
    Request req("https://games.roblox.com/v2/users/" + std::to_string(this->UID) + "/games?sortOrder=" + Sort + "&limit=" + std::to_string(limit));
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data);
}

int RoPP::User::GetExperiencesCount()
{
    Request req("https://games.roblox.com/v2/users/" + std::to_string(this->UID) + "/games");
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    std::string word = "name";
    int count = 0;
    for (size_t pos = res.data.find(word); pos != std::string::npos; pos = res.data.find(word, pos + word.length()))
    {
        ++count;
    }

    return count;
}

json RoPP::User::GetFavoriteGames(string Sort, int limit)
{
    Request req("https://games.roblox.com/v1/users/" + std::to_string(this->UID) + "/favorites/games?sortOrder=" + Sort + "&limit=" + std::to_string(limit));
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data);
}

json RoPP::User::GetPresence()
{
    json data = 
    {
        {"userIds", {this->UID}}
    };

    Request req("https://presence.roblox.com/v1/presence/users");
    req.set_header("Referer", "https://www.roblox.com/");
    req.set_header("Content-Type", "application/json");
    req.set_header("Accept", "application/json");
    req.set_data(data.dump());
    req.initalize();
    Response res = req.post();

    return json::parse(res.data);
}
