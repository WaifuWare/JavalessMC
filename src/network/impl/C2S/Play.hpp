//
// Created by taxis on 2024-04-23.
//

#ifndef JAVALESSMC_PLAY_HPP
#define JAVALESSMC_PLAY_HPP

#include "../../Packet.hpp"
#include "../../../utils/uuid.h"
#include "../../../utils/Exceptions.hpp"

namespace Packet {

    char* ConfirmTeleport(int32_t teleport_id) {
        MinecraftPacket packet{};
        packet.write_varint(0x00);
        packet.write_varint(teleport_id);
        return packet.getBuffer();
    }

    char* QueryBlockEntityTag(int32_t transaction_id, Position location) {
        MinecraftPacket packet{};
        packet.write_varint(0x01);
        packet.write_varint(transaction_id);
        packet.write_position(location);
        return packet.getBuffer();
    }

    char* ChangeDifficulty(Difficulty new_difficulty) {
        MinecraftPacket packet{};
        packet.write_varint(0x02);
        packet.write_byte((int8_t)new_difficulty);
        return packet.getBuffer();
    }

    char* AcknowledgeMessage(int32_t message_count) {
        MinecraftPacket packet{};
        packet.write_varint(0x03);
        packet.write_varint(message_count);
        return packet.getBuffer();
    }

    char* ChatCommand(const char* command, int64_t timestamp, int64_t salt, int32_t array_length, char** arguments, int32_t message_count, int8_t acknowledged) {
        MinecraftPacket packet{};
        packet.write_varint(0x04);
        packet.write_string(command);
        packet.write_long(timestamp);
        packet.write_long(salt);
        packet.write_varint(array_length);
        packet.write_array(arguments);
        packet.write_varint(message_count);
        packet.write_byte(acknowledged);
        return packet.getBuffer();
    }

}

#endif //JAVALESSMC_PLAY_HPP
