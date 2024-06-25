#pragma once

#include <iostream>
#include <string>

#include <cassert>
#define assertm(exp, msg) assert(((void)msg, exp))

// it is fair to assume any given item, 
// entity or otherwise anything that get to use NBT tags will ever only have 16 "root" objects in it at worse.
// each of those objects can, in theory, hold an infinite amount of tags in them. For all intents and purporses,
// we'll also assume an NBT tag will never contain more than a total amount of 2048 unique entries
#define MAX_ROOT_TAG 16

enum TAGTYPE {
    TAG_End = 0,
    TAG_Byte = 1,
    TAG_Short = 2,
    TAG_Int = 3,
    TAG_Long = 4,
    TAG_Float = 5,
    TAG_Double = 6,
    TAG_Byte_Array = 7,
    TAG_String = 8,
    TAG_List = 9,
    TAG_Compound = 10,
    TAG_Int_Array = 11,
    TAG_Long_Array = 12
};

struct NBTEntry {
    TAGTYPE type;
    std::string value;  // <-- will be converted properly dont worry
};

struct NBTTag {
    NBTEntry entries[MAX_ROOT_TAG];
};

NBTEntry *getEntryByName(std::string, NBTTag* tag) {
    return nullptr;
}

// todo : write a byte[] to nbt parser
void generateNBTData(NBTTag* tag, unsigned char rawdata[]) {

}

bool getBoolean(std::string name, NBTTag* tag) {

    NBTEntry *entry = getEntryByName(name, tag);

    if(entry == nullptr)
        return 0;

    assertm(entry->type == 1, "Specified NBT entry does not correspond to TAG_Byte");

    return 0;
}