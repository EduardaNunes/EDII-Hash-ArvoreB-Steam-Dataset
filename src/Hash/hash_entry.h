#ifndef HASH_ENTRY_H
#define HASH_ENTRY_H

#include "player.h"

enum EntryState
{
    EMPTY,
    OCCUPIED,
    DELETED
};

struct HashEntry
{
    Player player;
    EntryState state;

    HashEntry() : player(), state(EMPTY) {}
};

#endif
