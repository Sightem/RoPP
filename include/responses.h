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

        std::string ToISO8601()
        {
            return std::to_string(year) + "-" + std::to_string(month) + "-" + std::to_string(day);
        }

        std::time_t ToUnix()
        {
            std::tm t = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
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
        std::string Username;
        std::string DisplayName;
        std::string Description;
        std::string BuildersClubMembershipType;

        Timestamp Created;

        int PresenceType;
        int FriendFrequentScore;
        int FriendFrequentRank;

        long UID;

        bool IsOnline;
        bool IsDeleted;
        bool HasVerifiedBadge;
        bool IsBanned;

        void PopulateFromUID()
        {   
            Request req("https://users.roblox.com/v1/users/" + std::to_string(this->UID));
            req.set_header("Referer", "https://www.roblox.com/users/" + std::to_string(this->UID) + "/profile");
            req.set_header("Content", "application/json");
            req.set_header("Accept", "application/json");
            req.initalize();

            Response res = req.get();

            *this = User(json::parse(res.data));
        }

    public:
        explicit User(json j)
        {
            if (j.contains("name")) Username = j["name"];
            if (j.contains("username")) Username = j["username"];
            if (j.contains("displayName")) DisplayName = j["displayName"];
            if (j.contains("description") && !(j["description"].is_null())) Description = j["description"];
            if (j.contains("created")) Created = Timestamp(j["created"]);
            if (j.contains("presenceType")) PresenceType = j["presenceType"];
            if (j.contains("friendFrequentScore")) FriendFrequentScore = j["friendFrequentScore"];
            if (j.contains("friendFrequentRank")) FriendFrequentRank = j["friendFrequentRank"];
            if (j.contains("id")) UID = j["id"];
            if (j.contains("userId")) UID = j["userId"];
            if (j.contains("isOnline")) IsOnline = j["isOnline"];
            if (j.contains("isDeleted")) IsDeleted = j["isDeleted"];
            if (j.contains("hasVerifiedBadge")) HasVerifiedBadge = j["hasVerifiedBadge"];
            if (j.contains("isBanned")) IsBanned = j["isBanned"];
            if (j.contains("buildersClubMembershipType")) BuildersClubMembershipType = j["buildersClubMembershipType"];
        }

        User() = default;
    };

    struct ShorthandUser
    {
        std::string Username;
        std::string DisplayName;
        int64_t UID;

        bool HasVerifiedBadge;

        explicit ShorthandUser(json j)
        {
            if (j.contains("name")) Username = j["name"];
            if (j.contains("username")) Username = j["username"];
            if (j.contains("displayName")) DisplayName = j["displayName"];
            if (j.contains("id")) UID = j["id"];
            if (j.contains("userId")) UID = j["userId"];
            if (j.contains("hasVerifiedBadge")) HasVerifiedBadge = j["hasVerifiedBadge"];
        }

        ShorthandUser() = default;
    };

    struct Experience
    {
        std::string Name;
        std::string Description;
        std::string CreatorType;
        std::string PlaceType;

        Timestamp Created;
        Timestamp Updated;

        long CreatorID;
        long PlaceID;
        long PlaceVisits;

        explicit Experience(json j)
        {
            if (j.contains("name") && !(j["name"].is_null())) Name = j["name"];
            if (j.contains("description") && !(j["description"].is_null())) Description = j["description"];
            if (j.contains("creator") && !(j["creator"]["type"].is_null())) CreatorType = j["creator"]["type"];
            if (j.contains("rootPlace") && !(j["rootPlace"]["type"].is_null())) PlaceType = j["rootPlace"]["type"];
            if (j.contains("created") && !(j["created"].is_null())) Created = Timestamp(j["created"]);
            if (j.contains("updated") && !(j["updated"].is_null())) Updated = Timestamp(j["updated"]);
            if (j.contains("creator") && !(j["creator"]["id"].is_null())) CreatorID = j["creator"]["id"];
            if (j.contains("rootPlace") && !(j["rootPlace"]["id"].is_null())) PlaceID = j["rootPlace"]["id"];
            if (j.contains("placeVisits") && !(j["placeVisits"].is_null())) PlaceVisits = j["placeVisits"];
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
            if (j.contains("chatEnabled")) chat_enabled = j["chatEnabled"];
            if (j.contains("isActiveChatUser")) is_active_chat_user = j["isActiveChatUser"];
            if (j.contains("isConnectTabEnabled")) is_connect_tab_enabled = j["isConnectTabEnabled"];
        }

        ChatSettings() = default;
    };

    struct SearchedUser
    {
        std::vector<std::string> PreviousUsernames;
        bool HasVerifiedBadge;
        long ID;
        std::string Name;
        std::string DisplayName;

        explicit SearchedUser(json j)
        {
            if (j.contains("previousUsernames")) PreviousUsernames = j["previousUsernames"];
            if (j.contains("hasVerifiedBadge")) HasVerifiedBadge = j["hasVerifiedBadge"];
            if (j.contains("id")) ID = j["id"];
            if (j.contains("name")) Name = j["name"];
            if (j.contains("displayName")) DisplayName = j["displayName"];
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
            if (j.contains("rejectedReason")) rejected_reason = j["rejectedReason"];
            if (j.contains("type")) type = j["type"];
            if (j.contains("name")) name = j["name"];
            if (j.contains("displayName")) display_name = j["displayName"];
            if (j.contains("targetId")) target_id = j["targetId"];
            if (j.contains("hasVerifiedBadge")) has_verified_badge = j["hasVerifiedBadge"];
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
            if (j.contains("id")) id = j["id"];
            if (j.contains("senderType")) sender_type = j["senderType"];
            if (j.contains("messageType")) message_type = j["messageType"];
            if (j.contains("content")) content = j["content"];
            if (j.contains("sent")) sent = Timestamp(j["sent"]);
            if (j.contains("read")) read = j["read"];
            if (j.contains("senderTargetId")) sender_target_id = j["senderTargetId"];
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
            for (auto& i : j["roles"])
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
           if (j.contains("resultType")) result_type = j["resultType"];
           if (j.contains("statusMessage")) status_message = j["statusMessage"];
           if (j.contains("conversationId")) conersation_id = j["conversationId"];

           if (j.contains("rejectedParticipants") && !j["rejectedParticipants"].empty())
           {
                for (auto& i : j["rejectedParticipants"])
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
            if (j.contains("title")) Title = j["title"];
            if (j.contains("url")) URL = j["url"];
            if (j.contains("type")) Type = j["type"];
            if (j.contains("id")) ID = j["id"];
        }

        GameSocialLink() = default;
    };

    struct GameSocialLinks
    {
        std::vector<GameSocialLink> Links;

        explicit GameSocialLinks(json j)
        {
            for (auto& i : j["data"])
            {
                Links.emplace_back(i);
            }
        }

        GameSocialLinks() = default;
    };
    struct DeveloperProductCreateResponse
    {
        std::string Name, Description;

        long ID;
        long ShopID;
        long IconImageAssetID;

        explicit DeveloperProductCreateResponse(json j)
        {
            if (j.contains("id")) ID = j["id"];
            if (j.contains("name")) Name = j["name"];
            if (j.contains("description")) Description = j["description"];
            if (j.contains("shopId")) ShopID = j["shopId"];
            if (j.contains("iconImageAssetId")) IconImageAssetID = j["iconImageAssetId"];
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
            if (j.contains("headColorId")) head_color_id = j["headColorId"];
            if (j.contains("torsoColorId")) torso_color_id = j["torsoColorId"];
            if (j.contains("rightArmColorId")) right_arm_color_id = j["rightArmColorId"];
            if (j.contains("leftArmColorId")) left_arm_color_id = j["leftArmColorId"];
            if (j.contains("rightLegColorId")) right_leg_color_id = j["rightLegColorId"];
            if (j.contains("leftLegColorId")) left_leg_color_id = j["leftLegColorId"];
        }

        BodyColors() = default;
    };


    struct OutfitDetailsAsset
    {
        std::string name;
        
        AvatarAssetType asset_type;

        long asset_id;
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
        long id;
        bool is_editable;

        explicit GetOutfitsAsset(json j)
        {
            if (j.contains("name")) name = j["name"];
            if (j.contains("id")) id = j["id"];
            if (j.contains("isEditable")) is_editable = j["isEditable"];
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
                for (auto& i : j["data"]) outfits.emplace_back(i);
            }
            if (j.contains("total")) total = j["total"];
        }

        GetOutfitsResponse() = default;
    };

    struct AvatarScales
    {
        int height, width, depth, head, proportion, body_type;

        explicit AvatarScales(json j)
        {
            if (j.contains("height")) height = j["height"];
            if (j.contains("width")) width = j["width"];
            if (j.contains("depth")) depth = j["depth"];
            if (j.contains("head")) head = j["head"];
            if (j.contains("proportion")) proportion = j["proportion"];
            if (j.contains("bodyType")) body_type = j["bodyType"];
        }

        AvatarScales() = default;
    };

    struct OutfitDetailsResponse
    {
        std::string name;
        std::string player_avatar_type;
        std::string outfit_type;

        long id;

        std::vector<OutfitDetailsAsset> assets;
        BodyColors colors;
        AvatarScales scales;

        bool is_editable;

        explicit OutfitDetailsResponse(json j)
        {
            if (j.contains("name")) name = j["name"];
            if (j.contains("playerAvatarType")) player_avatar_type = j["playerAvatarType"];
            if (j.contains("outfitType")) outfit_type = j["outfitType"];
            if (j.contains("id")) id = j["id"];
            if (j.contains("bodyColors")) colors = BodyColors(j["bodyColors"]);
            if (j.contains("scale")) scales = AvatarScales(j["scale"]);
            if (j.contains("isEditable")) is_editable = j["isEditable"];

            for (auto& asset : j["assets"])
                assets.emplace_back(asset);
        }
    };

    struct TradeData
    {
        std::string status;

        int64_t trade_id;

        User sender;
        Timestamp created;
        Timestamp expiriation;

        bool is_active;

        explicit TradeData(json j)
        {
            if (j.contains("status")) status = j["status"];
            if (j.contains("id")) trade_id = j["id"];
            if (j.contains("user")) sender = User(j["user"]);
            if (j.contains("created")) created = Timestamp(j["created"]);
            if (j.contains("expiration")) expiriation = Timestamp(j["expiration"]);
            if (j.contains("isActive")) is_active = j["isActive"];
        }

        TradeData() = default;
    };

    struct CanTradeWithResponse
    {
        std::string status;
        bool can_trade;

        explicit CanTradeWithResponse(json j)
        {
            if (j.contains("status")) status = j["status"];
            if (j.contains("canTrade")) can_trade = j["canTrade"];
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
        std::string Name;
        std::string DisplayName;

        long ID;
        long CreatorID;
        long ProductIdID;

        int Price;

        explicit GamePass(json j)
        {
            if (j.contains("name")) Name = j["name"];
            if (j.contains("displayName")) DisplayName = j["displayName"];
            if (j.contains("id")) ID = j["id"];
            if (j.contains("sellerId")) CreatorID = j["sellerId"];
            if (j.contains("productId")) ProductIdID = j["productId"];
            if (j.contains("price")) Price = j["price"];
        }

        GamePass() = default;
    };
    
    struct PlaceInfoResponse
    {
        std::string Name, SourceName;
        std::string Description, SourceDescription;
        std::string UniverseAvatarType;
        std::string Genre;

        long UniverseID, PlaceID;
        long CurrentPlayers;
        long Visits;
        long FavoritedCount;

        int Price;
        int MaxPlayers;

        User Creator;
        Timestamp Created;
        Timestamp Updated;
        
        bool IsGenreEnforced;
        bool CopyingAllowed;
        bool StudioAccessToApisAllowed;
        bool CreateVipServersAllowed;
        bool IsAllGenre;

        explicit PlaceInfoResponse(json j)
        {
            if (j.contains("name")) Name = j["name"];
            if (j.contains("description")) Description = j["description"];
            if (j.contains("sourceName")) SourceName = j["sourceName"];
            if (j.contains("sourceDescription")) SourceDescription = j["sourceDescription"];
            if (j.contains("universeAvatarType")) UniverseAvatarType = j["universeAvatarType"];
            if (j.contains("genre")) Genre = j["genre"];
            if (j.contains("id")) UniverseID = j["id"];
            if (j.contains("rootPlaceId")) PlaceID = j["rootPlaceId"];
            if (j.contains("playing")) CurrentPlayers = j["playing"];
            if (j.contains("visits")) Visits = j["visits"];
            if (j.contains("favoritedCount")) FavoritedCount = j["favoritedCount"];
            if (j.contains("price") && !(j["price"].is_null())) Price = j["price"];
            if (j.contains("maxPlayers")) MaxPlayers = j["maxPlayers"];
            if (j.contains("creator")) Creator = User(j["creator"]);
            if (j.contains("created")) Created = Timestamp(j["created"]);
            if (j.contains("updated")) Updated = Timestamp(j["updated"]);
            if (j.contains("isGenreEnforced")) IsGenreEnforced = j["isGenreEnforced"];
            if (j.contains("copyingAllowed")) CopyingAllowed = j["copyingAllowed"];
            if (j.contains("studioAccessToApisAllowed")) StudioAccessToApisAllowed = j["studioAccessToApisAllowed"];
            if (j.contains("createVipServersAllowed")) CreateVipServersAllowed = j["createVipServersAllowed"];
            if (j.contains("isAllGenre")) IsAllGenre = j["isAllGenre"];
        }

        PlaceInfoResponse() = default;
    };

    struct GroupWallPost
    {
        std::string Body;

        User Poster;

        Timestamp Created;
        Timestamp Updated;
        
        long PostID;

        explicit GroupWallPost(json j)
        {
            if (j.contains("body")) Body = j["body"];
            if (j.contains("poster")) Poster = User(j["poster"]);
            if (j.contains("created")) Created = Timestamp(j["created"]);
            if (j.contains("updated")) Updated = Timestamp(j["updated"]);
            if (j.contains("id")) PostID = j["id"];
        }

        GroupWallPost() = default;
    };

    struct GroupNamehistory
    {
        std::string Name;
        Timestamp Created;

        explicit GroupNamehistory(json j)
        {
            if (j.contains("name")) Name = j["name"];
            if (j.contains("created")) Created = Timestamp(j["created"]);
        }

        GroupNamehistory() = default;
    };

    struct GroupExperience
    {
        std::string Name;
        std::string Description;
        std::string CreatorType;

        Timestamp Created;
        Timestamp Updated;

        long CreatorID;
        long PlaceID;
        long UniverseID;
        long PlaceVisits;

        explicit GroupExperience(json j)
        {
            if (j.contains("name")) Name = j["name"];
            if (j.contains("description") && !(j["description"].is_null())) Description = j["description"];
            if (j.contains("creator")) { CreatorType = j["creator"]["type"]; CreatorID = j["creator"]["id"]; }
            if (j.contains("created")) Created = Timestamp(j["created"]);
            if (j.contains("updated")) Updated = Timestamp(j["updated"]);
            if (j.contains("id")) UniverseID = j["id"];
            if (j.contains("rootPlace")) PlaceID = j["id"];
            if (j.contains("placeVisits")) PlaceVisits = j["placeVisits"];
        }

        GroupExperience() = default;
    };


    struct FriendRequest
    {
        std::string OriginSourceType;

        Timestamp SentAt;

        long SenderID;
        long SourceUniverseID;

        explicit FriendRequest(json j)
        {
            if (j.contains("originSourceType")) OriginSourceType = j["originSourceType"];
            if (j.contains("sentAt")) SentAt = Timestamp(j["sentAt"]);
            if (j.contains("senderId")) SenderID = j["senderId"];
            if (j.contains("sourceUniverseId") && !(j["sourceUniverseId"].is_null())) SourceUniverseID = j["sourceUniverseId"];
        }

        FriendRequest() = default;
    };

    struct FriendRequestsResponse
    {
        std::vector<FriendRequest> FriendRequests;
        std::vector<User> SenderInfo;
        std::vector<std::string> MutualFriendsList;

        explicit FriendRequestsResponse(json j)
        {
            for (auto& i : j["data"])
            {
                FriendRequests.emplace_back(i["friendRequest"]);
                SenderInfo.emplace_back(i);
            }

            if (j.contains("mutualFriendsList") && !j["mutualFriendsList"].empty())
            {
                for (auto& i : j["mutualFriendsList"])
                {
                    MutualFriendsList.emplace_back(i);
                }
            }
        }

        FriendRequestsResponse() = default;
    };

    struct PhoneInfo
    {
        std::string CountryCode;
        std::string Prefix;
        std::string Phone;

        int VerificationCodeLength;

        bool IsVerified;
        bool CanBypassPasswordForPhoneUpdate;

        explicit PhoneInfo(json j)
        {
            CountryCode = j["countryCode"];
            Prefix = j["prefix"];
            Phone = j["phone"];
            VerificationCodeLength = j["verificationCodeLength"];
            IsVerified = j["isVerified"];
            CanBypassPasswordForPhoneUpdate = j["canBypassPasswordForPhoneUpdate"];
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
            for (auto& asset : j["assets"])
            {
                assets.emplace_back(asset);
            }
        }

        AvatarResponse() = default;
    };

    struct BirthdateResponse
    {
        int Year, Month, Day;

        explicit BirthdateResponse(json j)
        {
            Year = j["birthYear"];
            Month = j["birthMonth"];
            Day = j["birthDay"];
        }

        BirthdateResponse() = default;
    };

    struct InventoryAsset
    {   
        std::string Name;
        std::string AssetType;

        Timestamp Created;

        long AssetID;

        explicit InventoryAsset(json j)
        {
            if (j.contains("name") && !(j["name"].is_null())) Name = j["name"];
            if (j.contains("assetType") && !(j["assetType"].is_null())) AssetType = j["assetType"];
            if (j.contains("created") && !(j["created"].is_null())) Created = Timestamp(j["created"]);
            if (j.contains("assetId") && !(j["assetId"].is_null())) AssetID = j["assetId"];
        }

        InventoryAsset() = default;
    };

    struct UserPresence
    {
        std::string LastLocation;
        std::string GameId;

        Timestamp LastOnline;

        long PlaceID;
        long RootPlaceID;
        long UniverseID;
        long UserID;

        int UserPresenceType;

        explicit UserPresence(json j)
        {
            if (j.contains("lastLocation") && !(j["lastLocation"].is_null())) LastLocation = j["lastLocation"];
            if (j.contains("lastOnline") && !(j["lastOnline"].is_null())) LastOnline = Timestamp(j["lastOnline"]);
            if (j.contains("placeId") && !(j["placeId"].is_null())) PlaceID = j["placeId"];
            if (j.contains("rootPlaceId") && !(j["rootPlaceId"].is_null())) RootPlaceID = j["rootPlaceId"];
            if (j.contains("universeId") && !(j["universeId"].is_null())) UniverseID = j["universeId"];
            if (j.contains("userId") && !(j["userId"].is_null())) UserID = j["userId"];
            if (j.contains("userPresenceType") && !(j["userPresenceType"].is_null())) UserPresenceType = j["userPresenceType"];
            if (j.contains("gameId") && !(j["gameId"].is_null())) GameId = j["gameId"];
        }

        UserPresence() = default;
    };

    struct BadgeStats
    {
        long PastDayAwardedCount;
        long AwardedCount;
        int WinRatePercentage;

        explicit BadgeStats(json j)
        {
            if (j.contains("pastDayAwardedCount")) PastDayAwardedCount = j["pastDayAwardedCount"];
            if (j.contains("awardedCount")) AwardedCount = j["awardedCount"];
            if (j.contains("winRatePercentage")) WinRatePercentage = j["winRatePercentage"];
        }

        BadgeStats() = default;
    };

    struct Badge
    {
        std::string Name;
        std::string Description;
        std::string DisplayName;
        std::string DisplayDescription;
        std::string AwarderType;

        Timestamp Created;
        Timestamp Updated;

        BadgeStats Statistics;
        
        long IconImageId;
        long DisplayIconImageId;
        long AwarderId;

        bool Enabled;

        explicit Badge(json j)
        {
            if (j.contains("name")) Name = j["name"];
            if (j.contains("description")) Description = j["description"];
            if (j.contains("displayName")) DisplayName = j["displayName"];
            if (j.contains("displayDescription")) DisplayDescription = j["displayDescription"];
            if (j.contains("awarder")) AwarderType = j["awarder"]["type"];
            if (j.contains("created")) Created = Timestamp(j["created"]);
            if (j.contains("updated")) Updated = Timestamp(j["updated"]);
            if (j.contains("iconImageId")) IconImageId = j["iconImageId"];
            if (j.contains("displayIconImageId")) DisplayIconImageId = j["displayIconImageId"];
            if (j.contains("awarder")) AwarderId = j["awarder"]["id"];
            if (j.contains("enabled")) Enabled = j["enabled"];
            if (j.contains("statistics")) Statistics = BadgeStats(j["statistics"]);
        }

        Badge() = default;
    };

    struct Role
    {
        std::string Name;
        int Rank;
        long ID;

        explicit Role(json j)
        {
            if (j.contains("name")) Name = j["name"];
            if (j.contains("rank")) Rank = j["rank"];
            if (j.contains("id")) ID = j["id"];
        }

        Role() = default;
    };

    struct AuditItemActor
    {
        ShorthandUser user;
        Role role;

        explicit AuditItemActor(json j)
        {
            if (j.contains("user")) user = ShorthandUser(j["user"]);
            if (j.contains("role")) role = Role(j["role"]);
        }

        AuditItemActor() = default;
    };

    struct AuditItem
    {
        AuditItemActor actor;
        std::string ActionType;
        json Description;
        Timestamp Created;

        explicit AuditItem(json j)
        {
            if (j.contains("actor")) actor = AuditItemActor(j["actor"]);
            if (j.contains("actionType")) ActionType = j["actionType"];
            if (j.contains("description")) Description = j["description"];
            if (j.contains("created")) Created = Timestamp(j["created"]);
        }

        AuditItem() = default;
    };

    struct AuditPage
    {
        std::vector<AuditItem> Items;

        explicit AuditPage(json j)
        {
            if (j.contains("data"))
            {
                for (auto& item : j["data"])
                {
                    Items.push_back(AuditItem(item));
                }
            }
        }
    };

    struct GShout
    {
        std::string Body;
        User Poster;

        Timestamp Created;
        Timestamp Updated;

        explicit GShout(json j)
        {
            if (j.contains("body")) Body = j["body"];
            if (j.contains("poster")) Poster = User(j["poster"]);
            if (j.contains("created")) Created = Timestamp(j["created"]);
            if (j.contains("updated")) Updated = Timestamp(j["updated"]);
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
        long MemberCount;

        bool is_builders_club_only;
        bool is_public_entry_allowed;
        bool has_verified_badge;

        explicit Group(json j)
        {
            if (j.contains("name")) name = j["name"];
            if (j.contains("description")) description = j["description"];
            if (j.contains("owner")) owner = ShorthandUser(j["owner"]);
            if (j.contains("shout") && !(j["shout"].is_null())) shout = GShout(j["shout"]);
            if (j.contains("memberCount")) MemberCount = j["memberCount"];
            if (j.contains("id")) group_id = j["id"];
            if (j.contains("isBuildersClubOnly")) is_builders_club_only = j["isBuildersClubOnly"];
            if (j.contains("isPublicEntryAllowed")) is_public_entry_allowed = j["isPublicEntryAllowed"];
            if (j.contains("hasVerifiedBadge")) has_verified_badge = j["hasVerifiedBadge"];
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
        std::string TitleForViewer;

        bool IsDefaultTitle;

       explicit ChatConversationTitle(json j)
       {
           TitleForViewer = j["titleForViewer"];
           IsDefaultTitle = j["isDefaultTitle"];
       }

       ChatConversationTitle() {}
    };

    struct ChatConversation
    {
        long id;
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
            if (j.contains("id")) id = j["id"];
            if (j.contains("title")) title = j["title"];
            if (j.contains("initiator")) initiator = User(j["initiator"]);
            if (j.contains("hasUnreadMessages") && !j["hasUnreadMessages"].is_null()) has_unread_messages = j["hasUnreadMessages"];
            if (j.contains("participants"))
            {
                for (auto& user : j["participants"])
                    participants.emplace_back(user);
            }
            if (j.contains("conversationType")) conversation_type = j["conversationType"];
            if (j.contains("conversationTitle")) conversation_title = ChatConversationTitle(j["conversationTitle"]);
            if (j.contains("lastUpdated")) last_updated = Timestamp(j["lastUpdated"]);
            if (!j["conversationUniverse"].is_null()) conversation_universe = ChatConversationUniverse(j["conversationUniverse"]);
        }

        ChatConversation() = default;
    };

    struct ChatConversationsResponse
    {
        std::vector<ChatConversation> Conversations;

       ChatConversationsResponse(json j)
       {
            for (auto& conversation : j) 
                Conversations.emplace_back(conversation);
       }
    };

    struct FriendsOnline
    {
        std::string UserPresenceType;
        std::string UserLocationType;
        std::string lastLocation;
        std::string GameInstanceId;
        std::string Username;
        std::string DisplayName;

        long PlaceID;
        long UniverseID;
        long UID;

        Timestamp LastOnline;

        explicit FriendsOnline(json j)
        {
            if (j.contains("userPresenceType")) UserPresenceType = j["userPresenceType"];
            if (j.contains("userLocationType")) UserLocationType = j["userLocationType"];
            if (j.contains("lastLocation")) lastLocation = j["lastLocation"];
            if (j.contains("gameInstanceId")) GameInstanceId = j["gameInstanceId"];
            if (j.contains("name")) Username = j["name"];
            if (j.contains("displayName")) DisplayName = j["displayName"];
            if (j.contains("placeId")) PlaceID = j["placeId"];
            if (j.contains("universeId")) UniverseID = j["universeId"];
            if (j.contains("id")) UID = j["id"];
            if (j.contains("lastOnline")) LastOnline = Timestamp(j["lastOnline"]);
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
            for (auto& user : j["rejectedParticipants"])
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
            for (auto& user : j["rejectedParticipants"])
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
            date = Timestamp(j["date"]);
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
            date = Timestamp(j["date"]);
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

            for (auto& element : j["priceDataPoints"])
                price_data.emplace_back(element);

            for (auto& element : j["volumeDataPoints"])
                volume_data.emplace_back(element);
        }

        ResaleData() = default;
    };

    struct ResellerAgent
    {
        std::string Username;
        std::string Type;
        long UID;

        explicit ResellerAgent(json j)
        {
            Username = j["name"];
            Type = j["type"];
            UID = j["id"];
        }
        ResellerAgent() = default;
    };

    struct ResellerData
    {
        int userAssetId;
        int price;
        int serialNumber;

        ResellerAgent Seller;

        explicit ResellerData(json resellerData)
        {
            userAssetId = resellerData["userAssetId"];
            price = resellerData["price"];
            serialNumber = resellerData["serialNumber"];

            Seller = ResellerAgent(resellerData["seller"]);
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

        //https://github.com/ro-py/ro.py/blob/284b30dfef4c8117198b961c3b4b47c040da6af4/roblox/assets.py#L21 <3
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
            created = Timestamp(Data["Created"]);
            updated = Timestamp(Data["Updated"]);
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
        std::string ID;
        std::string AccessCode;

        int VIPServerID;
        int MaxPlayers;
        int Playing;
        int FPS;
        double Ping;
        Responses::User Owner;

        std::vector<std::string> PlayerTokens;
        explicit GameInstance(json instance)
        {
            if (instance.contains("id")) ID = instance["id"];
            if (instance.contains("maxPlayers")) MaxPlayers = instance["maxPlayers"];
            if (instance.contains("playing") && !instance["playing"].is_null()) Playing = instance["playing"];
            if (instance.contains("playerTokens"))
            {
                for (auto& element : instance["playerTokens"])
                {
                    PlayerTokens.emplace_back(element);
                }
            }
            if (instance.contains("fps")) FPS = instance["fps"];
            if (instance.contains("ping")) Ping = instance["ping"];
            if (instance.contains("vipServerId")) VIPServerID = instance["vipServerId"];
            if (instance.contains("accessCode")) AccessCode = instance["accessCode"];
            if (instance.contains("owner")) Owner = Responses::User(instance["owner"]);
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
            for (auto& message : conversation["chatMessages"])
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
            if (!response["content"].is_null()) content = response["content"];
            filtered_for_receivers = response["filteredForReceivers"];
            message_id = response["messageId"];
            if (!response["Sent"].is_null()) sent = Timestamp(response["sent"]);
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
            created = Timestamp(Data["Created"]);
            updated = Timestamp(Data["Updated"]);
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
}