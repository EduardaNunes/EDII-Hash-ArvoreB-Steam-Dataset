#include <string>
using namespace std;

class Conquista{
    private:
        int id;
        int idJogo;
        string titulo;
        string descricao;

    public:
        Conquista(int id, int idJogo, string titulo, string descricao);

        int getId();
        int getIdJogo();
        string getTitulo();
        string getDescricao();
};