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

void my_sort(multiset<pair<int, int>, My_less>::iterator s,
    multiset<pair<int, int>, My_less>::iterator e,
    multiset<pair<int, int>, My_less> & d
) {
    for (; s != e; s++) {
        d.insert(*s);
    }
}


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
    mp = tmp_sm;
    cin >> n;
    while (n--) {
        my_type tmp;
        cin >> tmp.first >> tmp.second;
        tmp_sm = tmp;
        ms.insert(mp); //新手成为会员
        multiset<pair<int, int>, My_less>::iterator p;
        pair<int, int> p3;
        multiset<pair<int, int>, My_less> ms_tmp;
        my_sort(ms.begin(), ms.end(), ms_tmp);
        p = ms_tmp.begin();

        p3 = *p;
        cout << tmp.first << " "<<p3.first<<endl;
        mp = tmp;
    }

    
    
    return 0;
}
