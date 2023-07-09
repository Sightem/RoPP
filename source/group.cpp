#include "../include/RoPP/ropp.h"
#include <cpr/cpr.h>

Responses::Group RoPP::Group::get_group_info()
{
    /*
    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://groups.roblox.com/v1/groups/" + std::to_string(this->m_GroupID),
        "GET"
    ).JsonObj;
    */

    cpr::Response r = cpr::Get(
		cpr::Url{ "https://groups.roblox.com/v1/groups/" + std::to_string(this->m_GroupID) },
		cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "User-Agent", USER_AGENT } }
	);

    nlohmann::json res = nlohmann::json::parse(r.text);

    return Responses::Group(res);
}

std::vector<Responses::GroupNamehistory> RoPP::Group::get_name_history(const std::string& sort, int32_t limit)
{
    /*
    
    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://groups.roblox.com/v1/groups/" + std::to_string(this->m_GroupID) + "/name-history?sortOrder=" + sort + "&limit=" + std::to_string(limit),
        "GET"
    ).JsonObj;

    std::vector<Responses::GroupNamehistory> NameHistory;
    for (auto& element : res["data"])
    {
        NameHistory.emplace_back(element);
    }
    */
    cpr::Response r = cpr::Get(

        cpr::Url{ "https://groups.roblox.com/v1/groups/" + std::to_string(this->m_GroupID) + "/name-history?sortOrder=" + sort + "&limit=" + std::to_string(limit) },
        cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "User-Agent", USER_AGENT } }
    );

    nlohmann::json res = nlohmann::json::parse(r.text);

    std::vector<Responses::GroupNamehistory> NameHistory;
    for (auto& element : res["data"])
    {
		NameHistory.emplace_back(element);
	}

    return NameHistory;
}

std::vector<Responses::GroupWallPost> RoPP::Group::get_group_wall(const std::string& sort, int32_t limit)
{
    /*
    
    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://groups.roblox.com/v1/groups/" + std::to_string(this->m_GroupID) + "/wall/posts?sortOrder=" + sort + "&limit=" + std::to_string(limit),
        "GET"
    ).JsonObj;

    std::vector<Responses::GroupWallPost> posts;
    for (auto& element : res["data"])
    {
        posts.emplace_back(element);
    }

    */

    cpr::Response r = cpr::Get(

		cpr::Url{ "https://groups.roblox.com/v1/groups/" + std::to_string(this->m_GroupID) + "/wall/posts?sortOrder=" + sort + "&limit=" + std::to_string(limit) },
		cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "User-Agent", USER_AGENT } }
	);

    nlohmann::json res = nlohmann::json::parse(r.text);

    std::vector<Responses::GroupWallPost> posts;
    for (auto& element : res["data"])
    {
        posts.emplace_back(element);
    }

    return posts;
}

std::vector<Responses::GroupExperience> RoPP::Group::get_group_games(const std::string& access_filter, const std::string& sort, int32_t limit)
{
    /*
    
    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://games.roblox.com/v2/groups/" + std::to_string(this->m_GroupID) + "/games?accessFilter=" + access_filter + "&sortOrder=" + sort + "&limit=" + std::to_string(limit),
        "GET"
    ).JsonObj;
    */

    cpr::Response r = cpr::Get(

        cpr::Url{ "https://games.roblox.com/v2/groups/" + std::to_string(this->m_GroupID) + "/games?accessFilter=" + access_filter + "&sortOrder=" + sort + "&limit=" + std::to_string(limit) },
        cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "User-Agent", USER_AGENT } }
    );

    nlohmann::json res = nlohmann::json::parse(r.text);

    std::vector<Responses::GroupExperience> Experiences;
    for (auto& element : res["data"])
    {
        Experiences.emplace_back(element);
    }

    return Experiences;
}

void RoPP::Group::delete_group_wall_post(int64_t post_id)
{
    /*
    
    Helper::MakeAuthedRobloxRequest
    (
        "https://groups.roblox.com/v1/groups/" + std::to_string(this->m_GroupID) + "/wall/posts/" + std::to_string(post_id),
        "DELETE",
        this->m_Cookie,
        CSRF_REQUIRED
    );
    */

    cpr::Response r = cpr::Delete(

		cpr::Url{ "https://groups.roblox.com/v1/groups/" + std::to_string(this->m_GroupID) + "/wall/posts/" + std::to_string(post_id) },
		cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "User-Agent", USER_AGENT }, { "X-CSRF-TOKEN", this->get_csrf() } },
        cpr::Cookies{ {".ROBLOSECURITY", this->m_Cookie} }
	);

    nlohmann::json res = nlohmann::json::parse(r.text);
}

void RoPP::Group::delete_group_wall_posts_by_user(int64_t user_id)
{
    /*
    Helper::MakeAuthedRobloxRequest
    (
        "https://groups.roblox.com/v1/groups/" + std::to_string(this->m_GroupID) + "/wall/users/" + std::to_string(user_id) + "/posts",
        "DELETE",
        this->m_Cookie,
        CSRF_REQUIRED
    );
    */

    cpr::Response r = cpr::Delete(

        cpr::Url{ "https://groups.roblox.com/v1/groups/" + std::to_string(this->m_GroupID) + "/wall/users/" + std::to_string(user_id) + "/posts" },
        cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "User-Agent", USER_AGENT }, { "X-CSRF-TOKEN", this->get_csrf() } },
        cpr::Cookies{ {".ROBLOSECURITY", this->m_Cookie} }
    );
}

Responses::GroupRoles RoPP::Group::get_group_roles()
{
    /*
    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://groups.roblox.com/v1/groups/" + std::to_string(this->m_GroupID) + "/roles",
        "GET"
    ).JsonObj;

    return Responses::GroupRoles(res);
    */

    cpr::Response r = cpr::Get(

		cpr::Url{ "https://groups.roblox.com/v1/groups/" + std::to_string(this->m_GroupID) + "/roles" },
		cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "User-Agent", USER_AGENT } }
	);

    nlohmann::json res = nlohmann::json::parse(r.text);

	return Responses::GroupRoles(res);
}

void RoPP::Group::set_group_role(int64_t user_id, int64_t role_id)
{
    json body = 
    {
        {"roleId", role_id}
    };

    /*
    Helper::MakeAuthedRobloxRequest
    (
        "https://groups.roblox.com/v1/groups/" + std::to_string(this->m_GroupID) + "/users/" + std::to_string(user_id),
        "PATCH",
        this->m_Cookie,
        CSRF_REQUIRED,
        body
    );
    */

    cpr::Response r = cpr::Patch(

		cpr::Url{ "https://groups.roblox.com/v1/groups/" + std::to_string(this->m_GroupID) + "/users/" + std::to_string(user_id) },
		cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "User-Agent", USER_AGENT }, { "X-CSRF-TOKEN", this->get_csrf() } },
		cpr::Cookies{ {".ROBLOSECURITY", this->m_Cookie} },
		cpr::Body{ body.dump() }
	);
}

Responses::GroupRole RoPP::Group::get_user_role(int64_t user_id)
{
    /*
    
    ordered_json res = Helper::MakeRobloxRequest
    (
        "https://groups.roblox.com/v1/users/" + std::to_string(user_id) + "/groups/roles",
        "GET"
    ).JsonObj;
    */

    cpr::Response r = cpr::Get(

        cpr::Url{ "https://groups.roblox.com/v1/users/" + std::to_string(user_id) + "/groups/roles" },
        cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "User-Agent", USER_AGENT } }
    );

    nlohmann::json res = nlohmann::json::parse(r.text);

    for (int i = 0; i < res["data"].size(); i++)
    {
        if(res["data"][i]["group"]["id"] == this->m_GroupID)
        {
            return Responses::GroupRole(res["data"][i]["role"]);
        }
    }

    throw std::runtime_error("User is not in the group");
}

Responses::ChangeRoleResponse RoPP::Group::change_role(int64_t user_id, int change)
{
    Responses::GroupRoles roles = this->get_group_roles();
    RoPP::User user(user_id);
    std::vector<Responses::GroupWithRole> user_groups = user.get_groups();

    int64_t user_role = 0;
    for (auto& group : user_groups)
    {
        if (group.group.group_id == this->m_GroupID)
        {
            user_role = group.role.id;
            break;
        }
    }

    int index = 0;
    //get the index of current role in the roles vector
    for (int i = 0; i < roles.roles.size(); i++)
    {
        if (roles.roles[i].id == user_role)
        {
            index = i;
            break;
        }
    }

    //get the index of the role to change to
    int new_index = index + change;

    //check if the new index is out of bounds
    if (new_index < 0 || new_index >= roles.roles.size())
    {
        throw std::runtime_error("The new role is out of bounds");
    }

    //get the new role id
    int64_t new_role = roles.roles[new_index].id;

    //set the new role
    this->set_group_role(user_id, new_role);

    //return the new role
    return Responses::ChangeRoleResponse(roles.roles[index], roles.roles[new_index]);
}

Responses::ChangeRoleResponse RoPP::Group::demote(int64_t user_id)
{
    return this->change_role(user_id, -1);
}

void RoPP::Group::remove_user(int64_t UserID)
{
    /*
    Helper::MakeAuthedRobloxRequest
    (
        "https://groups.roblox.com/v1/groups/" + std::to_string(this->m_GroupID) + "/users/" + std::to_string(UserID),
        "DELETE",
        this->m_Cookie,
        CSRF_REQUIRED
    );
    */

    cpr::Response r = cpr::Delete(

		cpr::Url{ "https://groups.roblox.com/v1/groups/" + std::to_string(this->m_GroupID) + "/users/" + std::to_string(UserID) },
		cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "User-Agent", USER_AGENT }, { "X-CSRF-TOKEN", this->get_csrf() } },
		cpr::Cookies{ {".ROBLOSECURITY", this->m_Cookie} }
	);
}

Responses::AuditPage RoPP::Group::get_audit_log(const std::string& action_type, int64_t user_id, const std::string& sort, int32_t limit)
{
    std::string url = "https://groups.roblox.com/v1/groups/" + std::to_string(this->m_GroupID) + "/audit-log?limit=" + std::to_string(limit) + "&sortOrder=" + sort;

    if (action_type != "")
    {
        url += "&actionType=" + action_type; //in case of all, this wont actually do anything
    }

    if (user_id != 0)
    {
        url += "&userId=" + std::to_string(user_id);
    }

    /*
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        url,
        "GET",
        this->m_Cookie,
        CSRF_REQUIRED
    ).JsonObj;

    return Responses::AuditPage(res);
    */

    cpr::Response r = cpr::Get(

		cpr::Url{ url },
		cpr::Header{ {"Content-Type", "application/json"}, { "Referer", "https://www.roblox.com/" }, { "User-Agent", USER_AGENT }, { "X-CSRF-TOKEN", this->get_csrf() } },
		cpr::Cookies{ {".ROBLOSECURITY", this->m_Cookie} }
	);

    nlohmann::json res = nlohmann::json::parse(r.text);

	return Responses::AuditPage(res);
}
