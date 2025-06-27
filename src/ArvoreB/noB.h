#include <vector>

using namespace std;

class NoB {
    private:
        vector<int> chaves;
        vector <NoB*> filhos;
        int chavesPreenchidas;
        bool eFolha;
    
    public:
        NoB(int ordemArvore, bool eFolha);

        vector<int> getChaves();
        vector<NoB*> getFilhos();
        int getChavesPreenchidas();
        bool getEFolha();

        void addChave(int novaChave);
        void addFilho(NoB* novoFilho);
        void setChavesPreechidas(int novaChavesPreenchidas);
        void setEFolha(bool novoEFolha);
};