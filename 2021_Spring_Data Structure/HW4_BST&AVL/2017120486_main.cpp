/**
  * Assignment 4 for COSE213 Data Structures
  *
  * Won-Ki Jeong (wkjeong@korea.ac.kr)
  *
  * 2021. 6. 1
  *
  */

#include "LinkedBinaryTree.h"
#include "SearchTree.h"
#include "AVLTree.h"

#include <cstdlib>
#include <ctime>
#include <time.h>
#include <algorithm>    // std:shuffle
#include <vector>   // std::vector


using namespace std;

int main() {
    typedef Entry<int, float> EntryType;

    LinkedBinaryTree<EntryType> t;

    std::cout << "Size : " << t.size() << std::endl;

    t.addRoot();

    std::cout << "Size : " << t.size() << std::endl;


    //
    //
    //
    SearchTree<EntryType> st;

    std::cout << "Size : " << st.size() << std::endl;
    st.insert(1, 2.5);
    st.insert(3, 4.5);
    st.insert(7, 5.5);
    st.insert(2, 1.5);
    st.insert(3, 8.5);
    std::cout << "Size : " << st.size() << std::endl;

    for (SearchTree<EntryType>::Iterator it = st.begin(); it != st.end(); ++it) {
        std::cout << (*it).key() << " , " << (*it).value() << std::endl;
    }

    st.erase(3);
    std::cout << "Size : " << st.size() << std::endl;
    for (SearchTree<EntryType>::Iterator it = st.begin(); it != st.end(); ++it) {
        std::cout << (*it).key() << " , " << (*it).value() << std::endl;
    }

    std::cout << "------------" << std::endl;



    //
    //
    //
    AVLTree<EntryType> avl;

    // random test
    int nElem = 100; // change size 100, 1000, 10000, 100000, 1000000

    int *key = new int[nElem * 3];
    float *val = new float[nElem * 3];

    std::srand(std::time(0)); // use current time as seed for random generator



    // initialize
    for (int i = 0; i < nElem * 3; i++) {
        key[i] = std::rand();
        val[i] = (float) std::rand() / RAND_MAX * 20000;
    }


    //
    // AVL tree Insert test
    //
    clock_t tm;
    tm = clock();
    for (int i = 0; i < nElem; i++) {
        avl.insert(key[i], val[i]);
    }
    tm = clock() - tm;
    printf("AVL Insert Only: It took me %f seconds.\n", ((float) tm) / (float) CLOCKS_PER_SEC);


    //
    // AVL tree Find test
    //
    tm = clock();
    for (int i = nElem; i < nElem * 2; i++) {
        avl.find(key[i]);
    }
    tm = clock() - tm;
    printf("AVL Find Only: it took me %f seconds.\n", ((float) tm) / (float) CLOCKS_PER_SEC);

    //
    // AVL tree Erase and Find in random order test
    //

    vector<int> foo(nElem, 0);
    for (int i = 0; i < 0.8 * nElem; i++) {       // 0.2, 0.4, 0.5, 0.6, 0.8
        foo[i] = 1;
    }
    random_shuffle(foo.begin(), foo.end());

//    int count = 0;
//    for(int i = 0; i < nElem; i++){
//        if(foo[i] == 1) count++;
//    }
//    printf("%d\n", count);

    tm = clock();
    for (int i = nElem * 2, m = 0; i < nElem * 3 && m < nElem; i++, m++) {
        if (foo[m]) { // foo[m] == 1 -> implement erase function
            avl.erase(key[i]);
        } else {
            avl.find(key[i]);
        }
    }
    tm = clock() - tm;
    printf("AVL Random erase and find: It took me %f seconds.\n", ((float) tm) / (float) CLOCKS_PER_SEC);



    //
    //
    //
    SearchTree<EntryType> st1;

    std::srand(std::time(0)); // use current time as seed for random generator

    //
    // search tree Insert test
    //
    tm = clock();
    for (int i = 0; i < nElem; i++) {
        st1.insert(key[i], val[i]);
    }
    tm = clock() - tm;
    printf("ST Insert Only: It took me %f seconds.\n", ((float) tm) / (float) CLOCKS_PER_SEC);


    //
    // search tree Find test
    //
    tm = clock();
    for (int i = nElem; i < nElem * 2; i++) {
        st1.find(key[i]);
    }
    tm = clock() - tm;
    printf("ST Find Only: it took me %f seconds.\n", ((float) tm) / (float) CLOCKS_PER_SEC);

    //
    // search tree Erase and Find in random order test
    //

    tm = clock();
    for (int i = nElem * 2, m = 0; i < nElem * 3 && m < nElem; i++, m++) {
        if (foo[m]) { // foo[m] == 1 -> implement erase function
            st1.erase(key[i]);
        } else {
            st1.find(key[i]);
        }
    }
    tm = clock() - tm;
    printf("ST Random erase and find: It took me %f seconds.\n", ((float) tm) / (float) CLOCKS_PER_SEC);

    return 0;
}
