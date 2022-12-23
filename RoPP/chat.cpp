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
        Body
    ).JsonObj;

    return Responses::ConversationAddResponse().Parse(res);
}

Responses::ChatSettings RoPP::Chat::GetChatSettings()
{
    json res = Helper::MakeAuthedRobloxRequest
    (
        "https://chat.roblox.com/v2/chat-settings",
        "GET",
        this->Cookie
    ).JsonObj;

    return Responses::ChatSettings().Parse(res);
}

Responses::GetMessagesResponse RoPP::Chat::GetMessages(int PageSize, long ExclusiveStartMessageID)
{
    json res = Helper::MakeAuthedRobloxRequest
    (
        "https://chat.roblox.com/v2/get-messages?conversationId=" + std::to_string(this->ConversationID) + "&pageSize=" + std::to_string(PageSize) + (ExclusiveStartMessageID != 0 ? "&exclusiveStartMessageId=" + std::to_string(ExclusiveStartMessageID) : ""),
        "GET",
        this->Cookie
    ).JsonObj;

    return Responses::GetMessagesResponse().Parse(res);
}