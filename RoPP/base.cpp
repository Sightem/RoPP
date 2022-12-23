#include "../include/ropp.h"
#include "../include/helper.h"
#include "../include/request.hpp"
#include "../include/responses.h"

std::string RoPP::Base::GetCSRF()
{
    CookieCheck();

    Request req("https://auth.roblox.com/v1/authentication-ticket");
    req.set_cookie(".ROBLOSECURITY", this->Cookie);
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.post();
    return res.headers["x-csrf-token"];
}

std::string RoPP::Base::GetAuthTicket()
{
    CookieCheck();
    
    Request req("https://auth.roblox.com/v1/authentication-ticket");
    req.set_cookie(".ROBLOSECURITY", this->Cookie);
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.post();

    std::string csrfToken = res.headers["x-csrf-token"];
    req.set_header("x-csrf-token", csrfToken);

    res = req.post();
    std::string ticket = res.headers["rbx-authentication-ticket"];
    return ticket;
}

void RoPP::Base::CookieCheck()
{
    if (this->Cookie.empty())
    {
        throw std::runtime_error("Cookie is empty");
    }
}

void RoPP::Base::SetCookie(std::string_view Cookie)
{
    this->Cookie = Cookie;
}

std::string RoPP::Base::ReadCookie()
{
    return this->Cookie;
}