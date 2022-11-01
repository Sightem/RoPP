#include "../RoPP/ropp.h"
#include "../include/request.hpp"
#include <iostream>
#include <string>

int main()
{
    RoPP::Group group(1103278);

    std::cout << "Group Name: " << group.GetGroupName() << std::endl;
    std::cout << "Group Description: " << group.GetGroupDescription() << std::endl;
    std::cout << "Group Shout: " << group.GetGroupShout() << std::endl;
    std::cout << "Group Member Count: " << group.GetMemberCount() << std::endl;
    std::cout << "Group Owner ID: " << group.GetOwnerID() << std::endl;
    std::cout << "Group Owner Name: " << group.GetOwnerName() << std::endl;
    std::cout << "Group Owner Display Name: " << group.GetOwnerDisplayName() << std::endl;
    std::cout << "Group Name History: " << group.GetNameHistory() << std::endl;
    std::cout << "Group Wall: " << group.GetGroupWall() << std::endl;
    std::cout << "Group Games: " << group.GetGames() << std::endl;
    std::cout << "Is Public Entry Allowed: " << group.IsPublicEntryAllowed() << std::endl;
    std::cout << "Is Builders Club Only: " << group.IsBuildersClubOnly() << std::endl;
}