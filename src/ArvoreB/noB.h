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
};