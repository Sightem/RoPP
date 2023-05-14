#include "../include/ropp.h"
#include "../include/helper.h"
#include "../include/request.hpp"
#include "../include/responses.h"

Responses::ConversationAddResponse RoPP::Chat::add_users_to_conversation(std::vector<int64_t> user_ids)
{
    ordered_json Body = 
    {
        {"participantUserIds", user_ids},
        {"conversationId", this->m_ConversationID}
    };

    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://chat.roblox.com/v2/add-to-conversation",
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED,
        Body
    ).JsonObj;

    return Responses::ConversationAddResponse(res);
}

Responses::ChatSettings RoPP::Chat::get_chat_settings()
{
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://chat.roblox.com/v2/chat-settings",
        "GET",
        this->m_Cookie,
        CSRF_REQUIRED
    ).JsonObj;

    return Responses::ChatSettings(res);
}

std::vector<Responses::ChatMessage> RoPP::Chat::get_messages(int32_t page_size, std::string exclusive_start_messageid)
{
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://chat.roblox.com/v2/get-messages?conversationId=" + std::to_string(this->m_ConversationID) + "&pageSize=" + std::to_string(page_size) + (exclusive_start_messageid != "" ? "&exclusiveStartMessageId=" + exclusive_start_messageid : ""),
        "GET",
        this->m_Cookie,
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

Responses::ChatConversationsResponse RoPP::Chat::get_conversations(std::vector<int64_t> conversation_ids)
{
    if (conversation_ids.empty()) conversation_ids = { this->m_ConversationID };

    std::string URL = "https://chat.roblox.com/v2/get-conversations?";
    for (size_t i = 0; i < conversation_ids.size(); i++)
    {
        URL += "conversationIds=" + std::to_string(conversation_ids[i]) + (i != conversation_ids.size() - 1 ? "&" : "");
    }

    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        URL,
        "GET",
        this->m_Cookie,
        CSRF_REQUIRED
    ).JsonObj;
    
    return Responses::ChatConversationsResponse(res);
}

std::vector<Responses::RolloutFeature> RoPP::Chat::get_rollout_features(std::vector<std::string> feature_names)
{
    std::string URL = "https://chat.roblox.com/v2/get-rollout-settings?";
    for (size_t i = 0; i < feature_names.size(); i++)
    {
        URL += "featureNames=" + feature_names[i] + (i != feature_names.size() - 1 ? "&" : "");
    }

    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        URL,
        "GET",
        this->m_Cookie,
        CSRF_NOT_REQUIRED
    ).JsonObj;

    std::vector<Responses::RolloutFeature> features;
    for (auto& i : res["rolloutFeatures"])
    {
        features.emplace_back(i);
    }

    return features;
}

int64_t RoPP::Chat::get_unread_conversation_count()
{
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://chat.roblox.com/v2/get-unread-conversation-count",
        "GET",
        this->m_Cookie,
        CSRF_REQUIRED
    ).JsonObj;

    return res["count"];
}

std::vector<Responses::ChatConversationWithMessages> RoPP::Chat::get_unread_messages(std::vector<int64_t> conversation_ids, int32_t page_size)
{
    if (conversation_ids.empty()) conversation_ids = { this->m_ConversationID };

    std::string URL = "https://chat.roblox.com/v2/get-unread-messages?";
    for (size_t i = 0; i < conversation_ids.size(); i++)
    {
        URL += "conversationIds=" + std::to_string(conversation_ids[i]) + (i != conversation_ids.size() - 1 ? "&" : "");
    }
    URL += "&pageSize=" + std::to_string(page_size);

    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        URL,
        "GET",
        this->m_Cookie,
        CSRF_NOT_REQUIRED
    ).JsonObj;

    std::vector<Responses::ChatConversationWithMessages> Conversations;
    for (auto& i : res)
    {
        Conversations.emplace_back(i);
    }

    return Conversations;
}

std::vector<Responses::ChatConversation> RoPP::Chat::get_user_conversations(int32_t page_number, int32_t page_size)
{
    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://chat.roblox.com/v2/get-user-conversations?pageNumber=" + std::to_string(page_number) + "&pageSize=" + std::to_string(page_size),
        "GET",
        this->m_Cookie,
        CSRF_REQUIRED
    ).JsonObj;

    std::vector<Responses::ChatConversation> conversations;
    for (auto& i : res)
    {
        conversations.emplace_back(i);
    }

    return conversations;
}

bool RoPP::Chat::mark_conversation_as_read(std::string end_message_id)
{
    ordered_json Body = 
    {
        {"conversationId", this->m_ConversationID},
        {"endMessageId", end_message_id}
    };

    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://chat.roblox.com/v2/mark-as-read",
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED,
        Body
    ).JsonObj;

    return res["resultType"] == "Success";
}

bool RoPP::Chat::mark_conversation_as_seen(std::vector<int64_t> conversation_ids)
{
    if (conversation_ids.empty()) conversation_ids = { this->m_ConversationID };

    ordered_json Body =
    {
        {"conversationsToMarkSeen", conversation_ids}
    };

    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://chat.roblox.com/v2/mark-as-seen",
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED,
        Body
    ).JsonObj;

    return res["resultType"] == "Success";
}

std::vector<Responses::ChatConversationWithMessages> RoPP::Chat::multi_get_latest_messages(std::vector<int64_t> conversation_ids, int32_t page_size)
{
    std::string URL = "https://chat.roblox.com/v2/multi-get-latest-messages?";
    for (size_t i = 0; i < conversation_ids.size(); i++)
    {
        URL += "conversationIds=" + std::to_string(conversation_ids[i]) + (i != conversation_ids.size() - 1 ? "&" : "");
    }
    URL += "&pageSize=" + std::to_string(page_size);

    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        URL,
        "GET",
        this->m_Cookie,
        CSRF_REQUIRED
    ).JsonObj;

    std::vector<Responses::ChatConversationWithMessages> conversations;
    for (auto& i : res)
    {
        conversations.emplace_back(i);
    }

    return conversations;
}

Responses::RemoveFromConversationResponse RoPP::Chat::remove_from_conversation(int64_t user_id)
{
    ordered_json Body =
    {
        {"participantUserId", user_id},
        {"conversationId", this->m_ConversationID}
    };

    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://chat.roblox.com/v2/remove-from-conversation",
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED,
        Body
    ).JsonObj;

    return Responses::RemoveFromConversationResponse(res);
}

Responses::RenameGroupConversationResponse RoPP::Chat::rename_group_conversation(std::string NewTitle)
{
    ordered_json Body =
    {
        {"conversationId", this->m_ConversationID},
        {"newTitle", NewTitle}
    };

    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://chat.roblox.com/v2/rename-group-conversation",
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED,
        Body
    ).JsonObj;

    return Responses::RenameGroupConversationResponse(res);
}

Responses::SendMessageResponse RoPP::Chat::send_message(std::string message, bool is_experience_invite, std::vector<std::string> decorators)
{
    RoPP::Other other;

    ordered_json Body =
    {
        {"message", message},
        {"isExperienceInvite", is_experience_invite},
        {"userId", other.get_uid_from_cookie(this->m_Cookie)},
        {"conversationId", this->m_ConversationID},
        {"decorators", decorators}
    };

    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://chat.roblox.com/v2/send-message",
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED,
        Body
    ).JsonObj;

    return Responses::SendMessageResponse(res);
}

std::string RoPP::Chat::update_user_typing_status(bool is_typing)
{
    ordered_json Body =
    {
        {"conversationId", this->m_ConversationID},
        {"isTyping", is_typing}
    };

    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://chat.roblox.com/v2/update-user-typing-status",
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED,
        Body
    ).JsonObj;

    return res["statusMessage"];
}

Responses::OneToOneConversationResponse RoPP::Chat::start_one_to_one_conversation(int64_t user_id)
{
    ordered_json Body =
    {
        {"participantUserId", user_id}
    };

    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://chat.roblox.com/v2/start-one-to-one-conversation",
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED,
        Body
    ).JsonObj;

    return Responses::OneToOneConversationResponse(res);
}

Responses::StartGroupConversationResponse RoPP::Chat::start_group_conversation(std::vector<int64_t> UserIDs, std::string Title)
{
    ordered_json Body =
    {
        {"participantUserIds", UserIDs},
        {"title", Title}
    };

    ordered_json res = Helper::MakeAuthedRobloxRequest
    (
        "https://chat.roblox.com/v2/start-group-conversation",
        "POST",
        this->m_Cookie,
        CSRF_REQUIRED,
        Body
    ).JsonObj;

    return Responses::StartGroupConversationResponse(res);
}