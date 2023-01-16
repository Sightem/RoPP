#include "../include/json.hpp"
#include "../include/ropp.h"
#include <iostream>
#include <string>

int main()
{
    RoPP::User user(5725475);

    Responses::User UserResponse = user.GetUser();

    std::string UserResStr
    {
        "User Name: " + UserResponse.Username + "\n"
        "User Display name: " + UserResponse.DisplayName + "\n"
        "User Creation Date: " + UserResponse.Created.ToISO8601() + "\n"
        "User Description: " + UserResponse.Description + "\n"
    };
    std::cout << UserResStr;

    std::vector<Responses::User> FriendsResponse = user.GetFriends();
    std::cout << "Friends: ";
    for (int i = 0; i < FriendsResponse.size(); i++)
    {
        if (i == FriendsResponse.size() - 1)
        {
            std::cout << FriendsResponse[i].Username;
        }
        else
        {
            std::cout << FriendsResponse[i].Username << ", ";
        }
    }
    
    std::cout << '\n';

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

    std::cout << '\n';

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

    std::cout << '\n';

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
    
    std::cout << '\n';
}