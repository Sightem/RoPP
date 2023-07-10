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

std::string RoPP::Auth::renew_cookie()
{
    std::string csrf = this->get_csrf();
    std::string auth = this->get_auth_ticket();

    cpr::Response r = cpr::Post(
        cpr::Url{ "https://auth.roblox.com/v1/authentication-ticket/redeem" },
        cpr::Header{
            {"Content-Type", "application/json"},
            { "rbxauthenticationnegotiation", "1" },
            { "user-agent", "Roblox/WinInet" },
            { "origin", "https://www.roblox.com" },
            { "referer", "https://www.roblox.com/my/account" },
            { "x-csrf-token", csrf }
        },
        cpr::Body{
            "{\"authenticationTicket\": \"" + auth + "\"}"
        }
    );

    if (r.status_code == 200)
    {
		this->m_Cookie = r.header["set-cookie"];
		return this->m_Cookie;
	}
    else
    {
		throw std::runtime_error("Failed to renew cookie");
	}
}
