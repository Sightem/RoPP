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
        std::string Name;
        long ID;

        explicit AvatarAssetType(json j)
        {
            Name = j["name"];
            ID = j["id"];
        }

        AvatarAssetType() = default;
    };
    
    struct ChatSettings
    {
        bool ChatEnabled;
        bool IsActiveChatUser;
        bool IsConnectTabEnabled;
        
        explicit ChatSettings(json j)
        {
            if (j.contains("chatEnabled")) ChatEnabled = j["chatEnabled"];
            if (j.contains("isActiveChatUser")) IsActiveChatUser = j["isActiveChatUser"];
            if (j.contains("isConnectTabEnabled")) IsConnectTabEnabled = j["isConnectTabEnabled"];
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
        std::string RejectedReason;
        std::string Type;
        std::string Name;
        std::string DisplayName;

        long TargetID;

        bool HasVerifiedBadge;

        explicit RejectedParticipant(json j)
        {
            if (j.contains("rejectedReason")) RejectedReason = j["rejectedReason"];
            if (j.contains("type")) Type = j["type"];
            if (j.contains("name")) Name = j["name"];
            if (j.contains("displayName")) DisplayName = j["displayName"];
            if (j.contains("targetId")) TargetID = j["targetId"];
            if (j.contains("hasVerifiedBadge")) HasVerifiedBadge = j["hasVerifiedBadge"];
        }

        RejectedParticipant() = default;
    };
    struct ChatMessage
    {

        std::string ID;
        std::string SenderType;
        std::string MessageType;
        std::string Content;

        Timestamp Sent;
        bool Read;

        long SenderTargetID;

        explicit ChatMessage(json j)
        {
            if (j.contains("id")) ID = j["id"];
            if (j.contains("senderType")) SenderType = j["senderType"];
            if (j.contains("messageType")) MessageType = j["messageType"];
            if (j.contains("content")) Content = j["content"];
            if (j.contains("sent")) Sent = Timestamp(j["sent"]);
            if (j.contains("read")) Read = j["read"];
            if (j.contains("senderTargetId")) SenderTargetID = j["senderTargetId"];
        }

        ChatMessage() = default;
    };

    struct GroupRole
    {
        std::string Name;
        long id;
        int Rank;
        int MemberCount;

        explicit GroupRole(json j)
        {
            id = j["id"];
            Name = j["name"];
            Rank = j["rank"];
            if (j.contains("memberCount"))
            {
                MemberCount = j["memberCount"];
            }
        }

        GroupRole() = default;
    };

    struct GroupRoles
    {
        int64_t GroupID;
        std::vector<GroupRole> Roles;

        explicit GroupRoles(json j)
        {
            GroupID = j["groupId"];
            for (auto& i : j["roles"])
            {
                Roles.emplace_back(i);
            }
        }

        GroupRoles() = default;
    };

    struct ChangeRoleResponse
    {
        GroupRole OldRole;
        GroupRole NewRole;
    };

    struct ConversationAddResponse
    {
        std::string ResultType;
        std::string StatusMessage;
        long ConversationID;

        std::vector<RejectedParticipant> RejectedParticipants;

       explicit ConversationAddResponse(json j)
       {
           if (j.contains("resultType")) ResultType = j["resultType"];
           if (j.contains("statusMessage")) StatusMessage = j["statusMessage"];
           if (j.contains("conversationId")) ConversationID = j["conversationId"];

           if (j.contains("rejectedParticipants") && !j["rejectedParticipants"].empty())
           {
                for (auto& i : j["rejectedParticipants"])
                {
                    RejectedParticipants.emplace_back(i);
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
        int headColorId, torsoColorId, rightArmColorId, leftArmColorId, rightLegColorId, leftLegColorId;

        explicit BodyColors(json j)
        {
            if (j.contains("headColorId")) headColorId = j["headColorId"];
            if (j.contains("torsoColorId")) torsoColorId = j["torsoColorId"];
            if (j.contains("rightArmColorId")) rightArmColorId = j["rightArmColorId"];
            if (j.contains("leftArmColorId")) leftArmColorId = j["leftArmColorId"];
            if (j.contains("rightLegColorId")) rightLegColorId = j["rightLegColorId"];
            if (j.contains("leftLegColorId")) leftLegColorId = j["leftLegColorId"];
        }

        BodyColors() = default;
    };


    struct OutfitDetailsAsset
    {
        std::string Name;
        
        AvatarAssetType AssetType;

        long AssetID;
        long CurrentVersionID;

        explicit OutfitDetailsAsset(json j)
        {
            Name = j["name"];
            AssetType = AvatarAssetType(j["assetType"]);
            AssetID = j["id"];
            CurrentVersionID = j["currentVersion"];
        }

        OutfitDetailsAsset() = default;
    };
    
    struct GetOutfitsAsset
    {
        std::string Name;
        long ID;
        bool IsEditable;

        explicit GetOutfitsAsset(json j)
        {
            if (j.contains("name")) Name = j["name"];
            if (j.contains("id")) ID = j["id"];
            if (j.contains("isEditable")) IsEditable = j["isEditable"];
        }

        GetOutfitsAsset() = default;
    };

    struct GetOutfitsResponse
    {
        std::vector<GetOutfitsAsset> Outfits;
        int total;

        explicit GetOutfitsResponse(json j)
        {
            if (j.contains("data"))
            {
                for (auto& i : j["data"]) Outfits.emplace_back(i);
            }
            if (j.contains("total")) total = j["total"];
        }

        GetOutfitsResponse() = default;
    };

    struct AvatarScales
    {
        int height, width, depth, head, proportion, bodyType;

        explicit AvatarScales(json j)
        {
            if (j.contains("height")) height = j["height"];
            if (j.contains("width")) width = j["width"];
            if (j.contains("depth")) depth = j["depth"];
            if (j.contains("head")) head = j["head"];
            if (j.contains("proportion")) proportion = j["proportion"];
            if (j.contains("bodyType")) bodyType = j["bodyType"];
        }

        AvatarScales() = default;
    };

    struct OutfitDetailsResponse
    {
        std::string Name;
        std::string PlayerAvatarType;
        std::string OutfitType;

        long ID;

        std::vector<OutfitDetailsAsset> Assets;
        BodyColors Colors;
        AvatarScales Scales;

        bool IsEditable;

        explicit OutfitDetailsResponse(json j)
        {
            if (j.contains("name")) Name = j["name"];
            if (j.contains("playerAvatarType")) PlayerAvatarType = j["playerAvatarType"];
            if (j.contains("outfitType")) OutfitType = j["outfitType"];
            if (j.contains("id")) ID = j["id"];
            if (j.contains("bodyColors")) Colors = BodyColors(j["bodyColors"]);
            if (j.contains("scale")) Scales = AvatarScales(j["scale"]);
            if (j.contains("isEditable")) IsEditable = j["isEditable"];

            for (auto& asset : j["assets"])
                Assets.emplace_back(asset);
        }
    };

    struct TradeData
    {
        std::string Status;

        long TradeID;

        User Sender;
        Timestamp Created;
        Timestamp Expiriation;

        bool IsActive;

        explicit TradeData(json j)
        {
            if (j.contains("status")) Status = j["status"];
            if (j.contains("id")) TradeID = j["id"];
            if (j.contains("user")) Sender = User(j["user"]);
            if (j.contains("created")) Created = Timestamp(j["created"]);
            if (j.contains("expiration")) Expiriation = Timestamp(j["expiration"]);
            if (j.contains("isActive")) IsActive = j["isActive"];
        }

        TradeData() = default;
    };

    struct CanTradeWithResponse
    {
        std::string Status;
        bool CanTrade;

        explicit CanTradeWithResponse(json j)
        {
            if (j.contains("status")) Status = j["status"];
            if (j.contains("canTrade")) CanTrade = j["canTrade"];
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
        std::string Name;

        AvatarAssetType AssetType;

        long AssetID;
        long CurrentVersionID;

        explicit AvatarAsset(json j)
        {
            Name = j["name"];
            AssetType = AvatarAssetType(j["assetType"]);
            AssetID = j["id"];
            CurrentVersionID = j["currentVersionId"];
        }

        AvatarAsset() = default;
    };

    struct AvatarResponse
    {
        std::string AvatarType;

        BodyColors Colors;
        AvatarScales Scales;

        std::vector<AvatarAsset> Assets;

        explicit AvatarResponse(json j)
        {
            AvatarType = j["playerAvatarType"];
            Colors = BodyColors(j["bodyColors"]);
            Scales = AvatarScales(j["scales"]);
            for (auto& asset : j["assets"])
            {
                Assets.emplace_back(asset);
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
        std::string Name;
        std::string Description;
        
        User Owner;

        GShout Shout;

        int64_t GroupID;
        long MemberCount;

        bool IsBuildersClubOnly;
        bool IsPublicEntryAllowed;
        bool HasVerifiedBadge;

        explicit Group(json j)
        {
            if (j.contains("name")) Name = j["name"];
            if (j.contains("description")) Description = j["description"];
            if (j.contains("owner")) Owner = User(j["owner"]);
            if (j.contains("shout") && !(j["shout"].is_null())) Shout = GShout(j["shout"]);
            if (j.contains("memberCount")) MemberCount = j["memberCount"];
            if (j.contains("id")) GroupID = j["id"];
            if (j.contains("isBuildersClubOnly")) IsBuildersClubOnly = j["isBuildersClubOnly"];
            if (j.contains("isPublicEntryAllowed")) IsPublicEntryAllowed = j["isPublicEntryAllowed"];
            if (j.contains("hasVerifiedBadge")) HasVerifiedBadge = j["hasVerifiedBadge"];
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
        long UniverseId;
        long RootPlaceId;

        explicit ChatConversationUniverse(json j)
        {
            UniverseId = j["universeId"];
            RootPlaceId = j["rootPlaceId"];
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
        long ID;
        std::string Title;
        User Initiator;
        bool HasUnreadMessages;
        std::vector<User> Participants;
        std::string ConversationType;
        ChatConversationTitle ConversationTitle;
        Timestamp LastUpdated;
        ChatConversationUniverse ConversationUniverse;

        ChatConversation(json j)
        {
            if (j.contains("id")) ID = j["id"];
            if (j.contains("title")) Title = j["title"];
            if (j.contains("initiator")) Initiator = User(j["initiator"]);
            if (j.contains("hasUnreadMessages") && !j["hasUnreadMessages"].is_null()) HasUnreadMessages = j["hasUnreadMessages"];
            if (j.contains("participants"))
            {
                for (auto& user : j["participants"])
                    Participants.emplace_back(user);
            }
            if (j.contains("conversationType")) ConversationType = j["conversationType"];
            if (j.contains("conversationTitle")) ConversationTitle = ChatConversationTitle(j["conversationTitle"]);
            if (j.contains("lastUpdated")) LastUpdated = Timestamp(j["lastUpdated"]);
            if (!j["conversationUniverse"].is_null()) ConversationUniverse = ChatConversationUniverse(j["conversationUniverse"]);
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
        ChatConversation Conversation;
        std::vector<User> RejectedParticipants;
        std::string ResultType;
        std::string StatusMessage;

        explicit OneToOneConversationResponse(json j)
        {
            Conversation = ChatConversation(j["conversation"]);
            for (auto& user : j["rejectedParticipants"])
                RejectedParticipants.emplace_back(user);
            ResultType = j["resultType"];
            StatusMessage = j["statusMessage"];
        }

        OneToOneConversationResponse() = default;
    };

    struct StartGroupConversationResponse
    {
        ChatConversation Conversation;
        std::vector<User> RejectedParticipants;
        std::string ResultType;
        std::string StatusMessage;

        explicit StartGroupConversationResponse(json j)
        {
            Conversation = ChatConversation(j["conversation"]);
            for (auto& user : j["rejectedParticipants"])
                RejectedParticipants.emplace_back(user);
            ResultType = j["resultType"];
            StatusMessage = j["statusMessage"];
        }

        StartGroupConversationResponse() = default;
    };
    struct PriceDataPoint
    {
        long Price;
        Timestamp timestamp;

        explicit PriceDataPoint(json j)
        {
            Price = j["value"];
            timestamp = Timestamp(j["date"]);
        }

        PriceDataPoint() = default;
    };

    struct VolumeDataPoint
    {
        long Volume;
        Timestamp timestamp;

        explicit VolumeDataPoint(json j)
        {
            Volume = j["value"];
            timestamp = Timestamp(j["date"]);
        }

        VolumeDataPoint() = default;
    };
    struct ResaleData
    {
        int AssetStock;
        int Sales;
        int NumberRemaining;
        int OriginalPrice;

        long RecentAveragePrice;

        std::vector<PriceDataPoint> PriceData;
        std::vector<VolumeDataPoint> VolumeData;

        explicit ResaleData(json j)
        {
            AssetStock = j["assetStock"];
            Sales = j["sales"];
            NumberRemaining = j["numberRemaining"];
            OriginalPrice = j["originalPrice"];
            RecentAveragePrice = j["recentAveragePrice"];

            for (auto& element : j["priceDataPoints"])
                PriceData.emplace_back(element);

            for (auto& element : j["volumeDataPoints"])
                VolumeData.emplace_back(element);
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
        std::string Username;
        std::string Type;
        long UID;

        explicit AssetCreator(json creator)
        {
            Username = creator["Name"];
            Type = creator["CreatorType"];
            UID = creator["Id"];
        }

        AssetCreator() = default;
    };

    struct AssetInfo
    {
        std::string Name;
        std::string Description;
        std::string AssetType;
        std::string CreatorName;
        std::string CreatorType;

        Timestamp Created;
        Timestamp Updated;

        AssetCreator Creator;

        int Price;

        long Sales;
        long CreatorID;
        long ProductID;

        bool IsNew;
        bool IsForSale;
        bool IsLimited;
        bool IsLimitedUnique;

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
            Name = Data["Name"];
            Description = Data["Description"];
            AssetType = asset_type_names[Data["AssetTypeId"]];
            Created = Timestamp(Data["Created"]);
            Updated = Timestamp(Data["Updated"]);
            CreatorName = Data["Creator"]["Name"];
            CreatorType = Data["Creator"]["CreatorType"];
            Creator = AssetCreator(Data["Creator"]);
            Price = Data["PriceInRobux"];
            Sales = Data["Sales"];
            CreatorID = Data["Creator"]["Id"];
            IsNew = Data["IsNew"];
            IsForSale = Data["IsForSale"];
            IsLimited = Data["IsLimited"];
            IsLimitedUnique = Data["IsLimitedUnique"];
            ProductID = Data["ProductId"];
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
        std::string FeatureName;
        bool IsRolloutEnabled;

        explicit RolloutFeature(json feature)
        {
            FeatureName = feature["featureName"];
            IsRolloutEnabled = feature["isRolloutEnabled"];
        }
    };

    struct ChatConversationWithMessages
    {
        long ConversationId;
        std::vector<Responses::ChatMessage> Messages;

        explicit ChatConversationWithMessages(json conversation)
        {
            ConversationId = conversation["conversationId"];
            for (auto& message : conversation["chatMessages"])
            {
                Messages.emplace_back(message);
            }
        }
    };

    struct RemoveFromConversationResponse
    {
        long ConversationId;
        std::string ResultType;
        std::string StatusMessage;

        explicit RemoveFromConversationResponse(json response)
        {
            ConversationId = response["conversationId"];
            ResultType = response["resultType"];
            StatusMessage = response["statusMessage"];
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
        std::string Content;
        bool FilteredForReceivers;
        std::string MessageId;
        Timestamp Sent;
        std::string MessageType;
        std::string ResultType;
        std::string StatusMessage;

        explicit SendMessageResponse(json response)
        {
            if (!response["content"].is_null()) Content = response["content"];
            FilteredForReceivers = response["filteredForReceivers"];
            MessageId = response["messageId"];
            if (!response["Sent"].is_null()) Sent = Timestamp(response["sent"]);
            MessageType = response["messageType"];
            ResultType = response["resultType"];
            StatusMessage = response["statusMessage"];
        }

        SendMessageResponse() = default;
    };
}