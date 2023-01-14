#include "../include/ropp.h"
#include "../include/helper.h"
#include "../include/request.hpp"
#include "../include/responses.h"
#include <iostream>

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
        true,
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
        false
    ).JsonObj;

    return Responses::ChatSettings(res);
}

Responses::GetMessagesResponse RoPP::Chat::GetMessages(int PageSize, long ExclusiveStartMessageID)
{
    json res = Helper::MakeAuthedRobloxRequest
    (
        "https://chat.roblox.com/v2/get-messages?conversationId=" + std::to_string(this->ConversationID) + "&pageSize=" + std::to_string(PageSize) + (ExclusiveStartMessageID != 0 ? "&exclusiveStartMessageId=" + std::to_string(ExclusiveStartMessageID) : ""),
        "GET",
        this->Cookie,
        true
    ).JsonObj;

    return Responses::GetMessagesResponse(res);
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
        true
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
        false
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
        true
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
        true
    ).JsonObj;

    std::vector<Responses::ChatConversationWithMessages> Conversations;
    for (auto& i : res)
    {
        Conversations.emplace_back(i);
    }

    return Conversations;
}