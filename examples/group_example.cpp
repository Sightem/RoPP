#include "RoPP/ropp.h"
#include "RoPP/request.hpp"
#include <iostream>
#include <string>

int main()
{
    RoPP::Group group(1103278);

    Responses::Group groupResponse = group.get_group_info();

    std::cout << "Group Name: " << groupResponse.name << std::endl;
    std::cout << "Group Description: " << groupResponse.description << std::endl;
    std::cout << "Group Shout: " << groupResponse.shout.body << std::endl;
    std::cout << "Group Member Count: " << groupResponse.member_count << std::endl;
    std::cout << "Group Owner ID: " << groupResponse.owner.user_id << std::endl;
    std::cout << "Group Owner Name: " << groupResponse.owner.username << std::endl;
    std::cout << "Group Owner Display Name: " << groupResponse.owner.display_name << std::endl;
    std::cout << "Is Public Entry Allowed: " << groupResponse.is_public_entry_allowed << std::endl;
    std::cout << "Is Builders Club Only: " << groupResponse.is_builders_club_only << std::endl;
    
    std::cout << "Group Wall: ";
    std::vector<Responses::GroupWallPost> group_wall = group.get_group_wall("Asc", 10);

    for (auto& post : group_wall)
    {
        std::cout << post.body << " (" << post.created.to_ISO8601() << ")" << std::endl;
    }
}