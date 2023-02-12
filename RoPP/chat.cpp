#include "../include/ropp.h"
#include "../include/helper.h"
#include "../include/request.hpp"
#include "../include/responses.h"

using ordered_json = nlohmann::ordered_json;

Responses::ConversationAddResponse RoPP::Chat::AddUsersToConversation(std::vector<long> UserIDs)
{
    ordered_json Body;
    Body["participantUserIds"] = UserIDs;
    Body["conversationId"] = this->ConversationID;

    json res = Helper::MakeAuthedRobloxRequest
    (
        "https://chat.roblox.com/v2/add-to-conversation",
        "POST",
        this->Cookie,
        CSRF_REQUIRED,
        Body
    ).JsonObj;

    return Responses::ConversationAddResponse(res);
}

Responses::ChatSettings RoPP::Chat::GetChatSettings()
{
    json res = Helper::MakeAuthedRobloxRequest
    (
        "https://chat.roblox.com/v2/chat-settings",
        "GET",
        this->Cookie,
        CSRF_REQUIRED
    ).JsonObj;

    return Responses::ChatSettings(res);
}

std::vector<Responses::ChatMessage> RoPP::Chat::GetMessages(int PageSize, std::string ExclusiveStartMessageID)
{
    json res = Helper::MakeAuthedRobloxRequest
    (
        "https://chat.roblox.com/v2/get-messages?conversationId=" + std::to_string(this->ConversationID) + "&pageSize=" + std::to_string(PageSize) + (ExclusiveStartMessageID != "" ? "&exclusiveStartMessageId=" + ExclusiveStartMessageID : ""),
        "GET",
        this->Cookie,
        CSRF_REQUIRED
    ).JsonObj;

    std::vector<Responses::ChatMessage> Messages;
    if (!res.empty())
    {
        for (auto& i : res)
        {
            Messages.emplace_back(i);
        }
    }

    return Messages;
}

Responses::ChatConversationsResponse RoPP::Chat::GetConversations(std::vector<long> ConversationIDs)
{
    if (ConversationIDs.empty()) ConversationIDs = { this->ConversationID };

    std::string URL = "https://chat.roblox.com/v2/get-conversations?";
    for (size_t i = 0; i < ConversationIDs.size(); i++)
    {
        URL += "conversationIds=" + std::to_string(ConversationIDs[i]) + (i != ConversationIDs.size() - 1 ? "&" : "");
    }

    json res = Helper::MakeAuthedRobloxRequest
    (
        URL,
        "GET",
        this->Cookie,
        CSRF_REQUIRED
    ).JsonObj;
    
    return Responses::ChatConversationsResponse(res);
}

std::vector<Responses::RolloutFeature> RoPP::Chat::GetRolloutFeatures(std::vector<std::string> FeatureNames)
{
    std::string URL = "https://chat.roblox.com/v2/get-rollout-settings?";
    for (size_t i = 0; i < FeatureNames.size(); i++)
    {
        URL += "featureNames=" + FeatureNames[i] + (i != FeatureNames.size() - 1 ? "&" : "");
    }

    json res = Helper::MakeAuthedRobloxRequest
    (
        URL,
        "GET",
        this->Cookie,
        CSRF_NOT_REQUIRED
    ).JsonObj;

    std::vector<Responses::RolloutFeature> Features;
    for (auto& i : res["rolloutFeatures"])
    {
        Features.emplace_back(i);
    }

    return Features;
}

int RoPP::Chat::GetUnreadConversationCount()
{
    json res = Helper::MakeAuthedRobloxRequest
    (
        "https://chat.roblox.com/v2/get-unread-conversation-count",
        "GET",
        this->Cookie,
        CSRF_REQUIRED
    ).JsonObj;

    return res["count"];
}

std::vector<Responses::ChatConversationWithMessages> RoPP::Chat::GetUnreadMessages(std::vector<long> ConversationIDs, int PageSize)
{
    if (ConversationIDs.empty()) ConversationIDs = { this->ConversationID };

    std::string URL = "https://chat.roblox.com/v2/get-unread-messages?";
    for (size_t i = 0; i < ConversationIDs.size(); i++)
    {
        URL += "conversationIds=" + std::to_string(ConversationIDs[i]) + (i != ConversationIDs.size() - 1 ? "&" : "");
    }
    URL += "&pageSize=" + std::to_string(PageSize);

    json res = Helper::MakeAuthedRobloxRequest
    (
        URL,
        "GET",
        this->Cookie,
        CSRF_NOT_REQUIRED
    ).JsonObj;

    std::vector<Responses::ChatConversationWithMessages> Conversations;
    for (auto& i : res)
    {
        Conversations.emplace_back(i);
    }

    return Conversations;
}

std::vector<Responses::ChatConversation> RoPP::Chat::GetUserConversations(int PageNumber, int PageSize)
{
    json res = Helper::MakeAuthedRobloxRequest
    (
        "https://chat.roblox.com/v2/get-user-conversations?pageNumber=" + std::to_string(PageNumber) + "&pageSize=" + std::to_string(PageSize),
        "GET",
        this->Cookie,
        CSRF_REQUIRED
    ).JsonObj;

    std::vector<Responses::ChatConversation> Conversations;
    for (auto& i : res)
    {
        Conversations.emplace_back(i);
    }

    return Conversations;
}

bool RoPP::Chat::mark_conversation_as_read(std::string EndMessageId)
{
    ordered_json Body = 
    {
        {"conversationId", this->ConversationID},
        {"endMessageId", EndMessageId}
    };

    json res = Helper::MakeAuthedRobloxRequest
    (
        "https://chat.roblox.com/v2/mark-as-read",
        "POST",
        this->Cookie,
        CSRF_REQUIRED,
        Body
    ).JsonObj;

    return res["resultType"] == "Success";
}

bool RoPP::Chat::mark_conversation_as_seen(std::vector<long> ConversationIDs)
{
    if (ConversationIDs.empty()) ConversationIDs = { this->ConversationID };

    ordered_json Body =
    {
        {"conversationsToMarkSeen", ConversationIDs}
    };

    json res = Helper::MakeAuthedRobloxRequest
    (
        "https://chat.roblox.com/v2/mark-as-seen",
        "POST",
        this->Cookie,
        CSRF_REQUIRED,
        Body
    ).JsonObj;

    return res["resultType"] == "Success";
}

std::vector<Responses::ChatConversationWithMessages> RoPP::Chat::multi_get_latest_messages(std::vector<long> ConversationIDs, int PageSize)
{
    std::string URL = "https://chat.roblox.com/v2/multi-get-latest-messages?";
    for (size_t i = 0; i < ConversationIDs.size(); i++)
    {
        URL += "conversationIds=" + std::to_string(ConversationIDs[i]) + (i != ConversationIDs.size() - 1 ? "&" : "");
    }
    URL += "&pageSize=" + std::to_string(PageSize);

    json res = Helper::MakeAuthedRobloxRequest
    (
        URL,
        "GET",
        this->Cookie,
        CSRF_REQUIRED
    ).JsonObj;

    std::vector<Responses::ChatConversationWithMessages> Conversations;
    for (auto& i : res)
    {
        Conversations.emplace_back(i);
    }

    return Conversations;
}

Responses::RemoveFromConversationResponse RoPP::Chat::remove_from_conversation(long UserID)
{
    ordered_json Body =
    {
        {"participantUserId", UserID},
        {"conversationId", this->ConversationID}
    };

    json res = Helper::MakeAuthedRobloxRequest
    (
        "https://chat.roblox.com/v2/remove-from-conversation",
        "POST",
        this->Cookie,
        CSRF_REQUIRED,
        Body
    ).JsonObj;

    return Responses::RemoveFromConversationResponse(res);
}

Responses::RenameGroupConversationResponse RoPP::Chat::rename_group_conversation(std::string NewTitle)
{
    ordered_json Body =
    {
        {"conversationId", this->ConversationID},
        {"newTitle", NewTitle}
    };

    json res = Helper::MakeAuthedRobloxRequest
    (
        "https://chat.roblox.com/v2/rename-group-conversation",
        "POST",
        this->Cookie,
        CSRF_REQUIRED,
        Body
    ).JsonObj;

    return Responses::RenameGroupConversationResponse(res);
}

Responses::SendMessageResponse RoPP::Chat::send_message(std::string Message, bool IsExperienceInvite, std::vector<std::string> decorators)
{
    RoPP::Other other;

    ordered_json Body =
    {
        {"message", Message},
        {"isExperienceInvite", IsExperienceInvite},
        {"userId", other.get_uid_from_cookie(this->Cookie)},
        {"conversationId", this->ConversationID},
        {"decorators", decorators}
    };

    json res = Helper::MakeAuthedRobloxRequest
    (
        "https://chat.roblox.com/v2/send-message",
        "POST",
        this->Cookie,
        CSRF_REQUIRED,
        Body
    ).JsonObj;

    return Responses::SendMessageResponse(res);
}

std::string RoPP::Chat::update_user_typing_status(bool IsTyping)
{
    ordered_json Body =
    {
        {"conversationId", this->ConversationID},
        {"isTyping", IsTyping}
    };

    json res = Helper::MakeAuthedRobloxRequest
    (
        "https://chat.roblox.com/v2/update-user-typing-status",
        "POST",
        this->Cookie,
        CSRF_REQUIRED,
        Body
    ).JsonObj;

    return res["statusMessage"];
}

Responses::OneToOneConversationResponse RoPP::Chat::start_one_to_one_conversation(long UserID)
{
    ordered_json Body =
    {
        {"participantUserId", UserID}
    };

    json res = Helper::MakeAuthedRobloxRequest
    (
        "https://chat.roblox.com/v2/start-one-to-one-conversation",
        "POST",
        this->Cookie,
        CSRF_REQUIRED,
        Body
    ).JsonObj;

    return Responses::OneToOneConversationResponse(res);
}

Responses::StartGroupConversationResponse RoPP::Chat::start_group_conversation(std::vector<long> UserIDs, std::string Title)
{
    ordered_json Body =
    {
        {"participantUserIds", UserIDs},
        {"title", Title}
    };

    json res = Helper::MakeAuthedRobloxRequest
    (
        "https://chat.roblox.com/v2/start-group-conversation",
        "POST",
        this->Cookie,
        CSRF_REQUIRED,
        Body
    ).JsonObj;

    return Responses::StartGroupConversationResponse(res);
}