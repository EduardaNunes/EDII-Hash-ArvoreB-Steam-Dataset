#include <vector>
#include <string>

using namespace std;

class LeitorDePlanilha {
    public:
        vector<vector<string>> lerCSV(const string& caminhoArquivo);
        int contarJogadoresCSV(const string &caminho);
};