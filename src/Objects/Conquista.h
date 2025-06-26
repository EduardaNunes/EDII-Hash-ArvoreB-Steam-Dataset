#include "Jogo.h"
#include <string>
using namespace std;

class Conquista{
    private:
        int id;
        Jogo jogo;
        string titulo;
        string descricao;

    public:
        Conquista(int id, Jogo jogo, string titulo, string descricao);

        int getId();
        Jogo getJogo();
        string getTitulo();
        string getDescricao();
};