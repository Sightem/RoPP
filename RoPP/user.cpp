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