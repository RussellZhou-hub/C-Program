// Test1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<iomanip>
#include<map>
#include<cstdlib>
#include<set>


using namespace std;

typedef pair<int, int> intPair;

template<class T>
class My_less {
public:                     //能力值小的排前面
    bool operator()(const T & x,const T & y)const {
        if (x.second < y.second) return true;
        else return false;
     }
};

template<class T>
class My_less_2 {                                               //id小的排前面
public:
    bool operator()(const T& x, const T& y)const {
        if (x.first < y.first) return true;
        else return false;
    }
};




int main()
{
    int n;
    set<intPair,My_less<intPair>>  m;       //按能力值排
    
    intPair tmp;
    tmp.first = 1;
    tmp.second = 1000000000;
    m.insert(tmp);
    scanf("%d", &n);
    while (n--) {
        set<intPair, My_less_2<intPair>>  m_2;          //按id排序
        //cin >> tmp.first >> tmp.second;
        scanf("%d%d", &tmp.first, &tmp.second);
        m.insert(tmp);
        set<intPair, My_less<intPair>>::iterator t;
        set<intPair, My_less<intPair>>::iterator right;
        set<intPair, My_less<intPair>>::iterator left;
        intPair mt_tmp,a,b;
        t = m.find(tmp);
        if (t == m.begin()) {
            right = ++t;
            --t;
            mt_tmp = *t;
            //b = *right;
            //a = *left;
            int intTMP = (*right).second - mt_tmp.second;
            while (right != m.end() && ((*right).second - mt_tmp.second) == intTMP) {
                m_2.insert(*right++);
            }
        }
        else if (t == --m.end()) {
            left =t;
            mt_tmp = *t;
            //a = *left;
            int intTMP = mt_tmp.second- (*(--left)).second;
            do {
                m_2.insert(*left);
            } while (left != m.begin() && (mt_tmp.second - (*(--left)).second) == intTMP);
        }
        else {
            right = ++t;
            --t;
            left = --t;
            ++t;
            mt_tmp = *t;
            //b = *right;
            //a = *left;
            if ((*right).second - mt_tmp.second < mt_tmp.second - (*left).second) {
                int intTMP= (*right).second - mt_tmp.second;
                while (right != m.end() && ((*right).second - mt_tmp.second) == intTMP) {
                    m_2.insert(*right++);
                }
            }
            else if ((*right).second - mt_tmp.second > mt_tmp.second - (*left).second) {
                left = t;
                mt_tmp = *t;
                //a = *left;
                int intTMP = mt_tmp.second - (*(--left)).second;
                do {
                    m_2.insert(*left);
                } while (left != m.begin() && (mt_tmp.second - (*(--left)).second) == intTMP);
            }
            else if((*right).second - mt_tmp.second == mt_tmp.second - (*left).second) {
                mt_tmp = *t;
                //a = *left;
                int intTMP = (*right).second - mt_tmp.second;
                do {
                    m_2.insert(*left);
                } while (left != m.begin() && (mt_tmp.second - (*(--left)).second) == intTMP);
                while (right != m.end() && ((*right).second - mt_tmp.second) == intTMP) {
                    m_2.insert(*(right++));
                }
            }

        }
        intPair rival;
        rival = *m_2.begin();
        printf("%d %d\n", mt_tmp.first, rival.first);
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
