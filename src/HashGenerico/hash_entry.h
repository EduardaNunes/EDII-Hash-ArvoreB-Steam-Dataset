#ifndef HASH_ENTRY_H
#define HASH_ENTRY_H

// Enum para definir o estado de uma entrada na tabela hash
enum class EntryState
{
    VAZIO,
    OCUPADO,
    REMOVIDO
};

// Estrutura para representar uma entrada na tabela hash
template <typename T>
struct HashEntry
{
    T data;
    EntryState state = EntryState::VAZIO;

    HashEntry() = default;
};

#endif