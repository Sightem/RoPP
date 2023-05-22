#pragma once

#include <string>
#include <chrono>
#include "json.hpp"
#include "request.hpp"

using json = nlohmann::json;

namespace Responses
{
    struct Timestamp
    {
        int year, month, day, hour, minute, second;

        const std::string to_ISO8601()
        {
            return std::to_string(year) + "-" + std::to_string(month) + "-" + std::to_string(day);
        }

        std::time_t ToUnix()
        {
            std::tm t = {0};
            t.tm_year = year - 1900;
            t.tm_mon = month - 1;
            t.tm_mday = day;
            t.tm_hour = hour;
            t.tm_min = minute;
            t.tm_sec = second;
            return std::mktime(&t);
        }

        explicit Timestamp(std::string timestamp)
        {
            year = std::stoi(timestamp.substr(0, 4));
            month = std::stoi(timestamp.substr(5, 2));
            day = std::stoi(timestamp.substr(8, 2));
            hour = std::stoi(timestamp.substr(11, 2));
            minute = std::stoi(timestamp.substr(14, 2));
            second = std::stoi(timestamp.substr(17, 2));
        }

        Timestamp() = default;
    };

    struct User
    {
        std::string username;
        std::string display_name;
        std::string description;
        std::string builders_club_membership_type;

        Timestamp created;

        int presence_type;
        int friend_frequent_score;
        int friend_frequent_rank;

        int64_t user_id;

        bool is_online;
        bool is_deleted;
        bool has_verified_badge;
        bool is_banned;

        void PopulateFromUID()
        {
            Request req("https://users.roblox.com/v1/users/" + std::to_string(this->user_id));
            req.set_header("Referer", "https://www.roblox.com/users/" + std::to_string(this->user_id) + "/profile");
            req.set_header("Content", "application/json");
            req.set_header("Accept", "application/json");
            req.initalize();

            Response res = req.get();

            *this = User(json::parse(res.data));
        }

    public:
        explicit User(json j)
        {
            if (j.contains("name"))
                username = j["name"];
            if (j.contains("username"))
                username = j["username"];
            if (j.contains("displayName"))
                display_name = j["displayName"];
            if (j.contains("description") && !(j["description"].is_null()))
                description = j["description"];
            if (j.contains("created"))
                created = Timestamp(j["created"].get<std::string>());
            if (j.contains("presenceType"))
                presence_type = j["presenceType"];
            if (j.contains("friendFrequentScore"))
                friend_frequent_score = j["friendFrequentScore"];
            if (j.contains("friendFrequentRank"))
                friend_frequent_rank = j["friendFrequentRank"];
            if (j.contains("id"))
                user_id = j["id"].get<int64_t>();
            if (j.contains("userId"))
                user_id = j["userId"].get<int64_t>();
            if (j.contains("isOnline"))
                is_online = j["isOnline"];
            if (j.contains("isDeleted"))
                is_deleted = j["isDeleted"];
            if (j.contains("hasVerifiedBadge"))
                has_verified_badge = j["hasVerifiedBadge"];
            if (j.contains("isBanned"))
                is_banned = j["isBanned"];
            if (j.contains("buildersClubMembershipType"))
                builders_club_membership_type = j["buildersClubMembershipType"];
        }

        User() = default;
    };

    struct ShorthandUser
    {
        std::string username;
        std::string display_name;
        int64_t user_id;

        bool has_verified_badge;

        explicit ShorthandUser(json j)
        {
            if (j.contains("name"))
                username = j["name"];
            if (j.contains("username"))
                username = j["username"];
            if (j.contains("displayName"))
                display_name = j["displayName"];
            if (j.contains("id"))
                user_id = j["id"];
            if (j.contains("userId"))
                user_id = j["userId"];
            if (j.contains("hasVerifiedBadge"))
                has_verified_badge = j["hasVerifiedBadge"];
        }

        ShorthandUser() = default;
    };

    struct Experience
    {
        std::string name;
        std::string description;
        std::string creator_type;
        std::string place_type;

        Timestamp created;
        Timestamp updated;

        int64_t creator_id;
        int64_t place_id;
        long place_visits;

        explicit Experience(json j)
        {
            if (j.contains("name") && !(j["name"].is_null()))
                name = j["name"];
            if (j.contains("description") && !(j["description"].is_null()))
                description = j["description"];
            if (j.contains("creator") && !(j["creator"]["type"].is_null()))
                creator_type = j["creator"]["type"];
            if (j.contains("rootPlace") && !(j["rootPlace"]["type"].is_null()))
                place_type = j["rootPlace"]["type"];
            if (j.contains("created") && !(j["created"].is_null()))
                created = Timestamp(j["created"].get<std::string>());
            if (j.contains("updated") && !(j["updated"].is_null()))
                updated = Timestamp(j["updated"].get<std::string>());
            if (j.contains("creator") && !(j["creator"]["id"].is_null()))
                creator_id = j["creator"]["id"];
            if (j.contains("rootPlace") && !(j["rootPlace"]["id"].is_null()))
                place_id = j["rootPlace"]["id"];
            if (j.contains("placeVisits") && !(j["placeVisits"].is_null()))
                place_visits = j["placeVisits"];
        }

        Experience() = default;
    };

    struct AvatarAssetType
    {
        std::string name;
        long id;

        explicit AvatarAssetType(json j)
        {
            name = j["name"];
            id = j["id"];
        }

        AvatarAssetType() = default;
    };

    struct ChatSettings
    {
        bool chat_enabled;
        bool is_active_chat_user;
        bool is_connect_tab_enabled;

        explicit ChatSettings(json j)
        {
            if (j.contains("chatEnabled"))
                chat_enabled = j["chatEnabled"];
            if (j.contains("isActiveChatUser"))
                is_active_chat_user = j["isActiveChatUser"];
            if (j.contains("isConnectTabEnabled"))
                is_connect_tab_enabled = j["isConnectTabEnabled"];
        }

        ChatSettings() = default;
    };

    struct SearchedUser
    {
        std::vector<std::string> previous_usernames;
        bool has_verified_badge;
        int64_t id;
        std::string name;
        std::string display_name;

        explicit SearchedUser(json j)
        {
            if (j.contains("previousUsernames"))
                previous_usernames = j["previousUsernames"].get<std::vector<std::string>>();
            if (j.contains("hasVerifiedBadge"))
                has_verified_badge = j["hasVerifiedBadge"];
            if (j.contains("id"))
                id = j["id"];
            if (j.contains("name"))
                name = j["name"];
            if (j.contains("displayName"))
                display_name = j["displayName"];
        }

        SearchedUser() = default;
    };

    struct RejectedParticipant
    {
        std::string rejected_reason;
        std::string type;
        std::string name;
        std::string display_name;

        int64_t target_id;

        bool has_verified_badge;

        explicit RejectedParticipant(json j)
        {
            if (j.contains("rejectedReason"))
                rejected_reason = j["rejectedReason"];
            if (j.contains("type"))
                type = j["type"];
            if (j.contains("name"))
                name = j["name"];
            if (j.contains("displayName"))
                display_name = j["displayName"];
            if (j.contains("targetId"))
                target_id = j["targetId"];
            if (j.contains("hasVerifiedBadge"))
                has_verified_badge = j["hasVerifiedBadge"];
        }

        RejectedParticipant() = default;
    };
    struct ChatMessage
    {

        std::string id;
        std::string sender_type;
        std::string message_type;
        std::string content;

        Timestamp sent;
        bool read;

        int64_t sender_target_id;

        explicit ChatMessage(json j)
        {
            if (j.contains("id"))
                id = j["id"];
            if (j.contains("senderType"))
                sender_type = j["senderType"];
            if (j.contains("messageType"))
                message_type = j["messageType"];
            if (j.contains("content"))
                content = j["content"];
            if (j.contains("sent"))
                sent = Timestamp(j["sent"].get<std::string>());
            if (j.contains("read"))
                read = j["read"];
            if (j.contains("senderTargetId"))
                sender_target_id = j["senderTargetId"];
        }

        ChatMessage() = default;
    };

    struct GroupRole
    {
        std::string name;
        long id;
        int rank;
        int member_count;

        explicit GroupRole(json j)
        {
            id = j["id"];
            name = j["name"];
            rank = j["rank"];
            if (j.contains("memberCount"))
            {
                member_count = j["memberCount"];
            }
        }

        GroupRole() = default;
    };

    struct GroupRoles
    {
        int64_t group_id;
        std::vector<GroupRole> roles;

        explicit GroupRoles(json j)
        {
            group_id = j["groupId"];
            for (auto &i : j["roles"])
            {
                roles.emplace_back(i);
            }
        }

        GroupRoles() = default;
    };

    struct ChangeRoleResponse
    {
        GroupRole old_role;
        GroupRole new_role;
    };

    struct ConversationAddResponse
    {
        std::string result_type;
        std::string status_message;
        int64_t conersation_id;

        std::vector<RejectedParticipant> rejected_participants;

        explicit ConversationAddResponse(json j)
        {
            if (j.contains("resultType"))
                result_type = j["resultType"];
            if (j.contains("statusMessage"))
                status_message = j["statusMessage"];
            if (j.contains("conversationId"))
                conersation_id = j["conversationId"];

            if (j.contains("rejectedParticipants") && !j["rejectedParticipants"].empty())
            {
                for (auto &i : j["rejectedParticipants"])
                {
                    rejected_participants.emplace_back(i);
                }
            }
        }
    };
    struct GameSocialLink
    {
        std::string Title;
        std::string URL;
        std::string Type;

        long ID;

        explicit GameSocialLink(json j)
        {
            if (j.contains("title"))
                Title = j["title"];
            if (j.contains("url"))
                URL = j["url"];
            if (j.contains("type"))
                Type = j["type"];
            if (j.contains("id"))
                ID = j["id"];
        }

        GameSocialLink() = default;
    };

    struct GameSocialLinks
    {
        std::vector<GameSocialLink> Links;

        explicit GameSocialLinks(json j)
        {
            for (auto &i : j["data"])
            {
                Links.emplace_back(i);
            }
        }

        GameSocialLinks() = default;
    };

    struct DeveloperProductCreateResponse
    {
        std::string name, description;

        int64_t id;
        int64_t shop_id;
        int64_t icon_image_asset_id;

        explicit DeveloperProductCreateResponse(json j)
        {
            if (j.contains("id"))
                id = j["id"];
            if (j.contains("name"))
                name = j["name"];
            if (j.contains("description"))
                description = j["description"];
            if (j.contains("shopId"))
                shop_id = j["shopId"];
            if (j.contains("iconImageAssetId"))
                icon_image_asset_id = j["iconImageAssetId"];
        }

        DeveloperProductCreateResponse() = default;
    };

    struct BodyColors
    {
        int head_color_id;
        int torso_color_id;
        int right_arm_color_id;
        int left_arm_color_id;
        int right_leg_color_id;
        int left_leg_color_id;

        explicit BodyColors(json j)
        {
            if (j.contains("headColorId"))
                head_color_id = j["headColorId"];
            if (j.contains("torsoColorId"))
                torso_color_id = j["torsoColorId"];
            if (j.contains("rightArmColorId"))
                right_arm_color_id = j["rightArmColorId"];
            if (j.contains("leftArmColorId"))
                left_arm_color_id = j["leftArmColorId"];
            if (j.contains("rightLegColorId"))
                right_leg_color_id = j["rightLegColorId"];
            if (j.contains("leftLegColorId"))
                left_leg_color_id = j["leftLegColorId"];
        }

        BodyColors() = default;
    };

    struct OutfitDetailsAsset
    {
        std::string name;

        AvatarAssetType asset_type;

        int64_t asset_id;
        long current_version_id;

        explicit OutfitDetailsAsset(json j)
        {
            name = j["name"];
            asset_type = AvatarAssetType(j["assetType"]);
            asset_id = j["id"];
            current_version_id = j["currentVersion"];
        }

        OutfitDetailsAsset() = default;
    };

    struct GetOutfitsAsset
    {
        std::string name;
        int64_t id;
        bool is_editable;

        explicit GetOutfitsAsset(json j)
        {
            if (j.contains("name"))
                name = j["name"];
            if (j.contains("id"))
                id = j["id"];
            if (j.contains("isEditable"))
                is_editable = j["isEditable"];
        }

        GetOutfitsAsset() = default;
    };

    struct GetOutfitsResponse
    {
        std::vector<GetOutfitsAsset> outfits;
        int total;

        explicit GetOutfitsResponse(json j)
        {
            if (j.contains("data"))
            {
                for (auto &i : j["data"])
                    outfits.emplace_back(i);
            }
            if (j.contains("total"))
                total = j["total"];
        }

        GetOutfitsResponse() = default;
    };

    struct AvatarScales
    {
        int height, width, depth, head, proportion, body_type;

        explicit AvatarScales(json j)
        {
            if (j.contains("height"))
                height = j["height"];
            if (j.contains("width"))
                width = j["width"];
            if (j.contains("depth"))
                depth = j["depth"];
            if (j.contains("head"))
                head = j["head"];
            if (j.contains("proportion"))
                proportion = j["proportion"];
            if (j.contains("bodyType"))
                body_type = j["bodyType"];
        }

        AvatarScales() = default;
    };

    struct OutfitDetailsResponse
    {
        std::string name;
        std::string player_avatar_type;
        std::string outfit_type;

        int64_t id;

        std::vector<OutfitDetailsAsset> assets;
        BodyColors colors;
        AvatarScales scales;

        bool is_editable;

        explicit OutfitDetailsResponse(json j)
        {
            if (j.contains("name"))
                name = j["name"];
            if (j.contains("playerAvatarType"))
                player_avatar_type = j["playerAvatarType"];
            if (j.contains("outfitType"))
                outfit_type = j["outfitType"];
            if (j.contains("id"))
                id = j["id"];
            if (j.contains("bodyColors"))
                colors = BodyColors(j["bodyColors"]);
            if (j.contains("scale"))
                scales = AvatarScales(j["scale"]);
            if (j.contains("isEditable"))
                is_editable = j["isEditable"];

            for (auto &asset : j["assets"])
                assets.emplace_back(asset);
        }
    };

    struct TradeData
    {
        std::string status;

        int64_t trade_id;

        ShorthandUser sender;
        Timestamp created;
        Timestamp expiriation;

        bool is_active;

        explicit TradeData(json j)
        {
            if (j.contains("status"))
                status = j["status"];
            if (j.contains("id"))
                trade_id = j["id"];
            if (j.contains("user"))
                sender = ShorthandUser(j["user"]);
            if (j.contains("created"))
                created = Timestamp(j["created"].get<std::string>());
            if (j.contains("expiration"))
                expiriation = Timestamp(j["expiration"].get<std::string>());
            if (j.contains("isActive"))
                is_active = j["isActive"];
        }

        TradeData() = default;
    };

    struct CanTradeWithResponse
    {
        std::string status;
        bool can_trade;

        explicit CanTradeWithResponse(json j)
        {
            if (j.contains("status"))
                status = j["status"];
            if (j.contains("canTrade"))
                can_trade = j["canTrade"];
        }

        CanTradeWithResponse() = default;
    };

    struct ExperienceVotes
    {
        long Upvotes, Downvotes;

        explicit ExperienceVotes(json j)
        {
            Upvotes = j["upVotes"];
            Downvotes = j["downVotes"];
        }

        ExperienceVotes() = default;
    };

    struct GamePass
    {
        std::string name;
        std::string display_name;

        int64_t id;
        int64_t creator_id;
        int64_t product_id;

        int price;

        explicit GamePass(json j)
        {
            if (j.contains("name"))
                name = j["name"];
            if (j.contains("displayName"))
                display_name = j["displayName"];
            if (j.contains("id"))
                id = j["id"];
            if (j.contains("sellerId"))
                creator_id = j["sellerId"];
            if (j.contains("productId"))
                product_id = j["productId"];
            if (j.contains("price"))
                price = j["price"];
        }

        GamePass() = default;
    };

    struct PlaceInfoResponse
    {
        std::string name, source_name;
        std::string description, source_description;
        std::string universe_avatar_type;
        std::string genre;

        int64_t universe_id, place_id;
        long current_players;
        long visits;
        long favorited_count;

        int price;
        int max_players;

        User creator;
        Timestamp created;
        Timestamp updated;

        bool is_genre_enforced;
        bool copying_allowed;
        bool studio_access_to_apis_allowed;
        bool create_vip_servers_allowed;
        bool is_all_genre;

        explicit PlaceInfoResponse(json j)
        {
            if (j.contains("name"))
                name = j["name"];
            if (j.contains("description"))
                description = j["description"];
            if (j.contains("sourceName"))
                source_name = j["sourceName"];
            if (j.contains("sourceDescription"))
                source_description = j["sourceDescription"];
            if (j.contains("universeAvatarType"))
                universe_avatar_type = j["universeAvatarType"];
            if (j.contains("genre"))
                genre = j["genre"];
            if (j.contains("id"))
                universe_id = j["id"];
            if (j.contains("rootPlaceId"))
                place_id = j["rootPlaceId"];
            if (j.contains("playing"))
                current_players = j["playing"];
            if (j.contains("visits"))
                visits = j["visits"];
            if (j.contains("favoritedCount"))
                favorited_count = j["favoritedCount"];
            if (j.contains("price") && !(j["price"].is_null()))
                price = j["price"];
            if (j.contains("maxPlayers"))
                max_players = j["maxPlayers"];
            if (j.contains("creator"))
                creator = User(j["creator"]);
            if (j.contains("created"))
                created = Timestamp(j["created"].get<std::string>());
            if (j.contains("updated"))
                updated = Timestamp(j["updated"].get<std::string>());
            if (j.contains("isGenreEnforced"))
                is_genre_enforced = j["isGenreEnforced"];
            if (j.contains("copyingAllowed"))
                copying_allowed = j["copyingAllowed"];
            if (j.contains("studioAccessToApisAllowed"))
                studio_access_to_apis_allowed = j["studioAccessToApisAllowed"];
            if (j.contains("createVipServersAllowed"))
                create_vip_servers_allowed = j["createVipServersAllowed"];
            if (j.contains("isAllGenre"))
                is_all_genre = j["isAllGenre"];
        }

        PlaceInfoResponse() = default;
    };

    struct GroupWallPost
    {
        std::string body;

        ShorthandUser poster;

        Timestamp created;
        Timestamp updated;

        int64_t post_id;

        explicit GroupWallPost(json j)
        {
            if (j.contains("body"))
                body = j["body"];
            if (j.contains("poster"))
                poster = ShorthandUser(j["poster"]);
            if (j.contains("created"))
                created = Timestamp(j["created"].get<std::string>());
            if (j.contains("updated"))
                updated = Timestamp(j["updated"].get<std::string>());
            if (j.contains("id"))
                post_id = j["id"];
        }

        GroupWallPost() = default;
    };

    struct GroupNamehistory
    {
        std::string name;
        Timestamp created;

        explicit GroupNamehistory(json j)
        {
            if (j.contains("name"))
                name = j["name"];
            if (j.contains("created"))
                created = Timestamp(j["created"].get<std::string>());
        }

        GroupNamehistory() = default;
    };

    struct GroupExperienceCreator
    {
        int64_t id;
        std::string type;
        std::string name;

        explicit GroupExperienceCreator(json j)
        {
            id = j["id"];
            type = j["type"];
            if (j.contains("name"))
                name = j["name"];
        }

        GroupExperienceCreator() = default;
    };
    struct GroupExperience
    {
        std::string name;
        std::string description;

        Timestamp created;
        Timestamp updated;
        GroupExperienceCreator creator;

        int64_t place_id;
        int64_t universe_id;
        long place_visits;

        explicit GroupExperience(json j)
        {
            if (j.contains("name"))
                name = j["name"];
            if (j.contains("description") && !(j["description"].is_null()))
                description = j["description"];
            if (j.contains("creator"))
                creator = GroupExperienceCreator(j["creator"]);
            if (j.contains("created"))
                created = Timestamp(j["created"].get<std::string>());
            if (j.contains("updated"))
                updated = Timestamp(j["updated"].get<std::string>());
            if (j.contains("id"))
                universe_id = j["id"];
            if (j.contains("rootPlace"))
                place_id = j["id"];
            if (j.contains("placeVisits"))
                place_visits = j["placeVisits"];
        }

        GroupExperience() = default;
    };

    struct FriendRequest
    {
        std::string origin_source_type;

        Timestamp sent_at;

        int64_t sender_id;
        int64_t source_universe_id;

        explicit FriendRequest(json j)
        {
            if (j.contains("originSourceType"))
                origin_source_type = j["originSourceType"];
            if (j.contains("sentAt"))
                sent_at = Timestamp(j["sentAt"].get<std::string>());
            if (j.contains("senderId"))
                sender_id = j["senderId"];
            if (j.contains("sourceUniverseId") && !(j["sourceUniverseId"].is_null()))
                source_universe_id = j["sourceUniverseId"];
        }

        FriendRequest() = default;
    };

    struct FriendRequestsResponse
    {
        std::vector<FriendRequest> friend_requests;
        std::vector<User> sender_info;
        std::vector<std::string> mutual_friends_list;

        explicit FriendRequestsResponse(json j)
        {
            for (auto &i : j["data"])
            {
                friend_requests.emplace_back(i["friendRequest"]);
                sender_info.emplace_back(i);
            }

            if (j.contains("mutualFriendsList") && !j["mutualFriendsList"].empty())
            {
                for (auto &i : j["mutualFriendsList"])
                {
                    mutual_friends_list.emplace_back(i);
                }
            }
        }

        FriendRequestsResponse() = default;
    };

    struct PhoneInfo
    {
        std::string country_code;
        std::string prefix;
        std::string phone;

        int verification_code_length;

        bool is_verified;
        bool can_bypass_password_for_phone_update;

        explicit PhoneInfo(json j)
        {
            country_code = j["countryCode"];
            prefix = j["prefix"];
            phone = j["phone"];
            verification_code_length = j["verificationCodeLength"];
            is_verified = j["isVerified"];
            can_bypass_password_for_phone_update = j["canBypassPasswordForPhoneUpdate"];
        }

        PhoneInfo() = default;
    };

    struct AvatarAsset
    {
        std::string name;

        AvatarAssetType asset_type;

        long asset_id;
        long current_version_id;

        explicit AvatarAsset(json j)
        {
            name = j["name"];
            asset_type = AvatarAssetType(j["assetType"]);
            asset_id = j["id"];
            current_version_id = j["currentVersionId"];
        }

        AvatarAsset() = default;
    };

    struct AvatarResponse
    {
        std::string player_avatar_type;

        BodyColors colors;
        AvatarScales scales;

        std::vector<AvatarAsset> assets;

        explicit AvatarResponse(json j)
        {
            player_avatar_type = j["playerAvatarType"];
            colors = BodyColors(j["bodyColors"]);
            scales = AvatarScales(j["scales"]);
            for (auto &asset : j["assets"])
            {
                assets.emplace_back(asset);
            }
        }

        AvatarResponse() = default;
    };

    struct BirthdateResponse
    {
        int year, month, day;

        explicit BirthdateResponse(json j)
        {
            year = j["birthYear"];
            month = j["birthMonth"];
            day = j["birthDay"];
        }

        BirthdateResponse() = default;
    };

    struct InventoryAsset
    {
        std::string name;
        std::string asset_type;

        Timestamp created;

        int64_t asset_id;

        explicit InventoryAsset(json j)
        {
            if (j.contains("name") && !(j["name"].is_null()))
                name = j["name"];
            if (j.contains("assetType") && !(j["assetType"].is_null()))
                asset_type = j["assetType"];
            if (j.contains("created") && !(j["created"].is_null()))
                created = Timestamp(j["created"].get<std::string>());
            if (j.contains("assetId") && !(j["assetId"].is_null()))
                asset_id = j["assetId"];
        }

        InventoryAsset() = default;
    };

    struct UserPresence
    {
        std::string last_location;
        std::string game_id;

        Timestamp last_online;

        int64_t place_id;
        int64_t root_place_id;
        int64_t universe_id;
        int64_t user_id;

        int user_presence_type;

        explicit UserPresence(json j)
        {
            if (j.contains("lastLocation") && !(j["lastLocation"].is_null()))
                last_location = j["lastLocation"];
            if (j.contains("lastOnline") && !(j["lastOnline"].is_null()))
                last_online = Timestamp(j["lastOnline"].get<std::string>());
            if (j.contains("placeId") && !(j["placeId"].is_null()))
                place_id = j["placeId"];
            if (j.contains("rootPlaceId") && !(j["rootPlaceId"].is_null()))
                root_place_id = j["rootPlaceId"];
            if (j.contains("universeId") && !(j["universeId"].is_null()))
                universe_id = j["universeId"];
            if (j.contains("userId") && !(j["userId"].is_null()))
                user_id = j["userId"];
            if (j.contains("userPresenceType") && !(j["userPresenceType"].is_null()))
                user_presence_type = j["userPresenceType"];
            if (j.contains("gameId") && !(j["gameId"].is_null()))
                game_id = j["gameId"];
        }

        UserPresence() = default;
    };

    struct BadgeStats
    {
        long past_day_awarded_count;
        long awarded_count;
        int win_rate_percentage;

        explicit BadgeStats(json j)
        {
            if (j.contains("pastDayAwardedCount"))
                past_day_awarded_count = j["pastDayAwardedCount"];
            if (j.contains("awardedCount"))
                awarded_count = j["awardedCount"];
            if (j.contains("winRatePercentage"))
                win_rate_percentage = j["winRatePercentage"];
        }

        BadgeStats() = default;
    };

    struct Badge
    {
        std::string name;
        std::string description;
        std::string display_name;
        std::string display_description;
        std::string awarder_type;

        Timestamp created;
        Timestamp updated;

        BadgeStats statistics;

        long icon_image_id;
        long display_icon_image_id;
        long awarder_id;

        bool enabled;

        explicit Badge(json j)
        {
            if (j.contains("name"))
                name = j["name"];
            if (j.contains("description"))
                description = j["description"];
            if (j.contains("displayName"))
                display_name = j["displayName"];
            if (j.contains("displayDescription"))
                display_description = j["displayDescription"];
            if (j.contains("awarder"))
                awarder_type = j["awarder"]["type"];
            if (j.contains("created"))
                created = Timestamp(j["created"].get<std::string>());
            if (j.contains("updated"))
                updated = Timestamp(j["updated"].get<std::string>());
            if (j.contains("iconImageId"))
                icon_image_id = j["iconImageId"];
            if (j.contains("displayIconImageId"))
                display_icon_image_id = j["displayIconImageId"];
            if (j.contains("awarder"))
                awarder_id = j["awarder"]["id"];
            if (j.contains("enabled"))
                enabled = j["enabled"];
            if (j.contains("statistics"))
                statistics = BadgeStats(j["statistics"]);
        }

        Badge() = default;
    };

    struct Role
    {
        std::string name;
        int rank;
        int64_t id;

        explicit Role(json j)
        {
            if (j.contains("name"))
                name = j["name"];
            if (j.contains("rank"))
                rank = j["rank"];
            if (j.contains("id"))
                id = j["id"];
        }

        Role() = default;
    };

    struct AuditItemActor
    {
        ShorthandUser user;
        Role role;

        explicit AuditItemActor(json j)
        {
            if (j.contains("user"))
                user = ShorthandUser(j["user"]);
            if (j.contains("role"))
                role = Role(j["role"]);
        }

        AuditItemActor() = default;
    };

    struct AuditItem
    {
        AuditItemActor actor;
        std::string action_type;
        json description;
        Timestamp created;

        explicit AuditItem(json j)
        {
            if (j.contains("actor"))
                actor = AuditItemActor(j["actor"]);
            if (j.contains("actionType"))
                action_type = j["actionType"];
            if (j.contains("description"))
                description = j["description"];
            if (j.contains("created"))
                created = Timestamp(j["created"].get<std::string>());
        }

        AuditItem() = default;
    };

    struct AuditPage
    {
        std::vector<AuditItem> items;

        explicit AuditPage(json j)
        {
            if (j.contains("data"))
            {
                for (auto &item : j["data"])
                {
                    items.push_back(AuditItem(item));
                }
            }
        }
    };

    struct GShout
    {
        std::string body;
        ShorthandUser poster;

        Timestamp Created;
        Timestamp Updated;

        explicit GShout(json j)
        {
            if (j.contains("body"))
                body = j["body"];
            if (j.contains("poster"))
                poster = ShorthandUser(j["poster"]);
            if (j.contains("created"))
                Created = Timestamp(j["created"].get<std::string>());
            if (j.contains("updated"))
                Updated = Timestamp(j["updated"].get<std::string>());
        }

        GShout() = default;
    };

    struct Group
    {
        std::string name;
        std::string description;

        ShorthandUser owner;

        GShout shout;

        int64_t group_id;
        long member_count;

        bool is_builders_club_only;
        bool is_public_entry_allowed;
        bool has_verified_badge;

        explicit Group(json j)
        {
            if (j.contains("name"))
                name = j["name"];
            if (j.contains("description"))
                description = j["description"];
            if (j.contains("owner"))
                owner = ShorthandUser(j["owner"]);
            if (j.contains("shout") && !(j["shout"].is_null()))
                shout = GShout(j["shout"]);
            if (j.contains("memberCount"))
                member_count = j["memberCount"];
            if (j.contains("id"))
                group_id = j["id"];
            if (j.contains("isBuildersClubOnly"))
                is_builders_club_only = j["isBuildersClubOnly"];
            if (j.contains("isPublicEntryAllowed"))
                is_public_entry_allowed = j["isPublicEntryAllowed"];
            if (j.contains("hasVerifiedBadge"))
                has_verified_badge = j["hasVerifiedBadge"];
        }

        Group() = default;
    };

    struct GroupWithRole
    {
        Group group;
        Role role;

        explicit GroupWithRole(json j)
        {
            group = Group(j["group"]);
            role = Role(j["role"]);
        }

        GroupWithRole() = default;
    };

    struct ChatConversationUniverse
    {
        int64_t universe_id;
        int64_t root_place_id;

        explicit ChatConversationUniverse(json j)
        {
            universe_id = j["universeId"];
            root_place_id = j["rootPlaceId"];
        }

        ChatConversationUniverse() = default;
    };

    struct ChatConversationTitle
    {
        std::string title_for_viewer;

        bool is_default_title;

        explicit ChatConversationTitle(json j)
        {
            title_for_viewer = j["titleForViewer"];
            is_default_title = j["isDefaultTitle"];
        }

        ChatConversationTitle() {}
    };

    struct ChatConversation
    {
        int64_t id;
        std::string title;
        User initiator;
        bool has_unread_messages;
        std::vector<User> participants;
        std::string conversation_type;
        ChatConversationTitle conversation_title;
        Timestamp last_updated;
        ChatConversationUniverse conversation_universe;

        ChatConversation(json j)
        {
            if (j.contains("id"))
                id = j["id"];
            if (j.contains("title"))
                title = j["title"];
            if (j.contains("initiator"))
                initiator = User(j["initiator"]);
            if (j.contains("hasUnreadMessages") && !j["hasUnreadMessages"].is_null())
                has_unread_messages = j["hasUnreadMessages"];
            if (j.contains("participants"))
            {
                for (auto &user : j["participants"])
                    participants.emplace_back(user);
            }
            if (j.contains("conversationType"))
                conversation_type = j["conversationType"];
            if (j.contains("conversationTitle"))
                conversation_title = ChatConversationTitle(j["conversationTitle"]);
            if (j.contains("lastUpdated"))
                last_updated = Timestamp(j["lastUpdated"].get<std::string>());
            if (!j["conversationUniverse"].is_null())
                conversation_universe = ChatConversationUniverse(j["conversationUniverse"]);
        }

        ChatConversation() = default;
    };

    struct ChatConversationsResponse
    {
        std::vector<ChatConversation> Conversations;

        ChatConversationsResponse(json j)
        {
            for (auto &conversation : j)
                Conversations.emplace_back(conversation);
        }
    };

    struct FriendsOnline
    {
        std::string user_presence_type;
        std::string user_location_type;
        std::string last_location;
        std::string game_instance_id;
        std::string username;
        std::string display_name;

        int64_t place_id;
        int64_t universe_id;
        int64_t uid;

        Timestamp last_online;

        explicit FriendsOnline(json j)
        {
            if (j.contains("userPresenceType"))
                user_presence_type = j["userPresenceType"];
            if (j.contains("userLocationType"))
                user_location_type = j["userLocationType"];
            if (j.contains("lastLocation"))
                last_location = j["lastLocation"];
            if (j.contains("gameInstanceId"))
                game_instance_id = j["gameInstanceId"];
            if (j.contains("name"))
                username = j["name"];
            if (j.contains("displayName"))
                display_name = j["displayName"];
            if (j.contains("placeId"))
                place_id = j["placeId"];
            if (j.contains("universeId"))
                universe_id = j["universeId"];
            if (j.contains("id"))
                uid = j["id"];
            if (j.contains("lastOnline"))
                last_online = Timestamp(j["lastOnline"].get<std::string>());
        }

        FriendsOnline() = default;
    };

    struct OneToOneConversationResponse
    {
        ChatConversation conversation;
        std::vector<User> rejected_participants;
        std::string result_type;
        std::string status_message;

        explicit OneToOneConversationResponse(json j)
        {
            conversation = ChatConversation(j["conversation"]);
            for (auto &user : j["rejectedParticipants"])
                rejected_participants.emplace_back(user);
            result_type = j["resultType"];
            status_message = j["statusMessage"];
        }

        OneToOneConversationResponse() = default;
    };

    struct StartGroupConversationResponse
    {
        ChatConversation conversation;
        std::vector<User> rejected_participants;
        std::string result_type;
        std::string status_message;

        explicit StartGroupConversationResponse(json j)
        {
            conversation = ChatConversation(j["conversation"]);
            for (auto &user : j["rejectedParticipants"])
                rejected_participants.emplace_back(user);
            result_type = j["resultType"];
            status_message = j["statusMessage"];
        }

        StartGroupConversationResponse() = default;
    };
    struct PriceDataPoint
    {
        long price;
        Timestamp date;

        explicit PriceDataPoint(json j)
        {
            price = j["value"];
            date = Timestamp(j["date"].get<std::string>());
        }

        PriceDataPoint() = default;
    };

    struct VolumeDataPoint
    {
        long volume;
        Timestamp date;

        explicit VolumeDataPoint(json j)
        {
            volume = j["value"];
            date = Timestamp(j["date"].get<std::string>());
        }

        VolumeDataPoint() = default;
    };
    struct ResaleData
    {
        int asset_stock;
        int sales;
        int number_remaining;
        int original_price;

        long recent_average_price;

        std::vector<PriceDataPoint> price_data;
        std::vector<VolumeDataPoint> volume_data;

        explicit ResaleData(json j)
        {
            asset_stock = j["assetStock"];
            sales = j["sales"];
            number_remaining = j["numberRemaining"];
            original_price = j["originalPrice"];
            recent_average_price = j["recentAveragePrice"];

            for (auto &element : j["priceDataPoints"])
                price_data.emplace_back(element);

            for (auto &element : j["volumeDataPoints"])
                volume_data.emplace_back(element);
        }

        ResaleData() = default;
    };

    struct ResellerAgent
    {
        std::string username;
        std::string type;
        int64_t user_id;

        explicit ResellerAgent(json j)
        {
            username = j["name"];
            type = j["type"];
            user_id = j["id"];
        }
        ResellerAgent() = default;
    };

    struct ResellerData
    {
        int user_asset_id;
        int price;
        int serial_number;

        ResellerAgent seller;

        explicit ResellerData(json reseller_data)
        {
            user_asset_id = reseller_data["userAssetId"];
            price = reseller_data["price"];
            serial_number = reseller_data["serialNumber"];

            seller = ResellerAgent(reseller_data["seller"]);
        }

        ResellerData() = default;
    };

    struct AssetCreator
    {
        std::string name;
        std::string creator_type;
        int64_t user_id;

        explicit AssetCreator(json creator)
        {
            name = creator["Name"];
            creator_type = creator["CreatorType"];
            user_id = creator["Id"];
        }

        AssetCreator() = default;
    };

    struct AssetInfo
    {
        std::string name;
        std::string description;
        std::string asset_type;
        std::string creator_name;
        std::string creator_type;

        Timestamp created;
        Timestamp updated;

        AssetCreator creator;

        int price;

        long sales;
        long creator_id;
        long product_id;

        bool is_new;
        bool is_for_sale;
        bool is_limited;
        bool is_limited_unique;

        // https://github.com/ro-py/ro.py/blob/284b30dfef4c8117198b961c3b4b47c040da6af4/roblox/assets.py#L21 <3
        std::map<int, std::string> asset_type_names = {
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

        explicit AssetInfo(json Data)
        {
            name = Data["Name"];
            description = Data["Description"];
            asset_type = asset_type_names[Data["AssetTypeId"]];
            created = Timestamp(Data["Created"].get<std::string>());
            updated = Timestamp(Data["Updated"].get<std::string>());
            creator_name = Data["Creator"]["Name"];
            creator_type = Data["Creator"]["CreatorType"];
            creator = AssetCreator(Data["Creator"]);
            price = Data["PriceInRobux"];
            sales = Data["Sales"];
            creator_id = Data["Creator"]["Id"];
            is_new = Data["IsNew"];
            is_for_sale = Data["IsForSale"];
            is_limited = Data["IsLimited"];
            is_limited_unique = Data["IsLimitedUnique"];
            product_id = Data["ProductId"];
        }

        AssetInfo() = default;
    };

    struct GameInstance
    {
        std::string id;
        std::string access_code;

        int64_t vip_server_id;
        int max_players;
        int playing;
        int fps;
        double ping;
        Responses::User owner;

        std::vector<std::string> player_tokens;
        explicit GameInstance(json instance)
        {
            if (instance.contains("id"))
                id = instance["id"];
            if (instance.contains("maxPlayers"))
                max_players = instance["maxPlayers"];
            if (instance.contains("playing") && !instance["playing"].is_null())
                playing = instance["playing"];
            if (instance.contains("playerTokens"))
            {
                for (auto &element : instance["playerTokens"])
                {
                    player_tokens.emplace_back(element);
                }
            }
            if (instance.contains("fps"))
                fps = instance["fps"];
            if (instance.contains("ping"))
                ping = instance["ping"];
            if (instance.contains("vipServerId"))
                vip_server_id = instance["vipServerId"];
            if (instance.contains("accessCode"))
                access_code = instance["accessCode"];
            if (instance.contains("owner"))
                owner = Responses::User(instance["owner"]);
        }
    };

    struct RolloutFeature
    {
        std::string feature_name;
        bool is_rollout_enabled;

        explicit RolloutFeature(json feature)
        {
            feature_name = feature["featureName"];
            is_rollout_enabled = feature["isRolloutEnabled"];
        }
    };

    struct ChatConversationWithMessages
    {
        int64_t conversation_id;
        std::vector<Responses::ChatMessage> messages;

        explicit ChatConversationWithMessages(json conversation)
        {
            conversation_id = conversation["conversationId"];
            for (auto &message : conversation["chatMessages"])
            {
                messages.emplace_back(message);
            }
        }
    };

    struct RemoveFromConversationResponse
    {
        int64_t conversation_id;
        std::string result_type;
        std::string status_message;

        explicit RemoveFromConversationResponse(json response)
        {
            conversation_id = response["conversationId"];
            result_type = response["resultType"];
            status_message = response["statusMessage"];
        }

        RemoveFromConversationResponse() = default;
    };

    struct RenameGroupConversationTitle
    {
        std::string TitleForViewer;
        bool IsDefaultTitle;

        explicit RenameGroupConversationTitle(json title)
        {
            TitleForViewer = title["titleForViewer"];
            IsDefaultTitle = title["isDefaultTitle"];
        }

        RenameGroupConversationTitle() = default;
    };

    struct RenameGroupConversationResponse
    {
        std::string ConversationTitle;
        std::string ResultType;
        RenameGroupConversationTitle Title;
        std::string StatusMessage;

        explicit RenameGroupConversationResponse(json response)
        {
            ConversationTitle = response["conversationTitle"];
            ResultType = response["resultType"];
            Title = RenameGroupConversationTitle(response["title"]);
            StatusMessage = response["statusMessage"];
        }
    };

    struct SendMessageResponse
    {
        std::string content;
        bool filtered_for_receivers;
        std::string message_id;
        Timestamp sent;
        std::string message_type;
        std::string result_type;
        std::string status_message;

        explicit SendMessageResponse(json response)
        {
            if (!response["content"].is_null())
                content = response["content"];
            filtered_for_receivers = response["filteredForReceivers"];
            message_id = response["messageId"];
            if (!response["Sent"].is_null())
                sent = Timestamp(response["sent"].get<std::string>());
            message_type = response["messageType"];
            result_type = response["resultType"];
            status_message = response["statusMessage"];
        }

        SendMessageResponse() = default;
    };

    struct GamePassProductInfoResponse
    {
        int64_t target_id;
        std::string product_type;
        int64_t asset_id;
        int64_t product_id;
        std::string name;
        std::string description;
        int64_t asset_type_id;
        Responses::AssetCreator creator;
        int64_t icon_image_asset_id;
        Timestamp created;
        Timestamp updated;
        int64_t price_in_robux;
        int64_t sales;
        bool is_new;
        bool is_for_sale;
        bool is_public_domain;
        bool is_limited;
        bool is_limited_unique;
        int64_t minimum_membership_level;

        explicit GamePassProductInfoResponse(json Data)
        {
            target_id = Data["TargetId"];
            product_type = Data["ProductType"];
            asset_id = Data["AssetId"];
            product_id = Data["ProductId"];
            name = Data["Name"];
            description = Data["Description"];
            asset_type_id = Data["AssetTypeId"];
            creator = Responses::AssetCreator(Data["Creator"]);
            icon_image_asset_id = Data["IconImageAssetId"];
            created = Timestamp(Data["Created"].get<std::string>());
            updated = Timestamp(Data["Updated"].get<std::string>());
            price_in_robux = Data["PriceInRobux"];
            sales = Data["Sales"];
            is_new = Data["IsNew"];
            is_for_sale = Data["IsForSale"];
            is_public_domain = Data["IsPublicDomain"];
            is_limited = Data["IsLimited"];
            is_limited_unique = Data["IsLimitedUnique"];
            minimum_membership_level = Data["MinimumMembershipLevel"];
        }

        GamePassProductInfoResponse() = default;
    };

    struct Thumbnail
    {
        int64_t target_id;
        std::string state;
        std::string image_url;

        explicit Thumbnail(json Data)
        {
            target_id = Data["targetId"];
            state = Data["state"];
            Data["imageUrl"].is_null() ? image_url = "" : image_url = Data["imageUrl"];
        }
    };

    struct TransactionTotalsResponse
    {
        int64_t sales_total;
        int64_t purchases_total;
        int64_t affiliate_sales_total;
        int64_t group_payouts_total;
        int64_t currency_purchases_total;
        int64_t premium_stipends_total;
        int64_t trade_system_earnings_total;
        int64_t trade_system_costs_total;
        int64_t premium_payouts_total;
        int64_t group_premium_payouts_total;
        int64_t ad_spend_total;
        int64_t developer_exchange_total;
        int64_t pending_robux_total;
        int64_t incoming_robux_total;
        int64_t outgoing_robux_total;
        int64_t individual_to_group_total;
        int64_t cs_adjustment_total;
        int64_t ads_revshare_payouts_total;
        int64_t group_ads_revshare_payouts_total;

        explicit TransactionTotalsResponse(json Data)
        {
            sales_total = Data["salesTotal"];
            purchases_total = Data["purchasesTotal"];
            affiliate_sales_total = Data["affiliateSalesTotal"];
            group_payouts_total = Data["groupPayoutsTotal"];
            currency_purchases_total = Data["currencyPurchasesTotal"];
            premium_stipends_total = Data["premiumStipendsTotal"];
            trade_system_earnings_total = Data["tradeSystemEarningsTotal"];
            trade_system_costs_total = Data["tradeSystemCostsTotal"];
            premium_payouts_total = Data["premiumPayoutsTotal"];
            group_premium_payouts_total = Data["groupPremiumPayoutsTotal"];
            ad_spend_total = Data["adSpendTotal"];
            developer_exchange_total = Data["developerExchangeTotal"];
            pending_robux_total = Data["pendingRobuxTotal"];
            incoming_robux_total = Data["incomingRobuxTotal"];
            outgoing_robux_total = Data["outgoingRobuxTotal"];
            individual_to_group_total = Data["individualToGroupTotal"];
            cs_adjustment_total = Data["csAdjustmentTotal"];
            ads_revshare_payouts_total = Data["adsRevsharePayoutsTotal"];
            group_ads_revshare_payouts_total = Data["groupAdsRevsharePayoutsTotal"];
        }
    };
}