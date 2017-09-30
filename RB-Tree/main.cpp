#include "RBTree.h"
#include <iostream>
#include <vector>

using namespace std;


int main(int argc, char *argv[])
{
    RBTree t;
    vector<int> vec = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

    for(auto x : vec) {
        t.insert(x);
    }
    t.travelLevelOrder();
    cout << endl;

    //t.deleteItem(9);
    //t.travelLevelOrder();
    //cout << endl;

    for(int x = 0; x < 10; x++) {
        t.deleteItem(x);
        t.travelLevelOrder();
        cout << endl;
    }


    return 0;
}

