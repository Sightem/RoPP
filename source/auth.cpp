#include "../include/RoPP/ropp.h"
#include "../include/RoPP/helper.h"
#include "../include/RoPP/request.hpp"
#include "../include/RoPP/responses.h"
#include "cpr/cpr.h"

std::string RoPP::Auth::get_csrf()
{
    cookie_check();

    cpr::Response r = cpr::Post(
        cpr::Url{ "https://auth.roblox.com/v1/authentication-ticket" },
        cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" } },
        cpr::Cookies{ {".ROBLOSECURITY", this->m_Cookie} }
    );

    return r.header["x-csrf-token"];
}

std::string RoPP::Auth::get_auth_ticket()
{
    cookie_check();
    
    Request req("https://auth.roblox.com/v1/authentication-ticket");
    req.set_cookie(".ROBLOSECURITY", this->m_Cookie);
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.post();

    std::string csrfToken = res.headers["x-csrf-token"];
    req.set_header("x-csrf-token", csrfToken);

    res = req.post();
    std::string ticket = res.headers["rbx-authentication-ticket"];
    return ticket;
}

void RoPP::Auth::cookie_check()
{
    if (this->m_Cookie.empty())
    {
        throw std::runtime_error("Cookie is empty");
    }
}

void RoPP::Auth::set_cookie(std::string_view cookie)
{
    this->m_Cookie = cookie;
}

std::string RoPP::Auth::read_cookie()
{
    return this->m_Cookie;
}