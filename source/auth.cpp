#include "../include/RoPP/ropp.h"
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
    std::string csrf = this->get_csrf();

    cpr::Response r = cpr::Post(
        cpr::Url{ "https://auth.roblox.com/v1/authentication-ticket" },
        cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "x-csrf-token", csrf } },
        cpr::Cookies{ {".ROBLOSECURITY", this->m_Cookie} }
    );

    return r.header["rbx-authentication-ticket"];
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