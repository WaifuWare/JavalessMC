//
// Created by taxis on 2024-04-23.
//

#ifndef JAVALESSMC_STRUCTS_HPP
#define JAVALESSMC_STRUCTS_HPP

#define SEGMENT_BITS 0x7F
#define SEGMENT_CONTINUATION_BIT 0x80

#define CAPE_ENABLED 0x01
#define JACKET_ENABLED 0x02
#define LEFT_SLEEVE_ENABLED 0x04
#define RIGHT_SLEEVE_ENABLED 0x08
#define LEFT_PANTS_LEG_ENABLED 0x10
#define RIGHT_PANTS_LEG_ENABLED 0x20
#define HAT_ENABLED 0x40

enum HandshakeNextState {
    Status = 1,
    Login
};

enum ChatMode {
    ENABLE,
    COMMANDS_ONLY,
    HIDDEN
};

enum MainHand {
    LEFT,
    RIGHT
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

struct DisplayedSkinPart {
    bool cape;
    bool jacket;
    bool left_sleeve;
    bool right_sleeve;
    bool left_pants_leg;
    bool right_pants_leg;
    bool hat;
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

#endif //JAVALESSMC_STRUCTS_HPP
