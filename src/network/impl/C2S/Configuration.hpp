//
// Created by TaxMachine on 2024-04-22.
//

#ifndef JAVALESSMC_CONFIGURATION_HPP
#define JAVALESSMC_CONFIGURATION_HPP

#include "../../Packet.hpp"
#include "../../../utils/Exceptions.hpp"

enum ChatMode {
    ENABLE,
    COMMANDS_ONLY,
    HIDDEN
};

enum MainHand {
    LEFT,
    RIGHT
};

#define CAPE_ENABLED 0x01
#define JACKET_ENABLED 0x02
#define LEFT_SLEEVE_ENABLED 0x04
#define RIGHT_SLEEVE_ENABLED 0x08
#define LEFT_PANTS_LEG_ENABLED 0x10
#define RIGHT_PANTS_LEG_ENABLED 0x20
#define HAT_ENABLED 0x40

struct DisplayedSkinPart {
    bool cape;
    bool jacket;
    bool left_sleeve;
    bool right_sleeve;
    bool left_pants_leg;
    bool right_pants_leg;
    bool hat;
};

enum ResourcePackResultID {
    SUCCESSFULLY_DOWNLOADED,
    DECLINED,
    FAILED_TO_DOWNLOAD,
    ACCEPTED,
    DOWNLOADED,
    INVALID_URL,
    FAILED_TO_RELOAD,
    DISCARDED
};

/**
 * @brief Converts the displayed skin parts to a bitmask
 * @param skin_part The skin part
 * @return The bitmask
 */
static uint8_t GetSkinPart(DisplayedSkinPart skin_part) {
    uint8_t displayed_skin_part = 0;
    if (skin_part.cape) {
        displayed_skin_part |= CAPE_ENABLED;
    }
    if (skin_part.jacket) {
        displayed_skin_part |= JACKET_ENABLED;
    }
    if (skin_part.left_sleeve) {
        displayed_skin_part |= LEFT_SLEEVE_ENABLED;
    }
    if (skin_part.right_sleeve) {
        displayed_skin_part |= RIGHT_SLEEVE_ENABLED;
    }
    if (skin_part.left_pants_leg) {
        displayed_skin_part |= LEFT_PANTS_LEG_ENABLED;
    }
    if (skin_part.right_pants_leg) {
        displayed_skin_part |= RIGHT_PANTS_LEG_ENABLED;
    }
    if (skin_part.hat) {
        displayed_skin_part |= HAT_ENABLED;
    }
    return displayed_skin_part;
}

char* ClientInformation(const char* locale, int8_t view_distance, ChatMode chat_mode, bool chat_colors, DisplayedSkinPart displayed_skin_part, MainHand main_hand, bool enable_text_filtering, bool allow_server_listings) {
    MinecraftPacket packet{};
    packet.write_varint(0x00);
    packet.write_string(locale);
    packet.write_byte(view_distance);
    packet.write_varint((int)chat_mode);
    packet.write_bool(chat_colors);
    packet.write_ubyte(GetSkinPart(displayed_skin_part));
    packet.write_varint((int)main_hand);
    packet.write_bool(enable_text_filtering);
    packet.write_bool(allow_server_listings);
    return packet.getBuffer();
}

char* PluginMessage(const char* channel, const char* data) {
    MinecraftPacket packet{};
    packet.write_varint(0x01);
    packet.write_identifier(channel);
    packet.write_buffer(data, sizeof(data));
    return packet.getBuffer();
}

char* AcknowledgeFinishConfiguration() {
    MinecraftPacket packet{};
    packet.write_varint(0x02);
    return packet.getBuffer();
}

char* ServerboundKeepAlive(long keep_alive_id) {
    MinecraftPacket packet{};
    packet.write_varint(0x03);
    packet.write_long(keep_alive_id);
    return packet.getBuffer();
}

char* PongConfiguration(int id) {
    MinecraftPacket packet{};
    packet.write_varint(0x04);
    packet.write_varint(id);
    return packet.getBuffer();
}

char* ResourcePackResponse(uuids::uuid UUID, ResourcePackResultID result) {
    MinecraftPacket packet{};
    packet.write_varint(0x05);
    packet.write_UUID(UUID);
    packet.write_varint((int)result);
    return packet.getBuffer();
}

#endif //JAVALESSMC_CONFIGURATION_HPP
