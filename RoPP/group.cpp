#include "../include/ropp.h"
#include "../include/helper.h"
#include "../include/request.hpp"

Responses::Group RoPP::Group::GetGroupInfo()
{
    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://groups.roblox.com/v1/groups/" + std::to_string(this->GroupID),
        "GET"
    ).JsonObj;

    return Responses::Group(res);
}

std::vector<Responses::GroupNamehistory> RoPP::Group::GetNameHistory(string Sort, int Limit)
{
    ordered_json res = Helper::MakeRobloxRequest
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
    ordered_json res = Helper::MakeRobloxRequest
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
    ordered_json res = Helper::MakeRobloxRequest
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
    ordered_json res = Helper::MakeRobloxRequest
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
#include <iostream>
Responses::GroupRole RoPP::Group::get_user_role(int64_t UserID)
{
    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://groups.roblox.com/v1/users/" + std::to_string(UserID) + "/groups/roles",
        "GET"
    ).JsonObj;

    for (int i = 0; i < res["data"].size(); i++)
    {
        if(res["data"][i]["group"]["id"] == this->GroupID)
        {
            return Responses::GroupRole(res["data"][i]["role"]);
        }
    }

    throw std::runtime_error("User is not in the group");
}

Responses::ChangeRoleResponse RoPP::Group::change_role(int64_t UserID, int Change)
{
    Responses::GroupRoles roles = this->get_group_roles();
    RoPP::User user(UserID);
    std::vector<Responses::GroupWithRole> user_groups = user.GetGroups();

    int64_t user_role = 0;
    for (auto& group : user_groups)
    {
        if (group.group.GroupID == this->GroupID)
        {
            user_role = group.role.ID;
            break;
        }
    }

    int index = 0;
    //get the index of current role in the roles vector
    for (int i = 0; i < roles.Roles.size(); i++)
    {
        if (roles.Roles[i].id == user_role)
        {
            index = i;
            break;
        }
    }

    //get the index of the role to change to
    int new_index = index + Change;

    //check if the new index is out of bounds
    if (new_index < 0 || new_index >= roles.Roles.size())
    {
        throw std::runtime_error("The new role is out of bounds");
    }

    //get the new role id
    int64_t new_role = roles.Roles[new_index].id;

    //set the new role
    this->set_group_role(UserID, new_role);

    //return the new role
    return Responses::ChangeRoleResponse(roles.Roles[index], roles.Roles[new_index]);
}

Responses::ChangeRoleResponse RoPP::Group::demote(int64_t UserID)
{
    return this->change_role(UserID, -1);
}