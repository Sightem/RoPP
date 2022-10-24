#include "ropp.h"
#include "../include/request.hpp"


json RoPP::Other::UserSearch(string Keyword, int Limit)
{
    Request req("https://users.roblox.com/v1/users/search?keyword=" + Keyword + "&limit=" + std::to_string(Limit));
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data);
}

json RoPP::Other::GroupSearch(string Keyword, bool prioritizeExactMatch, int Limit)
{
    Request req("https://groups.roblox.com/v1/groups/search?keyword=" + Keyword + "&prioritizeExactMatch=" + std::to_string(prioritizeExactMatch) + "&limit=" + std::to_string(Limit));
    req.initalize();
    Response res = req.get();

    return json::parse(res.data);
}

std::string RoPP::Other::ValidateUsername(std::string Username)
{
    Request req("https://auth.roblox.com/v2/usernames/validate?request.username=" + Username + "&request.birthday=1970-10-10");
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data)["message"];
}