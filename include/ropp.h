#pragma once

#include <string>
#include <regex>

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
            std::vector<int64_t> get_currently_wearing(int64_t user_id);
            Responses::AvatarResponse get_avatar(int64_t user_id);
            Responses::OutfitDetailsResponse get_outfit_details(int64_t outfit_id);
            Responses::GetOutfitsResponse get_outfits(int64_t user_id, int page=1, int items_per_page=25, bool is_editable=false);

            bool set_body_colors(json colors);
            bool set_body_scales(json scales);
            bool set_player_avatar_type(std::string_view avatar_type);
            bool remove_asset(int64_t asset_id);
            bool wear_asset(int64_t asset_id);
    };
    
    class Asset : public Auth
    {
        public:
            json buy_asset();
            //TODO: buy limited

            Responses::AssetInfo get_asset_info();
            Responses::ResaleData get_resale_data();
            std::vector<Responses::ResellerData> get_asset_resellers(std::string sort="Asc", int limit=10);


        public:
            Asset(int64_t asset_id, std::string_view cookie)
            {
                this->m_AssetID = asset_id;
                this->m_Cookie = cookie;
            }

            Asset(int64_t asset_id)
            {
                this->m_AssetID = asset_id;
            }

            void set_asset_id(int64_t asset_id)
            {
                this->m_AssetID = asset_id;
            }

        private:
            int64_t m_AssetID = 0;
    };

    class Chat : public Auth
    {
        public:
            Responses::ConversationAddResponse add_users_to_conversation(std::vector<int64_t> user_ids);
            Responses::ChatSettings get_chat_settings();
            std::vector<Responses::ChatMessage> get_messages(int32_t page_size=10, std::string exclusive_start_messageid="");
            Responses::ChatConversationsResponse get_conversations(std::vector<int64_t> conversation_ids={});
            std::vector<Responses::RolloutFeature> get_rollout_features(std::vector<std::string> feature_names);
            int64_t get_unread_conversation_count();
            std::vector<Responses::ChatConversationWithMessages> get_unread_messages(std::vector<int64_t> conversation_ids={}, int32_t page_size=10);
            std::vector<Responses::ChatConversation> get_user_conversations(int32_t page_number=1, int32_t page_size=10);
            bool mark_conversation_as_read(std::string end_message_id);
            bool mark_conversation_as_seen(std::vector<int64_t> conversation_ids={});
            std::vector<Responses::ChatConversationWithMessages> multi_get_latest_messages(std::vector<int64_t> conversation_ids, int32_t page_size=10);
            Responses::RemoveFromConversationResponse remove_from_conversation(int64_t user_id);
            Responses::RenameGroupConversationResponse rename_group_conversation(std::string NewTitle);
            Responses::SendMessageResponse send_message(std::string message, bool is_experience_invite=false, std::vector<std::string> decorators={""});
            std::string update_user_typing_status(bool is_typing);
            Responses::OneToOneConversationResponse start_one_to_one_conversation(int64_t user_id);
            Responses::StartGroupConversationResponse start_group_conversation(std::vector<int64_t> user_id, std::string title);

        public:
            Chat(int64_t conversation_id, std::string_view cookie)
            {
                this->m_ConversationID = conversation_id;
                this->m_Cookie = cookie;
            }

            Chat(int64_t conversation_id)
            {
                this->m_ConversationID = conversation_id;
            }

            Chat(std::string_view cookie)
            {
                this->m_Cookie = cookie;
            }

            Chat()
            {
                this->m_ConversationID = 0;
            }

            void SetConversationID(long conversation_id)
            {
                this->m_ConversationID = conversation_id;
            }

        private:
            int64_t m_ConversationID = 0;
    };

    class Game : public Auth
    {
        public:
            Responses::PlaceInfoResponse get_place_info();
            std::vector<Responses::GamePass> get_gamepasses(const std::string& sort="Asc", int limit=10);
            std::vector<Responses::Badge> get_game_badges(const std::string& ort="Asc", int limit=10);
            Responses::ExperienceVotes get_votes();
            Responses::DeveloperProductCreateResponse create_developer_product(const std::string& name, const std::string& description, long price, int64_t icon_image_asset_id=0);
            std::vector<Responses::GameInstance> get_game_instances(const std::string& type="Public", const std::string& sort="Asc", int limit=100, bool exclude_full_games=false);
            Responses::GameSocialLinks get_social_links();

            int64_t create_game_pass(const std::string& name, const std::string& description, long price, const std::string& icon_path);
            int update_gamepass_price(int64_t gamepass_id, int new_price);

            int64_t get_universe_id();


        public:
            Game(int64_t PlaceID, std::string_view cookie)
            {
                this->m_PlaceID = PlaceID;
                this->m_UniverseID = get_universe_id();
                this->m_Cookie = cookie;
            }

            Game(int64_t PlaceID)
            {
                this->m_PlaceID = PlaceID;
                this->m_UniverseID = get_universe_id();
            }

            void set_place_id(int64_t PlaceID)
            {
                this->m_PlaceID = PlaceID;
                this->m_UniverseID = get_universe_id();
            }

        private:
            int64_t m_PlaceID = 0;
            int64_t m_UniverseID = 0;
    };

    class Group : public Auth
    {
        public:
            std::vector<Responses::GroupExperience> get_group_games(const std::string& access_filter="All", const std::string& sort="Asc", int32_t limit=10);
            Responses::AuditPage get_audit_log(const std::string& action_type="All", int64_t user_id=0, const std::string& sort="Asc", int32_t limit=10);
            std::vector<Responses::GroupNamehistory> get_name_history(const std::string& sort="Asc", int32_t limit=10);
            std::vector<Responses::GroupWallPost> get_group_wall(const std::string& sort="Asc", int32_t limit=10);
            Responses::ChangeRoleResponse change_role(int64_t user_id, int change);
            Responses::ChangeRoleResponse demote(int64_t user_id);
            Responses::GroupRole get_user_role(int64_t user_id);
            Responses::GroupRoles get_group_roles();
            Responses::Group get_group_info();

            void delete_group_wall_posts_by_user(int64_t user_id);
            void set_group_role(int64_t user_id, int64_t role_id);
            void delete_group_wall_post(int64_t post_id);
            void remove_user(int64_t user_id);
        
        public:
            Group(int64_t group_id, std::string_view cookie)
            {
                this->m_GroupID = group_id;
                this->m_Cookie = cookie;
            }

            Group(int64_t group_id)
            {
                this->m_GroupID = group_id;
            }

            Group()
            {
                this->m_GroupID = 0;
            }

            void SetGroupID(int64_t group_id)
            {
                this->m_GroupID = group_id;
            }

        private:
            int64_t m_GroupID = 0;
    };

    class Trade : public Auth
    {
        public:
            std::vector<Responses::TradeData> get_trades(const std::string& trade_status_type="Inbound", const std::string& sort="Asc", int32_t limit=10);
            json get_trade_info(int64_t trade_id);
            Responses::CanTradeWithResponse can_trade_with(int64_t user_id);
            //TODO: counter
            int send_trade_request(int64_t target_uid, json user_offer, json user_request);
            void accept_trade(int64_t trade_id);
            void decline_trade(int64_t trade_id);

        public:
            Trade(std::string_view cookie)
            {
                this->m_Cookie = cookie;
            }
    };

    class User
    {
        public:
            Responses::User get_user();

            std::vector<Responses::User> get_friends(const std::string& sort="Alphabetical");
            std::vector<Responses::User> get_followers(const std::string& sort="Asc", int limit=10);
            std::vector<Responses::User> get_followings(const std::string&  sort="Asc", int limit=10);
            std::vector<Responses::Experience> get_experiences(const std::string& sort="Asc", int limit=10);
            std::vector<Responses::Experience> get_favorite_experiences(const std::string& sort="Asc", int limit=10);
            std::vector<std::string> get_past_usernames(const std::string& sort="Asc", int limit=10);
            std::vector<Responses::GroupWithRole> get_groups();
            std::vector<Responses::Badge> get_badges();
            Responses::Group get_primary_group();
            std::vector<Responses::InventoryAsset> get_inventory(const std::vector<std::string>& asset_type, const std::string& sort="Asc", int limit=10);

            bool can_inventory_be_viewed();

        public:
            User(int64_t UID)
            {
                this->user_id = UID;
            }

            User()
            {
                this->user_id = 0;
            }

            void set_uid(int64_t UID)
            {
                this->user_id = UID;
            }

        private:
            int64_t user_id = 0;
    };

    class Thumbnail
    {
        public:
            std::vector<Responses::Thumbnail> get_avatar_headshots(const std::vector<int64_t>& user_ids, const std::string& size="48x48", const std::string& format="Png", bool is_circular=false);
    };


    class Session : public Auth
    {
        public:

            //get requests


            Responses::User get_user();
            
            std::string get_description();

            std::vector<Responses::FriendsOnline> get_friends_online();
            Responses::BirthdateResponse get_birth_date();
            Responses::PhoneInfo get_phone_info();
            Responses::FriendRequestsResponse get_friend_requests(const std::string& sort="Asc", int limit=10);

            int get_friends_count();

            long get_robux_balance();
            int64_t get_user_id();

            bool has_premium();
            bool is_favorite_game(int64_t place_id);
            
            //post requests

            double unlock_pin(int pin);

            bool send_friend_request(int64_t user_id);
            bool lock_pin();

            void set_favorite_game(int64_t place_id, bool favorite);
            void set_description(const std::string& description);
            void set_gender(std::string gender);
            void change_password(const std::string& old_password, const std::string& new_password);
            void accept_friend_request(int64_t user_id);
            void decline_friend_request(int64_t user_id);
            void decline_all_friend_requests();
            void block_user(int64_t user_id);
            void unblock_user(int64_t user_id);

            Session(std::string_view cookie)
            {
                this->m_Cookie = cookie;
            }
    };

    class Other : public Auth
    {
        public:
            std::vector<Responses::UserPresence> get_users_presence(const std::vector<int64_t>& user_ids);
            std::vector<Responses::SearchedUser> user_search(std::string keyword, int32_t limit=10);
            
            Responses::GamePassProductInfoResponse get_gamepass_product_info(int64_t gamepass_id);
            
            std::string validate_username(const std::string& username);
            std::string get_username_from_cookie(const std::string& cookie);
            
            json group_search(std::string keyword, bool prioritize_exact_match=true, int32_t limit=10);

            int64_t get_game_universe_id(int64_t place_id);
            int64_t get_uid_from_cookie(const std::string& cookie);
            int64_t get_user_id_from_username(const std::string& username);
            
            void buy_gamepass(int64_t gamepass_id);
    };
}