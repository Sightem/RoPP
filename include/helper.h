#pragma once

#include "request.hpp"
#include "json.hpp"
using json = nlohmann::json;

#define USER_AGENT "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/109.0.0.0 Safari/537.36"
#define CSRF_REQUIRED 1
#define CSRF_NOT_REQUIRED 0

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