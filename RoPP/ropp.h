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

            json GetInventory(string AssetType, string Sort="Asc", int Limit=10);
            
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

            bool CanInventoryBeViewed();

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

            //get requests

            std::string GetCSRF();
            std::string GetAuthTicket();
            std::string GetUsername();
            std::string GetDescription();

            json GetBirthDate();
            json GetPhoneInfo();
            json GetFriendRequests(string Sort="Asc", int Limit=10);

            int GetFriendsCount();

            long GetUserID();
            long GetRobuxBalance();

            bool HasPremium();
            bool IsFavoriteGame(int PlaceID);
            
            //post requests

            double UnlockPin(int Pin);

            bool LockPin();

            void SetFavoriteGame(int PlaceID, bool Favorite);

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
        json GetGames(string AccessFilter="All", string Sort="Asc", int Limit=10);

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

    class Place
    {
        public:

        std::string GetPlaceName();
        std::string GetPlaceDescription();
        std::string GetCreatorName();
        std::string GetCreatorType();
        std::string GetCreationDate();
        std::string GetUpdatedDate();
        std::string GetGenre();

        json GetPlaceInfo();
        json GetPlaceCreator();
        json GetAllowedGear();
        json GetGamepassInfo(string Sort="Asc", int Limit=10);

        long GetPlaceVisits();
        long GetCurrentPlayers();
        long GetFavoriteCount();
        long GetUpVotes();
        long GetDownVotes();

        int GetUniverseID();
        int GetCreatorID();
        int GetPrice();
        int GetMaxPlayers();

        bool IsCopyable();
        bool IsVIPServerAllowed();

        Place(long PID)
        {
            this->PID = PID;
            this->UniverseID = GetUniverseID();
        }

        private:
            long PID = 0;
            long UniverseID = 0;
    };

    class Asset
    {
        public:

        std::string GetName();
        std::string GetDescription();
        std::string GetType();
        std::string GetCreatorName();
        std::string GetCreatorType();
        std::string GetCreationDate();
        std::string GetUpdatedDate();

        json GetAssetInfo();
        json GetAssetCreator();
        json GetAssetOwners(string Sort="Asc", int Limit=10);

        long GetCreatorID();
        long GetPrice();
        long GetSales();

        bool IsForSale();
        bool IsLimited();
        bool IsLimitedUnique();
        bool IsNew();

        Asset(long AID)
        {
            this->AID = AID;
        }

        private:
            long AID = 0;

            //https://github.com/ro-py/ro.py/blob/284b30dfef4c8117198b961c3b4b47c040da6af4/roblox/assets.py#L21 <3
           std::map<int, std::string> asset_type_names = 
           {
                {1, "Image"},
                {2, "T-Shirt"},
                {3, "Audio"},
                {4, "Mesh"},
                {5, "Lua"},
                {6, "HTML"},
                {7, "Text"},
                {8, "Hat"},
                {9, "Place"},
                {10, "Model"},
                {11, "Shirt"},
                {12, "Pants"},
                {13, "Decal"},
                {16, "Avatar"},
                {17, "Head"},
                {18, "Face"},
                {19, "Gear"},
                {21, "Badge"},
                {22, "Group Emblem"},
                {24, "Animation"},
                {25, "Arms"},
                {26, "Legs"},
                {27, "Torso"},
                {28, "Right Arm"},
                {29, "Left Arm"},
                {30, "Left Leg"},
                {31, "Right Leg"},
                {32, "Package"},
                {33, "YouTubeVideo"},
                {34, "Pass"},
                {35, "App"},
                {37, "Code"},
                {38, "Plugin"},
                {39, "SolidModel"},
                {40, "MeshPart"},
                {41, "Hair Accessory"},
                {42, "Face Accessory"},
                {43, "Neck Accessory"},
                {44, "Shoulder Accessory"},
                {45, "Front Accessory"},
                {46, "Back Accessory"},
                {47, "Waist Accessory"},
                {48, "Climb Animation"},
                {49, "Death Animation"},
                {50, "Fall Animation"},
                {51, "Idle Animation"},
                {52, "Jump Animation"},
                {53, "Run Animation"},
                {54, "Swim Animation"},
                {55, "Walk Animation"},
                {56, "Pose Animation"},
                {59, "LocalizationTableManifest"},
                {60, "LocalizationTableTranslation"},
                {61, "Emote Animation"},
                {62, "Video"},
                {63, "TexturePack"},
                {64, "T-Shirt Accessory"},
                {65, "Shirt Accessory"},
                {66, "Pants Accessory"},
                {67, "Jacket Accessory"},
                {68, "Sweater Accessory"},
                {69, "Shorts Accessory"},
                {70, "Left Shoe Accessory"},
                {71, "Right Shoe Accessory"},
                {72, "Dress Skirt Accessory"},
                {73, "Font Family"},
                {74, "Font Face"},
                {75, "MeshHiddenSurfaceRemoval"}
           };
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

            std::string ValidateUsername(string Username);

            int GetGameUniverseID(int PlaceID);
    };
}