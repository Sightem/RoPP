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

    Responses::UserGroupsResponse UserGroupsResponse = user.GetGroups();
    std::cout << "Groups: ";
    for (int i = 0; i < UserGroupsResponse.Groups.size(); i++)
    {
        if (i == UserGroupsResponse.Groups.size() - 1)
        {
            std::cout << UserGroupsResponse.Groups[i].Name;
        }
        else
        {
            std::cout << UserGroupsResponse.Groups[i].Name << ", ";
        }
    }

    std::cout << std::endl;

    Responses::UserExperienceResponse UserExperienceResponse = user.GetExperiences();
    std::cout << "Experiences: ";
    for (int i = 0; i < UserExperienceResponse.Experiences.size(); i++)
    {
        if (i == UserExperienceResponse.Experiences.size() - 1)
        {
            std::cout << UserExperienceResponse.Experiences[i].Name;
        }
        else
        {
            std::cout << UserExperienceResponse.Experiences[i].Name << ", ";
        }
    }

    std::cout << std::endl;

    Responses::UserBadgesResponse UserBadgesResponse = user.GetBadges();
    std::cout << "Badges: ";
    for (int i = 0; i < UserBadgesResponse.Badges.size(); i++)
    {
        if (i == UserBadgesResponse.Badges.size() - 1)
        {
            std::cout << UserBadgesResponse.Badges[i].Name;
        }
        else
        {
            std::cout << UserBadgesResponse.Badges[i].Name << ", ";
        }
    }
    
    std::cout << std::endl;
}