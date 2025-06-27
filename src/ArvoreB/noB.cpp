#include "noB.h"

NoB::NoB(int m, bool isLeaf) {
    this->m = m;
    this->isLeaf = isLeaf;
    filledKeys = 0;
    keys.resize(m - 1);
    children.resize(m);
}
