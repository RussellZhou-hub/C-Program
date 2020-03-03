// Test1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <filesystem>
#include<iomanip>
#include<map>
#include<cstdlib>
#include<set>


using namespace std;


class My_less {
public:
    typedef pair<int,int> my_type;
    static my_type sm;
    bool operator()( my_type& t1,  my_type& t2) const {
        if (abs(t1.second-sm.second) < abs(t2.second-sm.second)) return true;
        else if (abs(t1.second- sm.second) == abs(t2.second-sm.second)) {
            if (t1.second<sm.second && t2.second>sm.second) return true;
        }
        return false;
    }
};
My_less::my_type sm;



int main()
{
    int n;
    map<int, int>  m;
    pair<int, int> mp;
    m[1] = 1000000000;
    sm.first = 1;
    sm.second = 1000000000;
    multiset<pair<int, int>, My_less> ms;
    ms.insert(sm);
    cin >> n;
    while (n--) {
        cin >> mp.first >> mp.second;
        sm = mp;
        cout << ms.first << " " << ms.second << endl;
        ms.insert(mp);
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
