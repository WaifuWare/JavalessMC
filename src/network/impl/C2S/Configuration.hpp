//
// Created by TaxMachine on 2024-04-22.
//

#ifndef JAVALESSMC_CONFIGURATION_HPP
#define JAVALESSMC_CONFIGURATION_HPP

#include "../../Packet.hpp"
#include "../../../utils/Exceptions.hpp"

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

char* ServerBoundKeepAlive(long keep_alive_id) {
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
