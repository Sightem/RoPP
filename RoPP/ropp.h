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
            json GetExperiences(string Sort="Asc", int Limit=10);
            json GetGroups();
            json GetBadges();

            int GetFriendsCount();
            int GetFollowingsCount();
            int GetFollowersCount();
            int GetGroupsCount();
            int GetBadgesCount();
            int GetExperiencesCount();

            User(long UID)
            {
                this->UID = UID;
            }

        private:
            long UID;
    };

    class Session
    {
        public:
            std::string GetCSRF();
            std::string GetAuthTicket();
            std::string GetUsername();
            std::string GetDescription();

            json GetBirthDate();

            long GetUserID();

            void SetCookie(std::string Cookie);

            Session(string Cookie)
            {
                this->Cookie = Cookie;
            }

        private:
            std::string Cookie;
    };
}