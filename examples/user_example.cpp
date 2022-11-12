#include "../include/json.hpp"
#include "../RoPP/ropp.h"
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
        std::cout << FriendsResponse.Friends[i].Username << std::endl;
    }

    std::cout << std::endl;

    Responses::UserGroupsResponse UserGroupsResponse = user.GetGroups();
    std::cout << "Groups: ";
    for (int i = 0; i < UserGroupsResponse.Groups.size(); i++)
    {
        std::cout << UserGroupsResponse.Groups[i].Name << ", ";
    }

    std::cout << std::endl;

    Responses::UserExperienceResponse UserExperienceResponse = user.GetExperiences();
    std::cout << "Experiences: ";
    for (int i = 0; i < UserExperienceResponse.Experiences.size(); i++)
    {
        std::cout << UserExperienceResponse.Experiences[i].Name << ", ";
    }

    std::cout << std::endl;

    Responses::UserBadgesResponse UserBadgesResponse = user.GetBadges();
    std::cout << "Badges: ";
    for (int i = 0; i < UserBadgesResponse.Badges.size(); i++)
    {
        std::cout << UserBadgesResponse.Badges[i].Name << ", ";
    }

    std::cout << std::endl;
}