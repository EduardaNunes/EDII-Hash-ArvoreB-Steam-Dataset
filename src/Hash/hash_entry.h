#ifndef HASH_ENTRY_H
#define HASH_ENTRY_H

#include "player.h"

enum class EntryState
{
    EMPTY,
    OCCUPIED,
    DELETED
};

struct HashEntry
{
    Player player;
    EntryState state = EntryState::EMPTY;

    HashEntry() = default;
};

#endif
