#ifndef HASH_ENTRY_H
#define HASH_ENTRY_H

enum class EntryState {
    VAZIO,
    OCUPADO,
    REMOVIDO
};

template<typename T>
struct HashEntry {
    T data;
    EntryState state = EntryState::VAZIO;

    HashEntry() = default;
};

#endif