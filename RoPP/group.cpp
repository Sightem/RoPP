#include "../include/ropp.h"
#include "../include/helper.h"
#include "../include/request.hpp"

Responses::Group RoPP::Group::GetGroupInfo()
{
    json res = Helper::MakeRobloxRequest
    (
        "https://groups.roblox.com/v1/groups/" + std::to_string(this->GroupID),
        "GET"
    ).JsonObj;

    return Responses::Group(res);
}

std::vector<Responses::GroupNamehistory> RoPP::Group::GetNameHistory(string Sort, int Limit)
{
    json res = Helper::MakeRobloxRequest
    (
        "https://groups.roblox.com/v1/groups/" + std::to_string(this->GroupID) + "/name-history?sortOrder=" + Sort + "&limit=" + std::to_string(Limit),
        "GET"
    ).JsonObj;

    std::vector<Responses::GroupNamehistory> NameHistory;
    for (auto& element : res["data"])
    {
        NameHistory.emplace_back(element);
    }

    return NameHistory;
}

std::vector<Responses::GroupWallPost> RoPP::Group::GetGroupWall(std::string Sort, int Limit)
{
    json res = Helper::MakeRobloxRequest
    (
        "https://groups.roblox.com/v1/groups/" + std::to_string(this->GroupID) + "/wall/posts?sortOrder=" + Sort + "&limit=" + std::to_string(Limit),
        "GET"
    ).JsonObj;

    std::vector<Responses::GroupWallPost> posts;
    for (auto& element : res["data"])
    {
        posts.emplace_back(element);
    }

    return posts;
}

std::vector<Responses::GroupExperience> RoPP::Group::GetGames(string AccessFilter, string Sort, int Limit)
{
    json res = Helper::MakeRobloxRequest
    (
        "https://games.roblox.com/v2/groups/" + std::to_string(this->GroupID) + "/games?accessFilter=" + AccessFilter + "&sortOrder=" + Sort + "&limit=" + std::to_string(Limit),
        "GET"
    ).JsonObj;

    std::vector<Responses::GroupExperience> Experiences;
    for (auto& element : res["data"])
    {
        Experiences.emplace_back(element);
    }

    return Experiences;
}

void RoPP::Group::delete_group_wall_post(int64_t PostID)
{
    Helper::MakeAuthedRobloxRequest
    (
        "https://groups.roblox.com/v1/groups/" + std::to_string(this->GroupID) + "/wall/posts/" + std::to_string(PostID),
        "DELETE",
        this->Cookie,
        CSRF_REQUIRED
    );
}

void RoPP::Group::delete_group_wall_posts_by_user(int64_t UserID)
{
    Helper::MakeAuthedRobloxRequest
    (
        "https://groups.roblox.com/v1/groups/" + std::to_string(this->GroupID) + "/wall/users/" + std::to_string(UserID) + "/posts",
        "DELETE",
        this->Cookie,
        CSRF_REQUIRED
    );
}

Responses::GroupRoles RoPP::Group::get_group_roles()
{
    json res = Helper::MakeRobloxRequest
    (
        "https://groups.roblox.com/v1/groups/" + std::to_string(this->GroupID) + "/roles",
        "GET"
    ).JsonObj;

    return Responses::GroupRoles(res);
}

void RoPP::Group::set_group_role(int64_t UserID, int64_t RoleID)
{
    json body = 
    {
        {"roleId", RoleID}
    };

    Helper::MakeAuthedRobloxRequest
    (
        "https://groups.roblox.com/v1/groups/" + std::to_string(this->GroupID) + "/users/" + std::to_string(UserID),
        "PATCH",
        this->Cookie,
        CSRF_REQUIRED,
        body
    );
}