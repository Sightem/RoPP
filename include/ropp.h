#pragma once

#include <string>

#include "../include/json.hpp"
#include "../include/responses.h"
#include "../include/helper.h"

using json = nlohmann::json;
using std::string;

namespace RoPP
{
    class Auth
    {
        public:
            std::string GetCSRF();
            std::string GetAuthTicket();
            std::string ReadCookie();
            
            void SetCookie(std::string_view Cookie);
        protected:
            std::string Cookie;

        private:
            void CookieCheck();
    };

    class Avatar : public Auth
    {
        public:
            std::vector<long> GetCurrentlyWearing(long UserID);
            Responses::AvatarResponse GetAvatar(long UserID);
            Responses::OutfitDetailsResponse GetOutfitDetails(long OutfitID);
            Responses::GetOutfitsResponse GetOutfits(long UserID, int Page=1, int ItemsPerPage=25, bool IsEditable=false);

            bool SetBodyColors(json Colors);
            bool SetBodyScales(json Scales);
            bool SetPlayerAvatarType(std::string_view AvatarType);
            bool RemoveAsset(long AssetID);
            bool WearAsset(long AssetID);
    };
    
    class Asset : public Auth
    {
        public:
            json BuyAsset();
            //TODO: buy limited

            Responses::AssetInfo GetAssetInfo();
            Responses::ResaleData GetResaleData();
            std::vector<Responses::ResellerData> GetAssetResellers(string Sort="Asc", int Limit=10);


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

    class Chat : public Auth
    {
        public:
            Responses::ConversationAddResponse AddUsersToConversation(std::vector<long> UserIDs);
            Responses::ChatSettings GetChatSettings();
            std::vector<Responses::ChatMessage> GetMessages(int PageSize=10, std::string ExclusiveStartMessageID="");
            Responses::ChatConversationsResponse GetConversations(std::vector<long> ConversationIDs={});
            std::vector<Responses::RolloutFeature> GetRolloutFeatures(std::vector<std::string> FeatureNames);
            int GetUnreadConversationCount();
            std::vector<Responses::ChatConversationWithMessages> GetUnreadMessages(std::vector<long> ConversationIDs={}, int PageSize=10);
            std::vector<Responses::ChatConversation> GetUserConversations(int PageNumber=1, int PageSize=10);
            bool mark_conversation_as_read(std::string EndMessageId);
            bool mark_conversation_as_seen(std::vector<long> ConversationIDs={});
            std::vector<Responses::ChatConversationWithMessages> multi_get_latest_messages(std::vector<long> ConversationIDs, int PageSize=10);

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

    class Game : public Auth
    {
        public:
            Responses::PlaceInfoResponse GetPlaceInfo();
            std::vector<Responses::GamePass> GetGamepasses(string Sort="Asc", int Limit=10);
            std::vector<Responses::Badge> GetGameBadges(string Sort="Asc", int Limit=10);
            Responses::ExperienceVotes GetVotes();
            Responses::DeveloperProductCreateResponse CreateDeveloperProduct(string Name, string Description, long Price, long IconImageAssetID=0);
            std::vector<Responses::GameInstance> GetGameInstances(string Type="Public", string Sort="Asc", int Limit=100, bool ExcludeFullGames=false);
            Responses::GameSocialLinks GetSocialLinks();

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

    class Group : public Auth
    {
        public:
            Responses::Group GetGroupInfo();
            std::vector<Responses::GroupNamehistory> GetNameHistory(string Sort="Asc", int Limit=10);
            std::vector<Responses::GroupWallPost> GetGroupWall(string Sort="Asc", int Limit=10);
            std::vector<Responses::GroupExperience> GetGames(string AccessFilter="All", string Sort="Asc", int Limit=10);

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

    class Trade : public Auth
    {
        public:
            std::vector<Responses::TradeData> GetTrades(std::string tradeStatusType="Inbound", std::string Sort="Asc", int Limit=10);
            json GetTradeInfo(long TradeID);
            Responses::CanTradeWithResponse CanTradeWith(long UserID);
            //TODO: counter
            int SendTradeRequest(long TargetUID, json UserOffer, json UserRequest);
            void AcceptTrade(long TradeID);
            void DeclineTrade(long TradeID);

        public:
            Trade(long TradeID, std::string_view Cookie)
            {
                this->TradeID = TradeID;
                this->Cookie = Cookie;
            }

            Trade(std::string_view Cookie)
            {
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

    class User
    {
        public:
            Responses::User GetUser();

            std::vector<Responses::User> GetFriends(string Sort="Alphabetical");
            std::vector<Responses::User> GetFollowers(string Sort="Asc", int Limit=10);
            std::vector<Responses::User> GetFollowings(string Sort="Asc", int Limit=10);
            std::vector<Responses::Experience> GetExperiences(string Sort="Asc", int Limit=10);
            std::vector<Responses::Experience> GetFavoriteExperiences(string Sort="Asc", int Limit=10);
            std::vector<std::string> GetPastUsernames(string Sort="Asc", int Limit=10);
            std::vector<Responses::GroupWithRole> GetGroups();
            std::vector<Responses::Badge> GetBadges();
            Responses::Group GetPrimaryGroup();
            std::vector<Responses::InventoryAsset>  GetInventory(std::vector<string> AssetType, string Sort="Asc", int Limit=10);

            bool CanInventoryBeViewed();

        public:
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


    class Session : public Auth
    {
        public:

            //get requests


            Responses::User GetUser();
            
            std::string GetDescription();

            std::vector<Responses::FriendsOnline> GetFriendsOnline();
            Responses::BirthdateResponse GetBirthDate();
            Responses::PhoneInfo GetPhoneInfo();
            Responses::FriendRequestsResponse GetFriendRequests(string Sort="Asc", int Limit=10);

            int GetFriendsCount();

            long GetRobuxBalance();
            long GetUserID();

            bool HasPremium();
            bool IsFavoriteGame(int PlaceID);
            
            //post requests

            double UnlockPin(int Pin);

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

            Session(std::string_view Cookie)
            {
                this->Cookie = Cookie;
            }
    };

    class Other : public Auth
    {
        public:

            std::vector<Responses::UserPresence> GetUsersPresence(std::vector<long> UIDs);

            std::vector<Responses::SearchedUser> UserSearch(string Keyword, int Limit=10);

            json GroupSearch(string Keyword, bool prioritizeExactMatch=true, int Limit=10);

            std::string ValidateUsername(string Username);

            long GetGameUniverseID(long PlaceID);
    };
}