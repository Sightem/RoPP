#include "request.hpp"
#include "json.hpp"
using json = nlohmann::json;

namespace helper 
{
    struct WebResponse 
    {
        json JsonObj;
        Response Res;
    };

    WebResponse makeRobloxRequest(std::string Url,
        std::string Method,
        std::string Cookie,
        json Body = {},
        headers_t Additional_headers = {},
        cookies_t Additional_cookies = {});
}