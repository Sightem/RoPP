#pragma once

#include <string>
#include <chrono>
#include "json.hpp"

using json = nlohmann::json;

namespace Responses
{
    struct Timestamp
    {
        int year;
        int month;
        int day;
        int hour;
        int minute;
        int second;

        Timestamp Parse(std::string timestamp)
        {
            Timestamp t;
            t.year = std::stoi(timestamp.substr(0, 4));
            t.month = std::stoi(timestamp.substr(5, 2));
            t.day = std::stoi(timestamp.substr(8, 2));
            t.hour = std::stoi(timestamp.substr(11, 2));
            t.minute = std::stoi(timestamp.substr(14, 2));
            t.second = std::stoi(timestamp.substr(17, 2));
            return t;
        }

        std::string ToISO8601()
        {
            return std::to_string(year) + "-" + std::to_string(month) + "-" + std::to_string(day);
        }

        long long ToUnix()
        {
            std::tm t = {0};
            t.tm_year = year - 1900;
            t.tm_mon = month - 1;
            t.tm_mday = day;
            t.tm_hour = hour;
            t.tm_min = minute;
            t.tm_sec = second;
            std::time_t time = std::mktime(&t);
            return time;
        }
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

        User Parse(json j)
        {
            User u;
            if (j.contains("name")) u.Username = j["name"];
            if (j.contains("username")) u.Username = j["username"];
            if (j.contains("displayName")) u.DisplayName = j["displayName"];
            if (j.contains("description") && !(j["description"].is_null())) u.Description = j["description"];
            if (j.contains("created")) u.Created = Timestamp().Parse(j["created"]);
            if (j.contains("presenceType")) u.PresenceType = j["presenceType"];
            if (j.contains("friendFrequentScore")) u.FriendFrequentScore = j["friendFrequentScore"];
            if (j.contains("friendFrequentRank")) u.FriendFrequentRank = j["friendFrequentRank"];
            if (j.contains("id")) u.UID = j["id"];
            if (j.contains("userId")) u.UID = j["userId"];
            if (j.contains("isOnline")) u.IsOnline = j["isOnline"];
            if (j.contains("isDeleted")) u.IsDeleted = j["isDeleted"];
            if (j.contains("hasVerifiedBadge")) u.HasVerifiedBadge = j["hasVerifiedBadge"];
            if (j.contains("isBanned")) u.IsBanned = j["isBanned"];
            if (j.contains("buildersClubMembershipType")) u.BuildersClubMembershipType = j["buildersClubMembershipType"];

            return u;
        }
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

        Experience Parse(json j)
        {
            Experience e;

            if (j.contains("name") && !(j["name"].is_null())) e.Name = j["name"];
            if (j.contains("description") && !(j["description"].is_null())) e.Description = j["description"];
            if (j.contains("creator") && !(j["creator"]["type"].is_null())) e.CreatorType = j["creator"]["type"];
            if (j.contains("rootPlace") && !(j["rootPlace"]["type"].is_null())) e.PlaceType = j["rootPlace"]["type"];
            if (j.contains("created") && !(j["created"].is_null())) e.Created = Timestamp().Parse(j["created"]);
            if (j.contains("updated") && !(j["updated"].is_null())) e.Updated = Timestamp().Parse(j["updated"]);
            if (j.contains("creator") && !(j["creator"]["id"].is_null())) e.CreatorID = j["creator"]["id"];
            if (j.contains("rootPlace") && !(j["rootPlace"]["id"].is_null())) e.PlaceID = j["rootPlace"]["id"];
            if (j.contains("placeVisits") && !(j["placeVisits"].is_null())) e.PlaceVisits = j["placeVisits"];

            return e;
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
            if (j.contains("created")) n.Created = Timestamp().Parse(j["created"]);
            return n;
        }
    };

    struct NameHistoryResponse
    {
        std::vector<Namehistory> NameHistory;

        NameHistoryResponse Parse(json j)
        {
            NameHistoryResponse n;

            for (int i = 0; i < j.size(); i++)
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
            if (j.contains("created")) e.Created = Timestamp().Parse(j["created"]);
            if (j.contains("updated")) e.Updated = Timestamp().Parse(j["updated"]);
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
                for (int i = 0; i < j["data"].size(); i++)
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

        FriendRequest Parse(json j)
        {
            FriendRequest f;

            if (j.contains("originSourceType")) f.OriginSourceType = j["originSourceType"];
            if (j.contains("sentAt")) f.SentAt = Timestamp().Parse(j["sentAt"]);
            if (j.contains("senderId")) f.SenderID = j["senderId"];
            if (j.contains("sourceUniverseId") && !(j["sourceUniverseId"].is_null())) f.SourceUniverseID = j["sourceUniverseId"];

            return f;
        }

    };

    struct FriendRequestsResponse
    {
        std::vector<FriendRequest> FriendRequests;
        std::vector<User> SenderInfo;

        FriendRequestsResponse Parse(json j)
        {
            FriendRequestsResponse frr;

            for (int i = 0; i < j["data"].size(); i++)
            {
                frr.FriendRequests.push_back(FriendRequest().Parse(j["data"][i]["friendRequest"]));
            }

            for (int i = 0; i < j.size(); i++)
            {
                frr.SenderInfo.push_back(User().Parse(j["data"][i]));
            }

            return frr;
        }
    };

    struct PhoneInfo
    {
        std::string CountryCode;
        std::string Prefix;
        std::string Phone;

        int VerificationCodeLength;

        bool IsVerified;
        bool CanBypassPasswordForPhoneUpdate;

        PhoneInfo Parse(json j)
        {
            PhoneInfo p;

            if (j.contains("countryCode")) p.CountryCode = j["countryCode"];
            if (j.contains("prefix")) p.Prefix = j["prefix"];
            if (j.contains("phone")) p.Phone = j["phone"];
            if (j.contains("verificationCodeLength")) p.VerificationCodeLength = j["verificationCodeLength"];
            if (j.contains("isVerified")) p.IsVerified = j["isVerified"];
            if (j.contains("canBypassPasswordForPhoneUpdate")) p.CanBypassPasswordForPhoneUpdate = j["canBypassPasswordForPhoneUpdate"];

            return p;
        }

    };
    struct bodyColors
    {
        int headColorId;
        int torsoColorId;
        int rightArmColorId;
        int leftArmColorId;
        int rightLegColorId;
        int leftLegColorId;

        bodyColors Parse(json j)
        {
            bodyColors b;
            if (j.contains("headColorId")) b.headColorId = j["headColorId"];
            if (j.contains("torsoColorId")) b.torsoColorId = j["torsoColorId"];
            if (j.contains("rightArmColorId")) b.rightArmColorId = j["rightArmColorId"];
            if (j.contains("leftArmColorId")) b.leftArmColorId = j["leftArmColorId"];
            if (j.contains("rightLegColorId")) b.rightLegColorId = j["rightLegColorId"];
            if (j.contains("leftLegColorId")) b.leftLegColorId = j["leftLegColorId"];
            return b;
        }
    };
    
    struct AvatarAsset
    {
        std::string Name;
        std::string AssetTypeName;
        
        int AssetTypeID;

        long AssetID;
        long CurrentVersionID;

        AvatarAsset Parse(json j)
        {
            AvatarAsset a;

            if (j.contains("name")) a.Name = j["name"];
            if (j.contains("assetType"))  { a.AssetTypeID = j["assetType"]["id"]; a.AssetTypeName = j["assetType"]["name"]; }
            if (j.contains("id")) a.AssetID = j["id"];
            if (j.contains("currentVersionId")) a.CurrentVersionID = j["currentVersionId"];

            return a;
        }
    };

    struct AvatarScales
    {
        int height, width, depth, head, proportion, bodyType;

        AvatarScales Parse(json j)
        {
            AvatarScales a;

            if (j.contains("height")) a.height = j["height"];
            if (j.contains("width")) a.width = j["width"];
            if (j.contains("depth")) a.depth = j["depth"];
            if (j.contains("head")) a.head = j["head"];
            if (j.contains("proportion")) a.proportion = j["proportion"];
            if (j.contains("bodyType")) a.bodyType = j["bodyType"];

            return a;
        }
    };

    struct AvatarResponse
    {
        std::string AvatarType;

        bodyColors BodyColors;
        AvatarScales Scales;

        std::vector<AvatarAsset> Assets;

        AvatarResponse Parse(json j)
        {
            AvatarResponse a;

            if (j.contains("playerAvatarType")) a.AvatarType = j["playerAvatarType"];
            if (j.contains("bodyColors")) a.BodyColors = bodyColors().Parse(j["bodyColors"]);
            if (j.contains("scales")) a.Scales = AvatarScales().Parse(j["scales"]);
            if (j.contains("assets"))
            {
                for (auto& asset : j["assets"])
                {
                    a.Assets.push_back(AvatarAsset().Parse(asset));
                }
            }

            return a;
        }
    };

    struct CurrentlyWearing
    {
        std::vector<long> AssetIDs;

        CurrentlyWearing Parse(json j)
        {
            CurrentlyWearing c;

            if (j.contains("assetIds"))
            {
                for (auto& id : j["assetIds"])
                {
                    c.AssetIDs.push_back(id);
                }
            }

            return c;
        }
    };

    struct BirthdateResponse
    {
        int Year;
        int Month;
        int Day;

        BirthdateResponse Parse(json j)
        {
            BirthdateResponse b;
            if (j.contains("birthYear")) b.Year = j["birthYear"];
            if (j.contains("birthMonth")) b.Month = j["birthMonth"];
            if (j.contains("birthDay")) b.Day = j["birthDay"];
            return b;
        }
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
            if (j.contains("created") && !(j["created"].is_null())) a.Created = Timestamp().Parse(j["created"]);
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

            for (int i = 0; i < j.size(); i++)
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

        UserPresence Parse(json j)
        {
            UserPresence u;

            if (j.contains("lastLocation") && !(j["lastLocation"].is_null())) u.LastLocation = j["lastLocation"];
            if (j.contains("lastOnline") && !(j["lastOnline"].is_null())) u.LastOnline = Timestamp().Parse(j["lastOnline"]);
            if (j.contains("placeId") && !(j["placeId"].is_null())) u.PlaceID = j["placeId"];
            if (j.contains("rootPlaceId") && !(j["rootPlaceId"].is_null())) u.RootPlaceID = j["rootPlaceId"];
            if (j.contains("universeId") && !(j["universeId"].is_null())) u.UniverseID = j["universeId"];
            if (j.contains("userId") && !(j["userId"].is_null())) u.UserID = j["userId"];
            if (j.contains("userPresenceType") && !(j["userPresenceType"].is_null())) u.UserPresenceType = j["userPresenceType"];
            if (j.contains("gameId") && !(j["gameId"].is_null())) u.GameId = j["gameId"];

            return u;
        }
    };

    struct UserPresenceResponse
    {
        std::vector<UserPresence> UserPresences;

        UserPresenceResponse Parse(json j)
        {
            UserPresenceResponse u;

            for (int i = 0; i < j.size(); i++)
            {
                u.UserPresences.push_back(UserPresence().Parse(j["userPresences"][i]));
            }

            return u;
        }
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

        Badge Parse(json j)
        {
            Badge b;

            if (j.contains("name")) b.Name = j["name"];
            if (j.contains("description")) b.Description = j["description"];
            if (j.contains("displayName")) b.DisplayName = j["displayName"];
            if (j.contains("displayDescription")) b.DisplayDescription = j["displayDescription"];
            if (j.contains("awarder")) b.AwarderType = j["awarder"]["type"];
            if (j.contains("created")) b.Created = Timestamp().Parse(j["created"]);
            if (j.contains("updated")) b.Updated = Timestamp().Parse(j["updated"]);
            if (j.contains("iconImageId")) b.IconImageId = j["iconImageId"];
            if (j.contains("displayIconImageId")) b.DisplayIconImageId = j["displayIconImageId"];
            if (j.contains("awarder")) b.AwarderId = j["awarder"]["id"];
            if (j.contains("enabled")) b.Enabled = j["enabled"];
            if (j.contains("statistics")) b.Statistics = BadgeStats().Parse(j["statistics"]);

            return b;
        }
    };

    struct UserBadgesResponse
    {
        std::vector<Badge> Badges;
        int Count = 0;

        UserBadgesResponse Parse(json j)
        {
            UserBadgesResponse u;

            for (int i = 0; i < j.size(); i++)
            {
                u.Badges.push_back(Badge().Parse(j["data"][i]));
            }

            Count = j["data"].size();

            return u;
        }
    };

    struct Role
    {
        std::string Name;
        int Rank;
        long ID;

        Role Parse(json j)
        {
            Role r;

            if (j.contains("name")) r.Name = j["name"];
            if (j.contains("rank")) r.Rank = j["rank"];
            if (j.contains("id")) r.ID = j["id"];

            return r;
        }
    };
    struct Shout
    {
        std::string Body;
        User Poster;

        Timestamp Created;
        Timestamp Updated;

        Shout Parse(json j)
        {
            Shout s;

            if (j.contains("body")) s.Body = j["body"];
            if (j.contains("poster")) s.Poster = User().Parse(j["poster"]);
            if (j.contains("created")) s.Created = Timestamp().Parse(j["created"]);
            if (j.contains("updated")) s.Updated = Timestamp().Parse(j["updated"]);

            return s;
        }
    };

    struct Group
    {
        std::string Name;
        std::string Description;
        
        User Owner;

        Shout GShout;

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
            if (j["group"].contains("owner")) g.Owner = User().Parse(j["group"]["owner"]);
            if (j["group"].contains("shout") && !(j["group"]["shout"].is_null())) g.GShout = Shout().Parse(j["group"]["shout"]);
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

    struct UserGroupsResponse
    {
        std::vector<Group> Groups;
        int Count;

        UserGroupsResponse Parse(json j)
        {
            UserGroupsResponse ugr;

            for (int i = 0; i < j.size(); i++)
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

            for (int i = 0; i < j.size(); i++)
            {
                Experience e = Experience().Parse(j["data"][i]);
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

            for (int i = 0; i < j.size(); i++)
            {
                r.Experiences.push_back(Experience().Parse(j["data"][i]));
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

        FriendsOnline Parse(json j)
        {
            FriendsOnline f;
            if (j.contains("userPresenceType")) f.UserPresenceType = j["UserPresenceType"];
            if (j.contains("userLocationType")) f.UserLocationType = j["UserLocationType"];
            if (j.contains("lastLocation")) f.lastLocation = j["lastLocation"];
            if (j.contains("gameInstanceId")) f.GameInstanceId = j["gameInstanceId"];
            if (j.contains("name")) f.Username = j["name"];
            if (j.contains("displayName")) f.DisplayName = j["displayName"];
            if (j.contains("placeId")) f.PlaceID = j["placeId"];
            if (j.contains("universeId")) f.UniverseID = j["universeId"];
            if (j.contains("id")) f.UID = j["id"];
            if (j.contains("lastOnline")) f.LastOnline = Timestamp().Parse(j["lastOnline"]);

            return f;
        }
    };

    struct FriendsOnlineResponse
    {
        std::vector<FriendsOnline> Friends;

        FriendsOnlineResponse Parse(json j)
        {
            FriendsOnlineResponse f;
            for (int i = 0; i < j.size(); i++)
            {
                f.Friends.push_back(FriendsOnline().Parse(j["data"][i]));
            }
            return f;
        }
    };

    struct FollowingsResponse
    {
        std::vector<User> Followings;
        int Count;

        FollowingsResponse Parse(json j)
        {
            FollowingsResponse f;

            for (int i = 0; i < j["data"].size(); i++)
            {
                f.Followings.push_back(User().Parse(j["data"][i]));
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

            for (int i = 0; i < j["data"].size(); i++)
            {
                f.Friends.push_back(User().Parse(j["data"][i]));
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
            for (int i = 0; i < j["data"].size(); i++)
            {
                f.Followers.push_back(User().Parse(j["data"][i]));
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
            p.timestamp = Timestamp().Parse(j["date"]);
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
            v.timestamp = Timestamp().Parse(j["date"]);
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

        ResaleData Parse(json j)
        {
            ResaleData r;
            r.AssetStock = j["assetStock"];
            r.Sales = j["sales"];
            r.NumberRemaining = j["numberRemaining"];
            r.OriginalPrice = j["originalPrice"];
            r.RecentAveragePrice = j["recentAveragePrice"];

            for (int i = 0; i < j["priceDataPoints"].size(); i++)
            {
                r.PriceData.push_back(PriceDataPoint().Parse(j["priceDataPoints"][i]));
            }

            for (int i = 0; i < j["volumeDataPoints"].size(); i++)
            {
                r.VolumeData.push_back(VolumeDataPoint().Parse(j["volumeDataPoints"][i]));
            }

            return r;
        }
    };

    struct ResellerData
    {
        int userAssetId;
        int price;
        int serialNumber;

        std::string SellerUsername;
        std::string SellerType;
        long SellerId;

        ResellerData Parse(json resellerData)
        {
            ResellerData r;
            r.userAssetId = resellerData["userAssetId"];
            r.price = resellerData["price"];
            r.serialNumber = resellerData["serialNumber"];

            r.SellerUsername = resellerData["seller"]["name"];
            r.SellerType = resellerData["seller"]["type"];
            r.SellerId = resellerData["seller"]["id"];

            return r;
        }
    };

    struct Resellers
    {
        std::vector<ResellerData> sellers;

        Resellers Parse(json resellers)
        {
            Resellers r;
            for (int i = 0; i < resellers["data"].size(); i++)
            {
                r.sellers.push_back(ResellerData().Parse(resellers["data"][i]));
            }
            return r;
        }
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

        AssetInfo Parse(json Data)
        {
            AssetInfo info;

            info.Name = Data["Name"];
            info.Description = Data["Description"];
            info.AssetType = asset_type_names[Data["AssetTypeId"]];
            info.Created = Timestamp().Parse(Data["Created"]);
            info.Updated = Timestamp().Parse(Data["Updated"]);
            info.CreatorName = Data["Creator"]["Name"];
            info.CreatorType = Data["Creator"]["CreatorType"];
            info.Creator = AssetCreator().Parse(Data["Creator"]);
            info.Price = Data["PriceInRobux"];
            info.Sales = Data["Sales"];
            info.CreatorID = Data["Creator"]["Id"];
            info.IsNew = Data["IsNew"];
            info.IsForSale = Data["IsForSale"];
            info.IsLimited = Data["IsLimited"];
            info.IsLimitedUnique = Data["IsLimitedUnique"];
            info.ProductID = Data["ProductId"];

            return info;
        }
    };
}