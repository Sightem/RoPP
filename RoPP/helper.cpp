#include "../include/request.hpp"
#include "../include/json.hpp"
#include "../include/helper.h"
using json = nlohmann::json;

//@Nowilltolife
[[maybe_unused]] Helper::WebResponse Helper::MakeAuthedRobloxRequest(
                       std::string Url,
                       std::string Method,
                       std::string Cookie,
                       bool CSRF,
                       json Body,
                       headers_t Additional_headers,
                       cookies_t Additional_cookies)
{
    if (Cookie.empty()) throw std::logic_error("Cookie is empty! (MakeAuthedRobloxRequest)");

/*
    Request req("https://auth.roblox.com/v1/authentication-ticket");
    req.set_header("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/108.0.0.0 Safari/537.36");
    req.set_cookie(".ROBLOSECURITY", Cookie);
    req.set_header("Referer", "https://www.roblox.com/");
    req.set_header("Accept", "application/json");
    req.set_header("Content-Type", "application/json");
    req.initalize();
    Response res = req.post();

    req.set_header("x-csrf-token", res.headers["x-csrf-token"]);
    */

    //get the csrf token if specified
    
    Request req("https://auth.roblox.com/v1/authentication-ticket");
    Response res;
    req.set_header("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/108.0.0.0 Safari/537.36");
    req.set_cookie(".ROBLOSECURITY", Cookie);
    req.set_header("Referer", "https://www.roblox.com/");
    req.set_header("Accept", "application/json");
    req.set_header("Content-Type", "application/json");
    req.initalize();
    if (CSRF)
    {
        res = req.post();
        req.set_header("x-csrf-token", res.headers["x-csrf-token"]);
    }

    req.set_url(Url);
    req.set_data(Body.dump());
    for (auto [key, value] : Additional_headers)
        req.set_header(key, value);
    for (auto [key, value] : Additional_cookies)
        req.set_cookie(key, value);

    res = req.request(Method);

    if (res.data.find("errors") != std::string::npos)
    {
        json errors = json::parse(res.data)["errors"];
        json errorObject = errors.at(0);
        throw std::logic_error(errorObject["message"].get<std::string>() + " (" + std::to_string(errorObject["code"].get<int>()) + ")");
    }

    return {json::parse(res.data), res};
}

[[maybe_unused]] Helper::WebResponse Helper::MakeRobloxRequest(
                       std::string Url,
                       std::string Method,
                       json Body,
                       headers_t Additional_headers,
                       cookies_t Additional_cookies)
{
    Request req(Url);
    req.set_header("User-Agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/108.0.0.0 Safari/537.36");
    req.set_header("Referer", "https://www.roblox.com/");
    req.set_header("Accept", "application/json");
    req.set_header("Content-Type", "application/json");

    for (auto [key, value] : Additional_headers)
        req.set_header(key, value);
    for (auto [key, value] : Additional_cookies)
        req.set_cookie(key, value);
    req.set_data(Body.dump());

    req.initalize();

    Response res = req.request(Method);

    if (res.data.find("errors") != std::string::npos)
    {
        json errors = json::parse(res.data)["errors"];
        json errorObject = errors.at(0);
        throw std::logic_error(errorObject["message"].get<std::string>() + " (" + std::to_string(errorObject["code"].get<int>()) + ")");
    }

    return {json::parse(res.data), res};
}