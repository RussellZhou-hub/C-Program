// Test1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<iomanip>
#include<map>
#include<cstdlib>
#include<set>
#include <iostream>
#include <fstream>


using namespace std;

typedef pair<int, int> intPair;

template<class T>
class My_less {
public:                     //能力值小的排前面
    bool operator()(const T & x,const T & y)const {
        if (x.second < y.second || x.second==y.second && x.first<y.first) return true;
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
    //int nOut;
    multiset<intPair,My_less<intPair>>  m;       //按能力值排
    
    intPair tmp;
    tmp.first = 1;
    tmp.second = 1000000000;
    m.insert(tmp);
    scanf("%d", &n);
    while (n--) {
        multiset<intPair, My_less_2<intPair>>  m_2;          //按id排序
        //cin >> tmp.first >> tmp.second;
        scanf("%d%d", &tmp.first, &tmp.second);
        m.insert(tmp);
        multiset<intPair, My_less<intPair>>::iterator t;
        multiset<intPair, My_less<intPair>>::iterator right;
        multiset<intPair, My_less<intPair>>::iterator left;
        intPair intPair_tmp,a,b;
        t = m.find(tmp);
        intPair_tmp = *t;
        if (t == m.begin()) {
            right = ++t;
            int intTMP = (*right).second - intPair_tmp.second;
            while (right != m.end() && ((*right).second - intPair_tmp.second) == intTMP) {         //只需向后搜索
                m_2.insert(*right++);
            }
        }
        else if (t == --m.end()) {                                      //只需向前搜索
            left =t;
            int intTMP = intPair_tmp.second- (*(--left)).second;
            do {
                m_2.insert(*left);
            } while (left != m.begin() && (intPair_tmp.second - (*(--left)).second) == intTMP);
        }
        else {                                                            //能力值在中间，两边都要搜索
            right = ++t;
            --t;
            left = --t;
            ++t;
            if ((*right).second - intPair_tmp.second < intPair_tmp.second - (*left).second) {         //向后
                int intTMP= (*right).second - intPair_tmp.second;
                while (right != m.end() && ((*right).second - intPair_tmp.second) == intTMP) {
                    m_2.insert(*right++);
                }
            }
            else if ((*right).second - intPair_tmp.second > intPair_tmp.second - (*left).second) {
                left = t;
                int intTMP = intPair_tmp.second - (*(--left)).second;
                do {                                                                   //向前
                    m_2.insert(*left);
                } while (left != m.begin() && (intPair_tmp.second - (*(--left)).second) == intTMP);
            }
            else if((*right).second - intPair_tmp.second == intPair_tmp.second - (*left).second) {
                int intTMP = (*right).second - intPair_tmp.second;
                do {
                    m_2.insert(*left);
                } while (left != m.begin() && (intPair_tmp.second - (*(--left)).second) == intTMP);
                while (right != m.end() && ((*right).second - intPair_tmp.second) == intTMP) {
                    m_2.insert(*(right++));
                }
            }

        }
        intPair rival;
        rival = *m_2.begin();
        printf("%d %d\n", intPair_tmp.first, rival.first);
    }

    return 0;
}

