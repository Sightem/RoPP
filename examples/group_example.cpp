#include "../include/ropp.h"
#include "../include/request.hpp"
#include <iostream>
#include <string>

int main()
{
    RoPP::Group group(1103278);

    Responses::Group groupResponse = group.GetGroupInfo();

    std::cout << "Group Name: " << groupResponse.Name << std::endl;
    std::cout << "Group Description: " << groupResponse.Description << std::endl;
    std::cout << "Group Shout: " << groupResponse.Shout.Body << std::endl;
    std::cout << "Group Member Count: " << groupResponse.MemberCount << std::endl;
    std::cout << "Group Owner ID: " << groupResponse.Owner.UID << std::endl;
    std::cout << "Group Owner Name: " << groupResponse.Owner.Username << std::endl;
    std::cout << "Group Owner Display Name: " << groupResponse.Owner.DisplayName << std::endl;
    std::cout << "Is Public Entry Allowed: " << groupResponse.IsPublicEntryAllowed << std::endl;
    std::cout << "Is Builders Club Only: " << groupResponse.IsBuildersClubOnly << std::endl;
    
    std::cout << "Group Wall: ";
    Responses::GroupWallResponse GroupWall = group.GetGroupWall();

    for (auto post : GroupWall.Posts)
    {
         std::cout << post.Body << " (" << post.Created.ToISO8601() << ")" << std::endl;
    }
}