#include "../include/request.hpp"
#include "../include/json.hpp"
#include "../include/helper.h"
using json = nlohmann::json;

helper::WebResponse helper::makeRobloxRequest(
                       std::string url,
                       std::string method,
                       std::string cookie,
                       json body,
                       headers_t additional_headers,
                       cookies_t additional_cookies)
{
    Request req("https://auth.roblox.com/v1/authentication-ticket");
    req.set_cookie(".ROBLOSECURITY", cookie);
    req.set_header("Referer", "https://www.roblox.com/");
    req.set_header("Accept", "application/json");
    req.set_header("Content-Type", "application/json");
    req.initalize();
    Response res = req.post();

    req.set_header("x-csrf-token", res.headers["x-csrf-token"]);
    req.set_url(url);
    req.set_data(body.dump());
    for (auto [key, value] : additional_headers)
        req.set_header(key, value);
    for (auto [key, value] : additional_cookies)
        req.set_cookie(key, value);

    if (method == "post") res = req.post();
    else if (method == "get") res = req.get();
    else res = req.request(method);

    return {json::parse(res.data), res};
}