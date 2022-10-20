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

            json GetFriends(string Sort="Alphabetical");
            json GetFriendsOnline();
            int GetFriendsCount();
            json GetFollowers(string Sort="Asc", int Limit=10);
            int GetFollowersCount();
            json GetFollowings(string Sort="Asc", int Limit=10);
            int GetFollowingsCount();
            json GetGroups();
            int GetGroupsCount();
            


            User(int UID)
            {
                this->UID = UID;
            }

        private:
            int UID;
    };
}