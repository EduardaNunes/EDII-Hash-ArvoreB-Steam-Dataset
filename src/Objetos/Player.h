#include <string>
#include <vector>
#include "Jogo.h"
#include "Conquista.h"

using namespace std;

class Player{
    private:
        int id;
        string pais;
        string dataDeCriacao;
        vector<Jogos> jogos;
        vector<Conquistas> conquistas;

    public:
        Player(int id, string pais, string dataDeCriacao);

        int getId();
        string getPais();
        string getDataDeCriacao();
        vector<Jogos> getJogos();
        vector<Conquista> getConquistas();

        void addConquista(Conquista novaConquista);
        void addJogo(Jogo novoJogo);
};