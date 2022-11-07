#include <string>

#include "../include/json.hpp"
#include "../include/responses.h"

using json = nlohmann::json;
using std::string;
using namespace Responses;

namespace RoPP
{
    class User
    {
        public:

            Responses::User GetUser();
            Timestamp GetCreationDate();

            FriendsResponse GetFriends(string Sort="Alphabetical");
            FollowersResponse GetFollowers(string Sort="Asc", int Limit=10);
            FollowingsResponse GetFollowings(string Sort="Asc", int Limit=10);
            UserExperienceResponse GetExperiences(string Sort="Asc", int Limit=10);
            UserFavoriteExperiences GetFavoriteExperiences(string Sort="Asc", int Limit=10);
            PastUsernames GetPastUsernames(string Sort="Asc", int Limit=10);
            json GetGroups();
            json GetBadges();
            json GetPresence();
            json GetPrimaryGroup();
            json GetCurrentlyWearing();
            json GetAvatar();
            json GetInventory(string AssetType, string Sort="Asc", int Limit=10);
            
            int GetFriendsCount();
            int GetFollowingsCount();
            int GetFollowersCount();
            int GetGroupsCount();
            int GetBadgesCount();

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
            std::string ReadCookie();

            FriendsOnlineResponse GetFriendsOnline();
            json GetBirthDate();
            json GetPhoneInfo();
            json BuyAsset(long AssetID);
            json GetFriendRequests(string Sort="Asc", int Limit=10);
            json GetAvatar();
            json GetTrades(string tradeStatusType="Inbound", string Sort="Asc", int Limit=10);
            json GetTradeInfo(long TradeID);
            json CanTradeWith(long UserID);

            int GetFriendsCount();
            int GetTradeCount(string TradeStatusType="Inbound");

            long GetUserID();
            long GetRobuxBalance();

            bool HasPremium();
            bool IsFavoriteGame(int PlaceID);
            
            //post requests

            double UnlockPin(int Pin);

            int SendTradeRequest(long TargetUID, json UserOffer, json UserRequest);

            bool SendFriendRequest(long UID);
            bool LockPin();

            void SetFavoriteGame(int PlaceID, bool Favorite);
            void SetDescription(string Description);
            void SetGender(string Gender);
            void ChangePassword(string OldPassword, string NewPassword);
            void AcceptFriendRequest(long UID);
            void DeclineFriendRequest(long UID);
            void DeclineAllFriendRequests();
            void BlockUser(long UID);
            void UnblockUser(long UID);
            void AcceptTrade(long TradeID);
            void DeclineTrade(long TradeID);

            void SetCookie(string Cookie);

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
            AssetInfo GetAssetInfo();
            ResaleData GetResaleData();
            Resellers GetAssetResellers(string Sort="Asc", int Limit=10);
    
            void SetCookie(string Cookie);
    
            Asset(long AID)
            {
                this->AID = AID;
            }
    
            Asset(long AID, string Cookie)
            {
                this->AID = AID;
                this->Cookie = Cookie;
            }
    
        private:
            long AID = 0;
            std::string Cookie;
    };

    class Other
    {
        public:

            json UserSearch(string Keyword, int Limit=10);

            json GroupSearch(string Keyword, bool prioritizeExactMatch=true, int Limit=10);

            std::string ValidateUsername(string Username);

            int GetGameUniverseID(int PlaceID);
    };
}