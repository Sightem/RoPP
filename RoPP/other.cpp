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