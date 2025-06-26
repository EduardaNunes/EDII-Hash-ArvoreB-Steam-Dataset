#include <vector>

using namespace std;

class NoB {
    private:
        int m;
        vector<int> keys;
        vector <NoB*> children;
        int filledKeys;
        bool isLeaf;
    
    public:
        NoB(int m, int keys[], NoB* children[]);
};