#include <string>

#include "ropp.h"
#include "../include/request.hpp"

/*
* @brief gets the friends of the user
* @return friends json object
*/
json RoPP::User::GetFriends(string Sort)
{
    Request req("https://friends.roblox.com/v1/users/" + std::to_string(this->UID) + "/friends?userSort=" + Sort);
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data);
}

/*
* @brief gets the followers of the user
* @return followers json object
*/
json RoPP::User::GetFollowers(string Sort, int Limit)
{
    Request req("https://friends.roblox.com/v1/users/" + std::to_string(this->UID) + "/followers?sortOrder=" + Sort + "&limit=" + std::to_string(Limit));
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data);
}

/*
* @brief gets the followings of the user
* @return followings json object
*/
json RoPP::User::GetFollowings(string Sort, int Limit)
{
    Request req("https://friends.roblox.com/v1/users/" + std::to_string(this->UID) + "/followings?sortOrder=" + Sort + "&limit=" + std::to_string(Limit));
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data);
}

/*
* @brief gets the friends count of the user
* @return friends count
*/
int RoPP::User::GetFriendsCount()
{
    Request req("https://friends.roblox.com/v1/users/" + std::to_string(this->UID) + "/friends/count");
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data)["count"];
}

/*
* @brief gets the followers count of the user
* @return followers count
*/
int RoPP::User::GetFollowersCount()
{
    Request req("https://friends.roblox.com/v1/users/" + std::to_string(this->UID) + "/followers/count");
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data)["count"];
}

/*
* @brief gets the followings count of the user
* @return followings count
*/
int RoPP::User::GetFollowingsCount()
{
    Request req("https://friends.roblox.com/v1/users/" + std::to_string(this->UID) + "/followings/count");
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data)["count"];
}

/*
* @brief gets the friends online of the user
* @return friends online json object
*/
json RoPP::User::GetFriendsOnline()
{
    Request req("https://friends.roblox.com/v1/users/" + std::to_string(this->UID) + "/friends/online");
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data);
}

/*
* @brief gets the username of the user
* @return username
*/
std::string RoPP::User::GetUsername()
{
    Request req("https://users.roblox.com/v1/users/" + std::to_string(this->UID));
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data)["name"];
}

/*
* @brief gets the display name of the user
* @return display name
*/
std::string RoPP::User::GetDisplayName()
{
    Request req("https://users.roblox.com/v1/users/" + std::to_string(this->UID));
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data)["displayName"];
}

/*
* @brief gets the description of the user
* @return description
*/
std::string RoPP::User::GetDescription()
{
    Request req("https://users.roblox.com/v1/users/" + std::to_string(this->UID));
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data)["description"];
}

/*
* @brief gets the groups of the user
* @return groups json object
*/
json RoPP::User::GetGroups()
{
    Request req("https://groups.roblox.com/v1/users/" + std::to_string(this->UID) + "/groups/roles");
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data);
}

/*
* @brief gets the count of groups the user is in
* @return count of groups
*/
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

/*
* @brief gets the badges of the user
* @return badges json object
*/
json RoPP::User::GetBadges()
{
    Request req("https://badges.roblox.com/v1/users/" + std::to_string(this->UID) + "/badges");
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data);
}

/*
* @brief gets the count of badges the user has
* @return count of badges
*/
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

/*
* @brief gets the creation date of the user
* @return creation date
*/
std::string RoPP::User::GetCreationDate()
{
    Request req("https://users.roblox.com/v1/users/" + std::to_string(this->UID));
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data)["created"];
}

/*
* @brief gets the experiences of the user
* @return experiences json object
*/
json RoPP::User::GetExperiences(string Sort, int limit)
{
    Request req("https://games.roblox.com/v2/users/" + std::to_string(this->UID) + "/games?sortOrder=" + Sort + "&limit=" + std::to_string(limit));
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data);
}
/*
* @brief gets the count of experiences the user has
* @return count of experiences
*/
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

/*
* @brief gets the favorite games of the user
* @return favorites json object
*/
json RoPP::User::GetFavoriteGames(string Sort, int limit)
{
    Request req("https://games.roblox.com/v1/users/" + std::to_string(this->UID) + "/favorites/games?sortOrder=" + Sort + "&limit=" + std::to_string(limit));
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data);
}