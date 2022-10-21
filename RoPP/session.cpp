#include "ropp.h"
#include "../include/request.hpp"

/*
* @brief gets the CSRF token of the cookie, used in many end points
* @return CSRF token
*/
std::string RoPP::Session::GetCSRF()
{
    Request req("https://auth.roblox.com/v1/authentication-ticket");
    req.set_cookie(".ROBLOSECURITY", this->Cookie);
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.post();

    return res.headers["x-csrf-token"];
}

/*
* @brief gets the auth ticket of the cookie, used to launch into games
* @return Authentication ticket
*/
std::string RoPP::Session::GetAuthTicket()
{
    Request req("https://auth.roblox.com/v1/authentication-ticket");
    req.set_cookie(".ROBLOSECURITY", this->Cookie);
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.post();

    string csrfToken = res.headers["x-csrf-token"];
    req.set_header("x-csrf-token", csrfToken);

    res = req.post();
    string ticket = res.headers["rbx-authentication-ticket"];
    return ticket;
}

/*
* @brief gets the UID of the cookie
* @return UID
*/
long RoPP::Session::GetUserID()
{
    Request req("https://users.roblox.com/v1/users/authenticated");
    req.set_cookie(".ROBLOSECURITY", this->Cookie);
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data)["id"];
}

/*
* @brief gets the username of the cookie
* @return Username
*/
std::string RoPP::Session::GetUsername()
{
    Request req("https://users.roblox.com/v1/users/authenticated");
    req.set_cookie(".ROBLOSECURITY", this->Cookie);
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data)["name"];
}

/*
* @brief sets the cookie of the session
* @param cookie
*/
void RoPP::Session::SetCookie(std::string cookie)
{
    this->Cookie = cookie;
}

/*
* @brief gets the birth date of the cookie
* @return Birth date json object
*/
json RoPP::Session::GetBirthDate()
{
    Request req("https://accountinformation.roblox.com/v1/birthdate");
    req.set_cookie(".ROBLOSECURITY", this->Cookie);
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data);
}

/*
* @brief gets the description of the cookie
* @return Description
*/
std::string RoPP::Session::GetDescription()
{
    Request req("https://accountinformation.roblox.com/v1/description");
    req.set_cookie(".ROBLOSECURITY", this->Cookie);
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data)["description"];
}