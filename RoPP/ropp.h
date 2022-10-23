#include <string>

#include "../include/json.hpp"

using json = nlohmann::json;
using std::string;

namespace RoPP
{
    class User
    {
        public:
            /*
            * @brief gets the username of the user
            * @return username
            */
            std::string GetUsername();

            /*
            * @brief gets the display name of the user
            * @return display name
            */
            std::string GetDisplayName();

            /*
            * @brief gets the description of the user
            * @return description
            */
            std::string GetDescription();

            /*
            * @brief gets the creation date of the user
            * @return creation date
            */
            std::string GetCreationDate();

            /*
            * @brief gets the friends of the user
            * @return friends json object
            */
            json GetFriends(string Sort="Alphabetical");

            /*
            * @brief gets the online friends of the user
            * @return online friends json object
            */
            json GetFriendsOnline();
            
            /*
            * @brief gets the followers of the user
            * @return followers json object
            */
            json GetFollowers(string Sort="Asc", int Limit=10);
            
            /*
            * @brief gets the followings of the user
            * @return followings json object
            */
            json GetFollowings(string Sort="Asc", int Limit=10);
            
            /*
            * @brief gets the experiences created by user
            * @return experiences json object
            */
            json GetExperiences(string Sort="Asc", int Limit=10);

            /*
            * @brief gets the favorite games of the user
            * @return favorite games json object
            */
            json GetFavoriteGames(string Sort="Asc", int Limit=10);
            
            /*
            * @brief gets the username historty of the user
            * @return username history json object
            */
            json GetPastUsernames(string Sort="Asc", int Limit=10);
            
            /*
            * @brief gets the groups of the user (very verbose)
            * @return groups json object
            */
            json GetGroups();
            
            /*
            * @brief gets the awarded badges of the user
            * @return awarded badges json object
            */
            json GetBadges();

            /*
            * @brief gets the presence data of the user
            * @return presence json object
            */
            json GetPresence();

            /*
            * @brief gets the primary group of the user
            * @return primary group json object
            */
            json GetPrimaryGroup();
            
            /*
            * @brief gets the friends count of the user
            * @return friends count
            */
            int GetFriendsCount();
            
            /*
            * @brief gets the following count of the user
            * @return followings count
            */
            int GetFollowingsCount();
            
            /*
            * @brief gets the followers count of the user
            * @return followers count
            */
            int GetFollowersCount();
            
            /*
            * @brief gets the groups count of the user
            * @return groups count 
            */
            int GetGroupsCount();
            
            /*
            * @brief gets the badge count of the user
            * @return badge count
            */
            int GetBadgesCount();
            
            /*
            * @brief gets the experience count of the user
            * @return experience count
            */
            int GetExperiencesCount();

            User(long UID)
            {
                this->UID = UID;
            }

        private:
            long UID = 0;
    };

    class Session
    {
        public:
            /*
            * @brief gets the CSRF token of the cookie
            * @return CSRF token
            */
            std::string GetCSRF();

            /*
            * @brief gets the auth ticket of the cookie
            * @return Authentication ticket
            */
            std::string GetAuthTicket();

            /*
            * @brief gets the username of the cookie
            * @return Username
            */
            std::string GetUsername();

            /*
            * @brief gets the description of the cookie
            * @return Description
            */
            std::string GetDescription();

            /*
            * @brief gets the birthdate of the cookie
            * @return Birthdate json object
            */
            json GetBirthDate();

            /*
            * @brief gets the verified phone number of the cookie
            * @return Verified phone number information json object
            */
            json GetPhoneInfo();

            /*
            * @brief gets friend requests of the cookie
            * @return Friend requests json object
            */
            json GetFriendRequests(string Sort="Asc", int Limit=10);

            /*
            * @brief gets the friend count of the cookie
            * @return Friend count
            */
            int GetFriendsCount();

            /*
            * @brief gets the UID of the cookie
            * @return UID
            */
            long GetUserID();
            
            /*
            * @brief gets the robux balance of the cookie
            * @return robux balance
            */
            long GetRobuxBalance();

            /*
            * @brief checks if the cookie has Roblox premium
            * @return true if premium, false if not
            */
            bool HasPremium();

            /*
            * @brief sets the cookie to a new cookie
            * @param cookie
            */
            void SetCookie(std::string Cookie);

            Session(string Cookie)
            {
                this->Cookie = Cookie;
            }

        private:
            std::string Cookie;
    };


    class Group
    {
        public:

        std::string GetGroupName();
        std::string GetGroupDescription();
        std::string GetOwnerName();
        std::string GetOwnerDisplayName();

        json GetGroupInfo();
        json GetGroupOwner();
        json GetGroupShout();
        json GetNameHistory(string Sort="Asc", int Limit=10);
        json GetGroupWall(string Sort="Asc", int Limit=10);

        long GetMemberCount();
        long GetOwnerID();

        bool IsGroupLocked();
        bool IsPublicEntryAllowed();
        bool IsBuildersClubOnly();

        Group(long GID)
        {
            this->GID = GID;
        }

        private:
            long GID = 0;
    };
    class Other
    {
        public:
            /*
            * @brief Search for users given a keyword
            * @return JSON of users
            */
            json UserSearch(string Keyword, int Limit=10);

            json GroupSearch(string Keyword, bool prioritizeExactMatch=true, int Limit=10);
    };
}