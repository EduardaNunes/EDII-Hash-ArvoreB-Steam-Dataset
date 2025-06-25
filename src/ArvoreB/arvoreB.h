#include "NoB.h"

using namespace std;

class ArvoreB{
    private:
        int m;
        NoB* root;

    public:
        void insert();
        void search();
        void remove();

        void getOrder();
        void getRoot();
};