#pragma once

#include <string>

#include "json.hpp"
#include "responses.h"
#include "helper.h"

using json = nlohmann::json;

namespace RoPP
{
    class Auth
    {
        public:
            std::string get_csrf();
            std::string get_auth_ticket();
            std::string read_cookie();
            
            void set_cookie(std::string_view cookie);
        protected:
            std::string m_Cookie;

        private:
            void cookie_check();
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
            std::vector<Responses::ResellerData> GetAssetResellers(std::string Sort="Asc", int Limit=10);


        public:
            Asset(long asset_id, std::string_view cookie)
            {
                this->m_AssetID = asset_id;
                this->m_Cookie = cookie;
            }

            Asset(long asset_id)
            {
                this->m_AssetID = asset_id;
            }

            void SetAssetID(long asset_id)
            {
                this->m_AssetID = asset_id;
            }

        private:
            long m_AssetID = 0;
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
            Responses::RemoveFromConversationResponse remove_from_conversation(long UserID);
            Responses::RenameGroupConversationResponse rename_group_conversation(std::string NewTitle);
            Responses::SendMessageResponse send_message(std::string Message, bool IsExperienceInvite=false, std::vector<std::string> decorators={""});
            std::string update_user_typing_status(bool IsTyping);
            Responses::OneToOneConversationResponse start_one_to_one_conversation(long UserID);
            Responses::StartGroupConversationResponse start_group_conversation(std::vector<long> UserIDs, std::string Title);

        public:
            Chat(long ConversationID, std::string_view cookie)
            {
                this->ConversationID = ConversationID;
                this->m_Cookie = cookie;
            }

            Chat(long ConversationID)
            {
                this->ConversationID = ConversationID;
            }

            Chat(std::string_view cookie)
            {
                this->m_Cookie = cookie;
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
            std::vector<Responses::GamePass> GetGamepasses(std::string Sort="Asc", int Limit=10);
            std::vector<Responses::Badge> GetGameBadges(std::string Sort="Asc", int Limit=10);
            Responses::ExperienceVotes GetVotes();
            Responses::DeveloperProductCreateResponse CreateDeveloperProduct(std::string Name, std::string Description, long Price, long IconImageAssetID=0);
            std::vector<Responses::GameInstance> GetGameInstances(std::string Type="Public", std::string Sort="Asc", int Limit=100, bool ExcludeFullGames=false);
            Responses::GameSocialLinks GetSocialLinks();

            long GetUniverseID();


        public:
            Game(long PlaceID, std::string_view cookie)
            {
                this->PlaceID = PlaceID;
                this->UniverseID = GetUniverseID();
                this->m_Cookie = cookie;
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
            void delete_group_wall_post(int64_t PostID);
            void delete_group_wall_posts_by_user(int64_t UserID);
            Responses::GroupRoles get_group_roles();
            void set_group_role(int64_t UserID, int64_t RoleID);
            Responses::GroupRole get_user_role(int64_t UserID);
            Responses::ChangeRoleResponse change_role(int64_t UserID, int Change);
            Responses::ChangeRoleResponse demote(int64_t UserID);
            void remove_user(int64_t UserID);
            Responses::AuditPage get_audit_log(std::string actionType="All", int64_t UID=0, std::string Sort="Asc", int Limit=10);
            std::vector<Responses::GroupNamehistory> GetNameHistory(std::string Sort="Asc", int Limit=10);
            std::vector<Responses::GroupWallPost> GetGroupWall(std::string Sort="Asc", int Limit=10);
            std::vector<Responses::GroupExperience> GetGames(std::string AccessFilter="All", std::string Sort="Asc", int Limit=10);

        public:
            Group(int64_t GroupID, std::string_view cookie)
            {
                this->GroupID = GroupID;
                this->m_Cookie = cookie;
            }

            Group(int64_t GroupID)
            {
                this->GroupID = GroupID;
            }

            Group()
            {
                this->GroupID = 0;
            }

            void SetGroupID(int64_t GroupID)
            {
                this->GroupID = GroupID;
            }

        private:
            int64_t GroupID = 0;
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
            Trade(long TradeID, std::string_view cookie)
            {
                this->TradeID = TradeID;
                this->m_Cookie = cookie;
            }

            Trade(std::string_view cookie)
            {
                this->m_Cookie = cookie;
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

            std::vector<Responses::User> GetFriends(std::string Sort="Alphabetical");
            std::vector<Responses::User> GetFollowers(std::string Sort="Asc", int Limit=10);
            std::vector<Responses::User> GetFollowings(std::string Sort="Asc", int Limit=10);
            std::vector<Responses::Experience> GetExperiences(std::string Sort="Asc", int Limit=10);
            std::vector<Responses::Experience> GetFavoriteExperiences(std::string Sort="Asc", int Limit=10);
            std::vector<std::string> GetPastUsernames(std::string Sort="Asc", int Limit=10);
            std::vector<Responses::GroupWithRole> GetGroups();
            std::vector<Responses::Badge> GetBadges();
            Responses::Group GetPrimaryGroup();
            std::vector<Responses::InventoryAsset>  GetInventory(std::vector<std::string> AssetType, std::string Sort="Asc", int Limit=10);

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
            Responses::FriendRequestsResponse GetFriendRequests(std::string Sort="Asc", int Limit=10);

            int GetFriendsCount();

            long GetRobuxBalance();
            long GetUserID();

            bool HasPremium();
            bool IsFavoriteGame(int64_t PlaceID);
            
            //post requests

            double UnlockPin(int Pin);

            bool SendFriendRequest(long UID);
            bool LockPin();

            void SetFavoriteGame(int PlaceID, bool Favorite);
            void SetDescription(std::string Description);
            void SetGender(std::string Gender);
            void ChangePassword(std::string OldPassword, std::string NewPassword);
            void AcceptFriendRequest(long UID);
            void DeclineFriendRequest(long UID);
            void DeclineAllFriendRequests();
            void BlockUser(long UID);
            void UnblockUser(long UID);

            Session(std::string_view cookie)
            {
                this->m_Cookie = cookie;
            }
    };

    class Other : public Auth
    {
        public:

            std::vector<Responses::UserPresence> GetUsersPresence(std::vector<long> UIDs);
            std::vector<Responses::SearchedUser> UserSearch(std::string Keyword, int Limit=10);
            json GroupSearch(std::string Keyword, bool prioritizeExactMatch=true, int Limit=10);
            std::string ValidateUsername(std::string Username);
            long GetGameUniverseID(long PlaceID);
            long get_uid_from_cookie(std::string Cookie);
    };
}