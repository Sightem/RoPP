#include "../include/json.hpp"
#include "../RoPP/ropp.h"
#include <iostream>
#include <string>
#include <fstream>

int main()
{
    RoPP::User user(5725475);

    std::cout << "User Name: " << user.GetUsername() << std::endl;
    std::cout << "User Display name: " << user.GetDisplayName() << std::endl;
    std::cout << "User Description: " << user.GetDescription() << std::endl;
    std::cout << "User Creation Date: " << user.GetCreationDate() << std::endl;

    std::cout << "Get Friends: " << std::endl;
    std::cout << user.GetFriends().dump(4) << std::endl;

    std::cout << "Get Groups: " << std::endl;
    std::cout << user.GetGroups().dump(4) << std::endl;

    std::cout << "User Experiences: " << std::endl;
    std::cout << user.GetExperiences().dump(4) << std::endl;
    
    std::cout << "User Badges: " << std::endl;
    std::cout << user.GetBadges().dump(4) << std::endl;

    //and many more functions, check out the documentation for more info
}