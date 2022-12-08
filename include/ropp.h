#pragma once

#include <string>

#include "../include/json.hpp"
#include "../include/responses.h"

using json = nlohmann::json;
using std::string;

namespace RoPP
{
    class Base
    {
        public:
            std::string GetCSRF()
            {
                Request req("https://auth.roblox.com/v1/authentication-ticket");
                req.set_cookie(".ROBLOSECURITY", this->Cookie);
                req.set_header("Referer", "https://www.roblox.com/");
                req.initalize();
                Response res = req.post();

                return res.headers["x-csrf-token"];
            }       

        public:
            void SetCookie(std::string_view Cookie)
            {
                this->Cookie = Cookie;
            }

        protected:
            std::string Cookie;
    };

    class Avatar : public Base
    {
        public:
            Responses::CurrentlyWearing GetCurrentlyWearing(long UserID);
            Responses::AvatarResponse GetAvatar(long UserID);
            Responses::OutfitDetailsResponse GetOutfitDetails(long OutfitID);
            Responses::GetOutfitsResponse GetOutfits(long UserID, int Page=1, int ItemsPerPage=25, bool IsEditable=false);

            bool SetBodyColors(json Colors);
            bool SetBodyScales(json Scales);
            bool SetPlayerAvatarType(std::string_view AvatarType);
            bool RemoveAsset(long AssetID);
            bool WearAsset(long AssetID);
    };
    
    class Asset : public Base
    {
        public:
            json BuyAsset(long AssetID);
            //TODO: buy limited

            Responses::AssetInfo GetAssetInfo();
            Responses::ResaleData GetResaleData();
            Responses::Resellers GetAssetResellers(string Sort="Asc", int Limit=10);


        public:
            Asset(long AssetID, std::string_view Cookie)
            {
                this->AssetID = AssetID;
                this->Cookie = Cookie;
            }

            Asset(long AssetID)
            {
                this->AssetID = AssetID;
            }

            void SetAssetID(long AssetID)
            {
                this->AssetID = AssetID;
            }

        private:
            long AssetID = 0;
    };

    class Chat : public Base
    {
        public:
            Chat(long ConversationID, std::string_view Cookie)
            {
                this->ConversationID = ConversationID;
                this->Cookie = Cookie;
            }

            Chat(long ConversationID)
            {
                this->ConversationID = ConversationID;
            }

            Chat()
            {
                this->ConversationID = 0;
            }

            void SetConversationID(long ConversationID)
            {
                this->ConversationID = ConversationID;
            }

        private:
            long ConversationID = 0;
    };

    class Game : public Base
    {
        public:
            Responses::PlaceInfoResponse GetPlaceInfo();
            Responses::ExperienceBadgesResponse GetGamepassInfo(string Sort="Asc", int Limit=10);
            Responses::ExperienceVotes GetVotes();
            Responses::DeveloperProductCreateResponse CreateDeveloperProduct(string Name, string Description, long Price, long IconImageAssetID=0);
            
            //Responses::GameInstancesResponse GetGameInstances();
            //https://games.roblox.com/v1/games/2414851778/servers/Public?sortOrder=Asc&excludeFullGames=false&limit=100
            Responses::GameInstancesResponse GetGameInstances(string Type="Public", string Sort="Asc", int Limit=100, bool ExcludeFullGames=false);
            
            long GetUniverseID();


        public:
            Game(long PlaceID, std::string_view Cookie)
            {
                this->PlaceID = PlaceID;
                this->UniverseID = GetUniverseID();
                this->Cookie = Cookie;
            }

            Game(long PlaceID)
            {
                this->PlaceID = PlaceID;
                this->UniverseID = GetUniverseID();
            }

            void SetPlaceID(long PlaceID)
            {
                this->PlaceID = PlaceID;
            }

        private:
            long PlaceID = 0;
            long UniverseID = 0;
    };

    class Group : public Base
    {
        public:
            Group(long GroupID, std::string_view Cookie)
            {
                this->GroupID = GroupID;
                this->Cookie = Cookie;
            }

            Group(long GroupID)
            {
                this->GroupID = GroupID;
            }

            Group()
            {
                this->GroupID = 0;
            }

            void SetGroupID(long GroupID)
            {
                this->GroupID = GroupID;
            }

        private:
            long GroupID = 0;
    };

    class Trade : public Base
    {
        public:
            Responses::GetTradesResponse GetTrades(string tradeStatusType="Inbound", string Sort="Asc", int Limit=10);
            json GetTradeInfo(long TradeID);
            Responses::CanTradeWithResponse CanTradeWith(long UserID);
            //TODO: counter
            //TODO: send
            void AcceptTrade(long TradeID);
            void DeclineTrade(long TradeID);



        public:
            Trade(long TradeID, std::string_view Cookie)
            {
                this->TradeID = TradeID;
                this->Cookie = Cookie;
            }

            Trade(long TradeID)
            {
                this->TradeID = TradeID;
            }

            void SetTradeID(long TradeID)
            {
                this->TradeID = TradeID;
            }

        private:
            long TradeID = 0;
    };

    class User : public Base
    {
        public:
            User(long UID, std::string_view Cookie)
            {
                this->UID = UID;
                this->Cookie = Cookie;
            }

            User(long UID)
            {
                this->UID = UID;
            }

            User()
            {
                this->UID = 0;
            }

            void SetUID(long UID)
            {
                this->UID = UID;
            }

        private:
            long UID = 0;
    };

/*
    class User
    {
        public:

            Responses::User GetUser();
            Responses::Timestamp GetCreationDate();

            Responses::FriendsResponse GetFriends(string Sort="Alphabetical");
            Responses::FollowersResponse GetFollowers(string Sort="Asc", int Limit=10);
            Responses::FollowingsResponse GetFollowings(string Sort="Asc", int Limit=10);
            Responses::UserExperienceResponse GetExperiences(string Sort="Asc", int Limit=10);
            Responses::UserFavoriteExperiences GetFavoriteExperiences(string Sort="Asc", int Limit=10);
            Responses::PastUsernames GetPastUsernames(string Sort="Asc", int Limit=10);
            Responses::UserGroupsResponse GetGroups();
            Responses::UserBadgesResponse GetBadges();
            Responses::Group GetPrimaryGroup();
            Responses::InventoryResponse GetInventory(std::vector<string> AssetType, string Sort="Asc", int Limit=10);

            bool CanInventoryBeViewed();

            User(long UID)
            {
                this->UID = UID;
            }

        private:
            long UID = 0;
    };
    */

    class Session
    {
        public:

            //get requests


            Responses::User GetUser();
            std::string GetCSRF();
            std::string GetAuthTicket();
            std::string GetDescription();
            std::string ReadCookie();

            Responses::FriendsOnlineResponse GetFriendsOnline();
            Responses::UserPresenceResponse GetUsersPresence(std::vector<long> UIDs);
            Responses::BirthdateResponse GetBirthDate();
            Responses::PhoneInfo GetPhoneInfo();
            Responses::FriendRequestsResponse GetFriendRequests(string Sort="Asc", int Limit=10);

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

            void SetCookie(string Cookie);

            Session(string Cookie)
            {
                this->Cookie = Cookie;
            }

        private:
            std::string Cookie;
    };

/*
    class Group
    {
        public:

            Responses::Group GetGroupInfo();
            Responses::NameHistoryResponse GetNameHistory(string Sort="Asc", int Limit=10);
            Responses::GroupWallResponse GetGroupWall(string Sort="Asc", int Limit=10);
            Responses::GroupExperiencesResponse GetGames(string AccessFilter="All", string Sort="Asc", int Limit=10);

            Group(long GID)
            {
                this->GID = GID;
            }

        private:
            long GID = 0;
    };
*/
    class Other
    {
        public:

            json UserSearch(string Keyword, int Limit=10);

            json GroupSearch(string Keyword, bool prioritizeExactMatch=true, int Limit=10);

            std::string ValidateUsername(string Username);

            long GetGameUniverseID(int PlaceID);
    };
}