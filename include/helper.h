#pragma once

#include "request.hpp"
#include "json.hpp"
using json = nlohmann::json;

//@Nowilltolife
namespace Helper
{
    struct WebResponse
    {
        json JsonObj;
        Response Res;
    };

    WebResponse MakeAuthedRobloxRequest
    (
        std::string Url,
        std::string Method,
        std::string Cookie,
        bool CSRF,
        json Body = {},
        headers_t Additional_headers = {},
        cookies_t Additional_cookies = {}
    );

    WebResponse MakeRobloxRequest
    (
        std::string Url,
        std::string Method,
        json Body = {},
        headers_t Additional_headers = {},
        cookies_t Additional_cookies = {}
    );
}