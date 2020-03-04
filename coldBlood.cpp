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

/*
intPair myOut[1002];
intPair myIn[1002];


void writeIn() {
    int a, b;
    cout << "1000\n";
    for (auto i = 0; i < 1000; i++) {
        cin >> a >> b;
        cout << myIn[i].first << " " << myIn[i].second << "\n";
        if ( a!= myOut[i].first) {
            cout << "\n\nline:" << i + 1 << "newb id wrong";
            if (b != myOut[i].second) {
                cout << "      line:" << i + 1 << "veteran id wrong" << "\n\n";
            }
        }
    }
}

void check( ) {
    int a, b;
    for (auto i = 0; i < 1000; i++) {
        cin >> a >> b;
        cout << myOut[i].first << " " << myOut[i].second << "\n";
        if (a != myOut[i].first) {
            cout << "\nline:" << i + 1 << "newb id wrong";
            if (b != myOut[i].second) {
                cout << "      line:" << i + 1 << "veteran id wrong" << "\n";
            }
        }
    }
}

*/

int main()
{
    /*
    ifstream in("In.txt");
    cin.rdbuf(in.rdbuf());
    ofstream out("myIn.txt");
    cout.rdbuf(out.rdbuf());
    */
    
            //测试
    int n;
    //int nOut;
    multiset<intPair,My_less<intPair>>  m;       //按能力值排
    
    intPair tmp;
    tmp.first = 1;
    tmp.second = 1000000000;
    m.insert(tmp);
    //cin >> n;


    //nOut = 0;
    scanf("%d", &n);
    while (n--) {
        multiset<intPair, My_less_2<intPair>>  m_2;          //按id排序
        //cin >> tmp.first >> tmp.second;
        scanf("%d%d", &tmp.first, &tmp.second);

        //myIn[nOut].first = tmp.first;
        //myIn[nOut].second = tmp.second;

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
        //myOut[nOut].first = intPair_tmp.first;
       //myOut[nOut].second = rival.first;
        //nOut++;

        
    }

    /*

    ifstream in2("out.txt");
    cin.rdbuf(in2.rdbuf());
    writeIn();

    ifstream in3("out.txt");
    cin.rdbuf(in3.rdbuf());
    ofstream out2("myOut.txt");
    cout.rdbuf(out2.rdbuf());
    check();
    
    */
    
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
