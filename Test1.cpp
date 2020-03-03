#include <iostream>
#include <filesystem>
#include<iomanip>
#include<map>
#include<cstdlib>
#include<set>


using namespace std;

typedef pair<int, int> my_type;     //id号，能力值

class My_less {                     //容器比较器
public:
    static my_type sm;             //新手的id，能力值
    bool operator()(const my_type& t1, const my_type& t2) const {
        if (abs(t1.second-sm.second) < abs(t2.second-sm.second)) return true;
        else if (abs(t1.second- sm.second) == abs(t2.second-sm.second)) {
            if (t1.second<sm.second && t2.second>sm.second) return true;
        }                         //最接近新手的排前面
        return false;
    }
};
my_type My_less::sm;



int main()
{
    int n;
    map<int, int>  m;
    pair<int, int> mp;
    m[1] = 1000000000;
    My_less ml;
    my_type& tmp_sm=ml.sm;
    tmp_sm.first = 1;
    tmp_sm.second = 1000000000;
    multiset<pair<int, int>, My_less> ms;
    ms.insert(tmp_sm);
    cin >> n;
    while (n--) {
        cin >> mp.first >> mp.second;
        tmp_sm = mp;
        multiset<pair<int, int>, My_less>::iterator p;
        pair<int, int> p2;
        p = ms.begin();
        p2 = *p;
        cout << mp.first << " "<<p2.first<<endl;
        ms.insert(mp);                    //新手成为会员
    }
    
    return 0;
}
