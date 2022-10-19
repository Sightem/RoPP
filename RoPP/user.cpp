#include <string>

#include "ropp.h"
#include "../include/request.hpp"

json RoPP::User::GetFriends(string Sort)
{
    Request req("https://friends.roblox.com/v1/users/" + std::to_string(this->UID) + "/friends");
    req.set_header("Referer", "https://www.roblox.com/");
    req.initalize();
    Response res = req.get();

    return json::parse(res.data);
}