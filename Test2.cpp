// Test1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<iomanip>
#include<map>
#include<cstdlib>
#include<set>


using namespace std;

typedef pair<int, int> mt;

template<class T>
class My_less {
public:
    bool operator()(const T & x,const T & y)const {
        if (x.second < y.second) return true;
        else return false;
     }
};




int main()
{
    int n;
    set<mt,My_less<mt>>  m;
    mt tmp;
    tmp.first = 1;
    tmp.second = 1000000000;
    m.insert(tmp);
    scanf("%d", &n);
    while (n--) {
        //cin >> tmp.first >> tmp.second;
        scanf("%d%d", &tmp.first, &tmp.second);
        m.insert(tmp);
        set<mt, My_less<int>>::iterator t;
        set<mt, My_less<int>>::iterator right;
        set<mt, My_less<int>>::iterator left;
        mt mt_tmp;
        t = m.find(tmp);
        if (t == m.begin()) {
            right = ++t;
            mt_tmp = *right;
            //cout << tmp.first << " " << mt_tmp.first << endl;
            printf("%d %d\n", tmp.first, mt_tmp.first);
        }
        else if (t == --m.end()) {
            left = --t;
            mt_tmp = *left;
            //cout << tmp.first << " " << mt_tmp.first << endl;
            printf("%d %d\n",tmp.first, mt_tmp.first);
        }
        else {
            right = ++t;
            --t;
            left = --t;
            ++t;
            mt a,b;
            mt_tmp = *t;
            b = *right;
            a = *left;
            if (b.second - mt_tmp.second < mt_tmp.second - a.second) {
                //cout << tmp.first << " " << b.first << endl;
                printf("%d %d\n", tmp.first, b.first);

            }
            else { //cout << tmp.first << " " << a.first << endl;
                printf("%d %d\n", tmp.first, a.first);
            }

        }
    }

    
    
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
