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

        User(const User& other)
        {
            *this = other;
        }

        User& operator=(const User& other)
        {
            Username = other.Username;
            DisplayName = other.DisplayName;
            Description = other.Description;
            BuildersClubMembershipType = other.BuildersClubMembershipType;
            Created = other.Created;
            PresenceType = other.PresenceType;
            FriendFrequentScore = other.FriendFrequentScore;
            FriendFrequentRank = other.FriendFrequentRank;
            UID = other.UID;
            IsOnline = other.IsOnline;
            IsDeleted = other.IsDeleted;
            HasVerifiedBadge = other.HasVerifiedBadge;
            IsBanned = other.IsBanned;
            return *this;
        }

        User() = default;
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

    struct GetMessagesResponse
    {
        std::vector<ChatMessage> Messages;

        explicit GetMessagesResponse(json j)
        {
            if (!j.empty())
            {
                for (auto& i : j)
                {
                    Messages.push_back(ChatMessage(i));
                }
            }
        }

        GetMessagesResponse() = default;
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
               for (size_t i = 0; i < j["rejectedParticipants"].size(); i++)
               {
                   RejectedParticipants.push_back(RejectedParticipant(j["rejectedParticipants"][i])); //?
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
            for (size_t i = 0; i < j.size(); i++)
            {
                Links.push_back(GameSocialLink(j["data"][i]));
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
                for (auto& i : j["data"])
                    Outfits.push_back(GetOutfitsAsset(i));
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
                Assets.push_back(OutfitDetailsAsset(asset));
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

        TradeData Parse(json j)
        {
            TradeData t;

            if (j.contains("status")) t.Status = j["status"];
            if (j.contains("id")) t.TradeID = j["id"];
            if (j.contains("user")) t.Sender = User(j["user"]);
            if (j.contains("created")) t.Created = Timestamp(j["created"]);
            if (j.contains("expiration")) t.Expiriation = Timestamp(j["expiration"]);
            if (j.contains("isActive")) t.IsActive = j["isActive"];

            return t;
        }
    };

    struct GetTradesResponse
    {
        std::vector<TradeData> Trades;

        GetTradesResponse Parse(json j)
        {
            GetTradesResponse g;

            if (j.contains("data"))
            {
                for (size_t i = 0; i < j["data"].size(); i++)
                {
                    g.Trades.push_back(TradeData().Parse(j["data"][i]));
                }
            }
            return g;
        }
    };

    struct CanTradeWithResponse
    {
        std::string Status;
        bool CanTrade;

        CanTradeWithResponse Parse(json j)
        {
            CanTradeWithResponse c;

            if (j.contains("status")) c.Status = j["status"];
            if (j.contains("canTrade")) c.CanTrade = j["canTrade"];

            return c;
        }
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

        GamePass Parse(json j)
        {
            GamePass b;

            if (j.contains("name")) b.Name = j["name"];
            if (j.contains("displayName")) b.DisplayName = j["displayName"];
            if (j.contains("id")) b.ID = j["id"];
            if (j.contains("sellerId")) b.CreatorID = j["sellerId"];
            if (j.contains("productId")) b.ProductIdID = j["productId"];
            if (j.contains("price")) b.Price = j["price"];

            return b;
        }
    };

    struct GamePassesResponse
    {
        std::vector<GamePass> GamePasses;

        GamePassesResponse Parse(json j)
        {
            GamePassesResponse r;

            for (size_t i = 0; i < j["data"].size(); i++)
            {
                r.GamePasses.push_back(GamePass().Parse(j["data"][i]));
            }

            return r;
        }
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

        GroupWallPost Parse(json j)
        {
            GroupWallPost g;

            if (j.contains("body")) g.Body = j["body"];
            if (j.contains("poster")) g.Poster = User(j["poster"]);
            if (j.contains("created")) g.Created = Timestamp(j["created"]);
            if (j.contains("updated")) g.Updated = Timestamp(j["updated"]);
            if (j.contains("id")) g.PostID = j["id"];

            return g;
        }
    };

    struct GroupWallResponse
    {
        std::vector<GroupWallPost> Posts;

        GroupWallResponse Parse(json j)
        {
            GroupWallResponse g;

            for (size_t i = 0; i < j.size(); i++)
            {
                g.Posts.push_back(GroupWallPost().Parse(j["data"][i]));
            }

            return g;
        }
    };

    struct Namehistory
    {
        std::string Name;
        Timestamp Created;

        Namehistory Parse(json j)
        {
            Namehistory n;
            if (j.contains("name")) n.Name = j["name"];
            if (j.contains("created")) n.Created = Timestamp(j["created"]);
            return n;
        }
    };

    struct NameHistoryResponse
    {
        std::vector<Namehistory> NameHistory;

        NameHistoryResponse Parse(json j)
        {
            NameHistoryResponse n;

            for (size_t i = 0; i < j.size(); i++)
            {
                n.NameHistory.push_back(Namehistory().Parse(j["data"][i]));
            }

            return n;
        }
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

        GroupExperience Parse(json j)
        {
            GroupExperience e;

            if (j.contains("name")) e.Name = j["name"];
            if (j.contains("description") && !(j["description"].is_null())) e.Description = j["description"];
            if (j.contains("creator")) { e.CreatorType = j["creator"]["type"]; e.CreatorID = j["creator"]["id"]; }
            if (j.contains("created")) e.Created = Timestamp(j["created"]);
            if (j.contains("updated")) e.Updated = Timestamp(j["updated"]);
            if (j.contains("id")) e.UniverseID = j["id"];
            if (j.contains("rootPlace")) e.PlaceID = j["id"];
            if (j.contains("placeVisits")) e.PlaceVisits = j["placeVisits"];

            return e;
        }

    };

    struct GroupExperiencesResponse
    {
        std::vector<GroupExperience> Experiences;

        GroupExperiencesResponse Parse(json j)
        {
            GroupExperiencesResponse r;

            if (j.contains("data"))
            {
                for (size_t i = 0; i < j["data"].size(); i++)
                {
                    GroupExperience e = GroupExperience().Parse(j["data"][i]);
                    r.Experiences.push_back(e);
                }
            }

            return r;
        }
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

        explicit FriendRequestsResponse(json j)
        {
            for (size_t i = 0; i < j["data"].size(); i++)
            {
                FriendRequests.push_back(FriendRequest(j["data"][i]["friendRequest"]));
            }

            for (size_t i = 0; i < j.size(); i++)
            {
                SenderInfo.push_back(User(j["data"][i]["senderInfo"]));
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
                Assets.push_back(AvatarAsset(asset));
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

        InventoryAsset Parse(json j)
        {
            InventoryAsset a;

            if (j.contains("name") && !(j["name"].is_null())) a.Name = j["name"];
            if (j.contains("assetType") && !(j["assetType"].is_null())) a.AssetType = j["assetType"];
            if (j.contains("created") && !(j["created"].is_null())) a.Created = Timestamp(j["created"]);
            if (j.contains("assetId") && !(j["assetId"].is_null())) a.AssetID = j["assetId"];

            return a;
        }
    };

    struct InventoryResponse
    {
        std::vector<InventoryAsset> Assets;

        InventoryResponse Parse(json j)
        {
            InventoryResponse r;

            for (size_t i = 0; i < j.size(); i++)
            {
                r.Assets.push_back(InventoryAsset().Parse(j["data"][i]));
            }

            return r;
        }
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

        BadgeStats Parse(json j)
        {
            BadgeStats b;

            if (j.contains("pastDayAwardedCount")) b.PastDayAwardedCount = j["pastDayAwardedCount"];
            if (j.contains("awardedCount")) b.AwardedCount = j["awardedCount"];
            if (j.contains("winRatePercentage")) b.WinRatePercentage = j["winRatePercentage"];

            return b;
        }
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
            if (j.contains("statistics")) Statistics = BadgeStats().Parse(j["statistics"]);
        }

        Badge() = default;
    };

    struct GameBadges
    {
        std::vector<Badge> Badges;
        int Count = 0;

        explicit GameBadges(json j)
        {
            for (size_t i = 0; i < j.size(); i++)
            {
                Badges.push_back(Badge(j["data"][i]));
            }

            Count = j["data"].size();
        }

        GameBadges() = default;
    };

    struct UserBadgesResponse
    {
        std::vector<Badge> Badges;
        int Count = 0;

        explicit UserBadgesResponse(json j)
        {
            for (size_t i = 0; i < j.size(); i++)
            {
                Badges.push_back(Badge(j["data"][i]));
            }

            Count = j["data"].size();
        }

        UserBadgesResponse() = default;
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
    struct GShout
    {
        std::string Body;
        User Poster;

        Timestamp Created;
        Timestamp Updated;

        GShout Parse(json j)
        {
            GShout s;

            if (j.contains("body")) s.Body = j["body"];
            if (j.contains("poster")) s.Poster = User(j["poster"]);
            if (j.contains("created")) s.Created = Timestamp(j["lastUpdated"]);
            if (j.contains("updated")) s.Updated = Timestamp(j["lastUpdated"]);

            return s;
        }
    };

    struct Group
    {
        std::string Name;
        std::string Description;
        
        User Owner;

        GShout Shout;

        Role role;

        long GroupID;
        long MemberCount;

        bool IsBuildersClubOnly;
        bool IsPublicEntryAllowed;
        bool HasVerifiedBadge;

        Group Parse(json j)
        {
            Group g;

            if (j["group"].contains("name")) g.Name = j["group"]["name"];
            if (j["group"].contains("description")) g.Description = j["group"]["description"];
            if (j["group"].contains("owner")) g.Owner = User(j["group"]["owner"]);
            if (j["group"].contains("shout") && !(j["group"]["shout"].is_null())) g.Shout = GShout().Parse(j["group"]["shout"]);
            if (j["group"].contains("memberCount")) g.MemberCount = j["group"]["memberCount"];
            if (j["group"].contains("id")) g.GroupID = j["group"]["id"];
            if (j["group"].contains("isBuildersClubOnly")) g.IsBuildersClubOnly = j["group"]["isBuildersClubOnly"];
            if (j["group"].contains("isPublicEntryAllowed")) g.IsPublicEntryAllowed = j["group"]["isPublicEntryAllowed"];
            if (j["group"].contains("hasVerifiedBadge")) g.HasVerifiedBadge = j["group"]["hasVerifiedBadge"];

            
            if (j["role"].contains("name")) g.role.Name = j["role"]["name"];
            if (j["role"].contains("rank")) g.role.Rank = j["role"]["rank"];
            if (j["role"].contains("id")) g.role.ID = j["role"]["id"];

    
            return g;
        }
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
            if (j.contains("hasUnreadMessages")) HasUnreadMessages = j["hasUnreadMessages"];
            if (j.contains("participants"))
            {
                for (size_t i = 0; i < j["participants"].size(); i++)
                    Participants.push_back(User(j["participants"][i]));
            }
            if (j.contains("conversationType")) ConversationType = j["conversationType"];
            if (j.contains("conversationTitle")) ConversationTitle = ChatConversationTitle(j["conversationTitle"]);
            if (j.contains("lastUpdated")) LastUpdated = Timestamp(j["lastUpdated"]);
            if (!j["conversationUniverse"].is_null()) ConversationUniverse = ChatConversationUniverse(j["conversationUniverse"]);
        }
    };

    struct ChatConversationsResponse
    {
        std::vector<ChatConversation> Conversations;

       ChatConversationsResponse(json j)
       {
           for (size_t i = 0; i < j.size(); i++)
           {
               Conversations.push_back(ChatConversation(j[i]));
           }
       }
    };

    struct UserGroupsResponse
    {
        std::vector<Group> Groups;
        int Count;

        UserGroupsResponse Parse(json j)
        {
            UserGroupsResponse ugr;

            for (size_t i = 0; i < j.size(); i++)
            {
                ugr.Groups.push_back(Group().Parse(j["data"][i]));
            }

            Count = j["data"].size();

            return ugr;
        }
    };


    struct PastUsernames
    {
        std::vector<std::string> Usernames;

        PastUsernames Parse(json j)
        {
            PastUsernames p;

            if (j.contains("data"))
            {
                for (auto& i : j["data"])
                {
                    p.Usernames.push_back(i["name"]);
                }
            }

            if (p.Usernames.empty())
                p.Usernames.push_back("");

            return p;
        }
    };

    struct UserFavoriteExperiences
    {
        std::vector<Experience> Experiences;
        int Count;

        UserFavoriteExperiences Parse(json j)
        {
            UserFavoriteExperiences ufe;

            for (size_t i = 0; i < j.size(); i++)
            {
                Experience e = Experience(j["data"][i]);
                ufe.Experiences.push_back(e);
            }

            ufe.Count = j["data"].size();

            return ufe;
        }
    };

    struct UserExperienceResponse
    {
        std::vector<Experience> Experiences;
        int Count;

        UserExperienceResponse Parse(json j)
        {
            UserExperienceResponse r;

            for (size_t i = 0; i < j.size(); i++)
            {
                r.Experiences.push_back(Experience(j["data"][i]));
            }

            r.Count = j["data"].size();

            return r;
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

    struct FollowingsResponse
    {
        std::vector<User> Followings;
        int Count;

        FollowingsResponse Parse(json j)
        {
            FollowingsResponse f;

            for (size_t i = 0; i < j["data"].size(); i++)
            {
                f.Followings.push_back(User(j["data"][i]));
            }

            f.Count = j["data"].size();

            return f;
        }
    };

    struct FriendsResponse
    {
        std::vector<User> Friends;
        int Count;

        FriendsResponse Parse(json j)
        {
            FriendsResponse f;

            for (size_t i = 0; i < j["data"].size(); i++)
            {
                f.Friends.push_back(User(j["data"][i]));
            }

            f.Count = j["data"].size();

            return f;
        }
    };

    struct FollowersResponse
    {
        std::vector<User> Followers;
        int Count;

        FollowersResponse Parse(json j)
        {
            FollowersResponse f;
            for (size_t i = 0; i < j["data"].size(); i++)
            {
                f.Followers.push_back(User(j["data"][i]));
            }

            f.Count = j["data"].size();

            return f;
        }
    };

    struct PriceDataPoint
    {
        long Price;
        Timestamp timestamp;

        PriceDataPoint Parse(json j)
        {
            PriceDataPoint p;
            p.Price = j["value"];
            p.timestamp = Timestamp(j["date"]);
            return p;
        }
    };

    struct VolumeDataPoint
    {
        long Volume;
        Timestamp timestamp;

        VolumeDataPoint Parse(json j)
        {
            VolumeDataPoint v;
            v.Volume = j["value"];
            v.timestamp = Timestamp(j["date"]);
            return v;
        }
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
                PriceData.push_back(PriceDataPoint().Parse(element));

            for (auto& element : j["volumeDataPoints"])
                VolumeData.push_back(VolumeDataPoint().Parse(element));
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

        AssetCreator Parse(json creator)
        {
            AssetCreator c;
            c.Username = creator["Name"];
            c.Type = creator["CreatorType"];
            c.UID = creator["Id"];
            return c;
        }
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
            Creator = AssetCreator().Parse(Data["Creator"]);
            Price = Data["PriceInRobux"];
            Sales = Data["Sales"];
            CreatorID = Data["Creator"]["Id"];
            IsNew = Data["IsNew"];
            IsForSale = Data["IsForSale"];
            IsLimited = Data["IsLimited"];
            IsLimitedUnique = Data["IsLimitedUnique"];
            ProductID = Data["ProductId"];
        }

        AssetInfo(const AssetInfo& other)
        {
            *this = other;
        }

        AssetInfo() = default;

        AssetInfo& operator=(const AssetInfo& other)
        {
            Name = other.Name;
            Description = other.Description;
            AssetType = other.AssetType;
            CreatorName = other.CreatorName;
            CreatorType = other.CreatorType;
            Created = other.Created;
            Updated = other.Updated;
            Creator = other.Creator;
            Price = other.Price;
            Sales = other.Sales;
            CreatorID = other.CreatorID;
            IsNew = other.IsNew;
            IsForSale = other.IsForSale;
            IsLimited = other.IsLimited;
            IsLimitedUnique = other.IsLimitedUnique;
            ProductID = other.ProductID;
            return *this;
        }
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
                    PlayerTokens.push_back(element);
                }
            }
            if (instance.contains("fps")) FPS = instance["fps"];
            if (instance.contains("ping")) Ping = instance["ping"];
            if (instance.contains("vipServerId")) VIPServerID = instance["vipServerId"];
            if (instance.contains("accessCode")) AccessCode = instance["accessCode"];
            if (instance.contains("owner")) Owner = Responses::User(instance["owner"]);
        }
    };
}