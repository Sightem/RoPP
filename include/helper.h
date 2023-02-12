#pragma once

#include "request.hpp"
#include "json.hpp"

#define USER_AGENT "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/109.0.0.0 Safari/537.36"
#define CSRF_REQUIRED 1
#define CSRF_NOT_REQUIRED 0
using CSRF_t = bool;

using json = nlohmann::json;
using ordered_json = nlohmann::ordered_json;

//@Nowilltolife
namespace Helper
{
    struct WebResponse
    {
        ordered_json JsonObj;
        Response Res;
    };

    WebResponse MakeAuthedRobloxRequest
    (
        std::string Url,
        std::string Method,
        std::string Cookie,
        CSRF_t CSRF,
        ordered_json Body = {},
        headers_t Additional_headers = {},
        cookies_t Additional_cookies = {}
    );

    WebResponse MakeRobloxRequest
    (
        std::string Url,
        std::string Method,
        ordered_json Body = {},
        headers_t Additional_headers = {},
        cookies_t Additional_cookies = {}
    );
}