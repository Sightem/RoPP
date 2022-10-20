#include <string>

#include "../include/json.hpp"

using json = nlohmann::json;
using std::string;

namespace RoPP
{
    class User
    {
        public:
            std::string GetUsername();
            std::string GetDisplayName();
            std::string GetDescription();
            std::string GetCreationDate();

            json GetFriends(string Sort="Alphabetical");
            json GetFriendsOnline();
            json GetFollowers(string Sort="Asc", int Limit=10);
            json GetFollowings(string Sort="Asc", int Limit=10);
            json GetGroups();
            json GetBadges();

            int GetFriendsCount();
            int GetFollowingsCount();
            int GetFollowersCount();
            int GetGroupsCount();
            int GetBadgesCount();

            json GetExperiences(string Sort="Asc", int Limit=10);
            int GetExperiencesCount();

            User(long UID)
            {
                this->UID = UID;
            }

        private:
            long UID;
    };
}