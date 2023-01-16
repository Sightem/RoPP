#include "../include/json.hpp"
#include "../include/ropp.h"
#include <iostream>
#include <string>

int main()
{
    RoPP::User user(5725475);

    Responses::User UserResponse = user.GetUser();

    std::cout << "User Name: " << UserResponse.Username << std::endl;
    std::cout << "User Display name: " << UserResponse.DisplayName << std::endl;
    std::cout << "User Creation Date: " <<  UserResponse.Created.ToISO8601() << std::endl;
    std::cout << "User Description: " << UserResponse.Description << std::endl;

    Responses::FriendsResponse FriendsResponse = user.GetFriends();
    std::cout << "Friends: ";
    for (int i = 0; i < FriendsResponse.Friends.size(); i++)
    {
        if (i == FriendsResponse.Friends.size() - 1)
        {
            std::cout << FriendsResponse.Friends[i].Username;
        }
        else
        {
            std::cout << FriendsResponse.Friends[i].Username << ", ";
        }
    }
    
    std::cout << std::endl;

    std::vector<Responses::GroupWithRole> UserGroupsResponse = user.GetGroups();
    std::cout << "Groups: ";

    for (int i = 0; i < UserGroupsResponse.size(); i++)
    {
        if (i == UserGroupsResponse.size() - 1)
        {
            std::cout << UserGroupsResponse[i].group.Name;
        }
        else
        {
            std::cout << UserGroupsResponse[i].group.Name << ", ";
        }
    }

    std::cout << std::endl;

    std::vector<Responses::Experience> UserExperienceResponse = user.GetExperiences();
    std::cout << "Experiences: ";
    for (int i = 0; i < UserExperienceResponse.size(); i++)
    {
        if (i == UserExperienceResponse.size() - 1)
        {
            std::cout << UserExperienceResponse[i].Name;
        }
        else
        {
            std::cout << UserExperienceResponse[i].Name << ", ";
        }
    }

    std::cout << std::endl;

    std::vector<Responses::Badge> UserBadgesResponse = user.GetBadges();
    std::cout << "Badges: ";
    for (int i = 0; i < UserBadgesResponse.size(); i++)
    {
        if (i == UserBadgesResponse.size() - 1)
        {
            std::cout << UserBadgesResponse[i].Name;
        }
        else
        {
            std::cout << UserBadgesResponse[i].Name << ", ";
        }
    }
    
    std::cout << std::endl;
}