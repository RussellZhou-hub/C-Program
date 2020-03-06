// test1.cpp : This file contains the 'main' function. Program execution begins and ends there.



#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <cstdlib>
#include <cstddef>
#include <cstring>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <algorithm>
#include<set>


using namespace std;

int M, N, K, T;



int minute;

string timeToString(int min) {           //表示时间
	int hour = min / 60;
	min = min % 60;
	char s[7];
	sprintf(s, "%3d:%2d", hour, min);
	for (int i = 0; i < 6; i++) {
		if (s[i] == ' ') s[i] = '0';
	}
	s[6] = '\0';
	string ss(s);
	return ss;
}

class HeadQuarter {
public:
	static int redElement, blueElement;                 //司令部生命元
	int color;                                     //0红1蓝
	int iniElement[5] = {0,0,0,0,0};
	int iniForce[5]= { 0,0,0,0,0 };
	string indexToName[5] = { "dragon","ninja","iceman","lion","wolf" };
	HeadQuarter(int col) {
		color = col;
	}
	int generate() {                 //返回-1表示停止制造
		if (color == 0) {
			int order[5] = { 2,3,4,1,0 };          //红方司令部按照iceman、lion、wolf、ninja、dragon 的顺序制造武士。
			for (auto i = 0; i < 5; i++) {
				if (redElement - iniElement[order[i]] >= 0) {
					redElement -= iniElement[order[i]];
					return order[i];
				}
			}
		}
		else {
			int order[5] = { 3,0,1,2,4 };     //蓝方司令部按照lion、dragon、ninja、iceman、wolf 的顺序制造武士。
			for (auto i = 0; i < 5; i++) {
				if (blueElement - iniElement[order[i]] >= 0) {
					blueElement -= iniElement[order[i]];
					return order[i];
				}
			}
		}
		return -1;
	}
};
int HeadQuarter::redElement = 0;
int HeadQuarter::blueElement = 0;    

class Weapon {                            //武器类
public:
	int size,id,attack_effect;       //num该种武器数量
	class Info {                      //武器信息类
	public:
		int available;
		bool used;
		Info() {
			available = 0;
			used = false;
		}
		Info(int a,bool u) {
			available = a;
			used = u;
		}
		bool operator<(Info& info) {
			if (this->used == true && info.used == false) return true;        //用过的排使用顺序前面
			return false;
		}
	};
	
	multiset<Info> msetInfo;     //每个该种剩余使用次数，最多10个武器,用过的排在前面
	string idToName[3] = { "sword","bomb","arrow" };
	Weapon() {
		size = 0;        
		attack_effect = 0;
		id = 0;
	}
	void setId(int id_tmp) {
		if (id_tmp == 0) {
			attack_effect = 2;          //   该类武器最终攻击力==战士攻击力*attck_effect /10
		}
		if (id_tmp == 1) {
			attack_effect = 4;
		}
		if (id_tmp == 2) {
			attack_effect = 3;
		}
	}
	void gain() {
		if (id == 0) {
			
			size++;
		}
		else if(id == 1) {

		}
		else if (id == 2) {

		}
	}
};


class Soldier {                                //战士
public:
	static int redNumSoldier;
	static int blueNumSoldier;
	int element,force,id,city,color,index;     //0代表红1代表蓝
	
	Weapon weapon[3];       //拥有武器情况
	Soldier() = default;
	Soldier(int ele,int f,int color_tmp){
		for (auto i = 0; i < 3; i++) weapon[i].setId(i);         //初始化武器id和攻击力
		color = color_tmp;
		if (color == 0) {
			redNumSoldier++;
			id = redNumSoldier;
			city = 0;
		}
		else {
			blueNumSoldier++;
			id = blueNumSoldier;
			city = N + 1;
		}
		element = ele;
		force = f;
	}
	virtual ~Soldier() {
		if (color == 0) redNumSoldier--;
		else blueNumSoldier--;
	}
	virtual void attack(Soldier* rival){}
	virtual void take(Soldier* rival) {}
	virtual void hurt(Soldier* rival) {}
	virtual void move(){}
	virtual int getLoyalty() { return 1; }
	virtual void setLoyalty(int x) { }
};
int Soldier::redNumSoldier = 0;
int Soldier::blueNumSoldier = 0;

class Dragon:public Soldier {             //龙战士
public:
	static int redNumDragon;
	static int blueNumDragon;
	Dragon() = default;
	Dragon(int ele,int forceTmp,int color_tmp) :Soldier(ele,forceTmp,color_tmp) {
		if (color == 0) {
			redNumDragon++;
		}
		else {
			blueNumDragon++;
		}
		index = 0;
		int weaponID = id % 3;   //编号为n的dragon降生时即获得编号为n%3 的武器
		weapon[weaponID].gain();
	}
	~Dragon() {
		if (color == 0) {
			redNumDragon--;
		}
		else {
			blueNumDragon--;
		}
	}
	void attack(Soldier* rival) {

	}
	void celebrate() {            //龙特有的

	}
};
int Dragon::redNumDragon = 0;
int Dragon::blueNumDragon = 0;

class Ninja :public Soldier {             //忍者战士
public:
	static int redNumNinja;
	static int blueNumNinja;
	Ninja() = default;
	Ninja(int ele, int forceTmp, int color_tmp) :Soldier(ele, forceTmp, color_tmp) {
		if (color == 0) {
			redNumNinja++;
		}
		else {
			blueNumNinja++;
		}
		index = 1;
	}
	~Ninja() {
		if (color == 0) {
			redNumNinja--;
		}
		else {
			blueNumNinja--;
		}
	}
	void attack(Soldier* rival) {

	}
};
int Ninja::redNumNinja = 0;
int Ninja::blueNumNinja = 0;

class Iceman :public Soldier {             //冰人战士
public:
	static int redNumIceman;
	static int blueNumIceman;
	Iceman() = default;
	Iceman(int ele, int forceTmp, int color_tmp) :Soldier(ele, forceTmp, color_tmp) {
		if (color == 0) {
			redNumIceman++;
		}
		else {
			blueNumIceman++;
		}
		index = 2;
	}
	~Iceman() {
		if (color == 0) {
			redNumIceman--;
		}
		else {
			blueNumIceman--;
		}
	}
	void attack(Soldier* rival) {

	}
};
int Iceman::redNumIceman = 0;
int Iceman::blueNumIceman = 0;

class Lion :public Soldier {             //狮战士
public:
	static int redNumLion;
	static int blueNumLion;
	int loyalty;                         //狮特有的
	Lion() = default;
	Lion(int ele, int forceTmp, int color_tmp,int lo) :Soldier(ele, forceTmp, color_tmp) {
		if (color == 0) {
			redNumLion++;
			loyalty = lo;
		}
		else {
			blueNumLion++;
		}
		index = 3;
	}
	~Lion() {
		if (color == 0) {
			redNumLion--;
		}
		else {
			blueNumLion--;
		}
	}
	int getLoyalty() {
		return loyalty;
	}
	void setLoyalty(int x) {
		loyalty = x;
	}
	void attack(Soldier* rival) {

	}
};
int Lion::redNumLion = 0;
int Lion::blueNumLion = 0;

class Wolf :public Soldier {             //狼战士
public:
	static int redNumWolf;
	static int blueNumWolf;
	Wolf() = default;
	Wolf(int ele, int forceTmp, int color_tmp) :Soldier(ele, forceTmp, color_tmp) {
		if (color == 0) {
			redNumWolf++;
		}
		else {
			blueNumWolf++;
		}
		index = 4;
	}
	~Wolf() {
		if (color == 0) {
			redNumWolf--;
		}
		else {
			blueNumWolf--;
		}
	}
	void attack(Soldier* rival) {

	}
};
int Wolf::redNumWolf = 0;
int Wolf::blueNumWolf = 0;

void init() {
	  Dragon::redNumDragon = 0;
	  Dragon::blueNumDragon = 0;
	  Ninja::redNumNinja = 0;
	  Ninja::blueNumNinja = 0;
	  Iceman::redNumIceman = 0;
	  Iceman::blueNumIceman = 0;
	  Lion::redNumLion = 0;
	  Lion::blueNumLion = 0;
	  Wolf::redNumWolf = 0;
	  Wolf::blueNumWolf = 0;
	  HeadQuarter::redElement = 0;
	  HeadQuarter::blueElement = 0;
	  Soldier::redNumSoldier = 0;
	  Soldier::blueNumSoldier = 0;
}

int main()
{
	int n;
	bool gameover;
	cin >> n;

	for (auto k = 1; k <= n; k++) {
		init();
		gameover = false;
		cout << "Case:" << k << endl;
		HeadQuarter redQuarter(0);
		HeadQuarter blueQuarter(1);
		vector<Soldier*> redSoldier;
		vector<Soldier*> blueSoldier;
		cin >> M >> N >> K >> T;
		redQuarter.redElement = M;                 //司令部初始生命元
		blueQuarter.blueElement = M;
		for (auto i = 0; i < 5; i++) {    //每种武士初始生命值
			int tmp;
			cin >> tmp;
			redQuarter.iniElement[i]=tmp;
			blueQuarter.iniElement[i] = tmp;
		}
		for (auto i = 0; i < 5; i++) {     //每种武士初始攻击力
			int tmp;
			cin >> tmp;
			redQuarter.iniForce[i] = tmp;
			blueQuarter.iniForce[i] = tmp;
		}
		for (minute = 0; minute <= T; minute++) {       //计时器
			if (minute % 60 == 0) {             //整点触发事件,降生
				int index;
				index=redQuarter.generate();
				if (index == 0) {
					redSoldier.push_back(new Dragon(redQuarter.iniElement[index], redQuarter.iniForce[index], 0));
				}
				else if (index == 1) {
					redSoldier.push_back(new Ninja(redQuarter.iniElement[index], redQuarter.iniForce[index], 0));
				}
				else if (index == 2) {
					redSoldier.push_back(new Iceman(redQuarter.iniElement[index], redQuarter.iniForce[index], 0));
				}
				else if (index == 3) {
					redSoldier.push_back(new Lion(redQuarter.iniElement[index], redQuarter.iniForce[index], 0,redQuarter.redElement) );
				}
				else if (index == 4) {
					redSoldier.push_back(new Wolf(redQuarter.iniElement[index], redQuarter.iniForce[index], 0));
				}
				if (index != -1) {
					cout << timeToString(minute) << " red " << redQuarter.indexToName[index] << " " << (*redSoldier.back()).id << " born\n";
					if (index == 3) {
						vector<Soldier*>::iterator S_it;
						S_it = redSoldier.end();
						S_it--;
						cout << "Its loyalty is " << (*S_it)->getLoyalty() << "\n";
					}
				}
				index = blueQuarter.generate();
				if (index == 0) {
					blueSoldier.push_back(new Dragon(blueQuarter.iniElement[index], blueQuarter.iniForce[index], 1));
				}
				else if (index == 1) {
					blueSoldier.push_back(new Ninja(blueQuarter.iniElement[index], blueQuarter.iniForce[index], 1));
				}
				else if (index == 2) {
					blueSoldier.push_back(new Iceman(blueQuarter.iniElement[index], blueQuarter.iniForce[index], 1));
				}
				else if (index == 3) {
					blueSoldier.push_back(new Lion(blueQuarter.iniElement[index], blueQuarter.iniForce[index], 1,blueQuarter.blueElement) );
				}
				else if (index == 4) {
					blueSoldier.push_back(new Wolf(blueQuarter.iniElement[index], blueQuarter.iniForce[index], 1));
				}
				if (index != -1) {
					cout << timeToString(minute) << " blue " << blueQuarter.indexToName[index] << " " << (*blueSoldier.back()).id << " born\n";
					if (index == 3) {
						vector<Soldier*>::iterator S_it;
						S_it = blueSoldier.end();
						S_it--;
						cout << "Its loyalty is " << (*S_it)->getLoyalty() << "\n";
					}
				}
			}
			if (minute % 60 == 5) {             //lion逃跑
				vector<Soldier*>::iterator S_it;
				S_it = redSoldier.begin();
				for (; S_it != redSoldier.end(); S_it++) {
					if ((*S_it)->index == 3 && (*S_it)->getLoyalty() <=0 && (*S_it)->city!=N+1 ) {                 //不在对方司令部，忠诚度<=0
						cout << timeToString(minute) << " red lion " << (*S_it)->id << " ran away\n";
						vector<Soldier*>::iterator tmp_it;
						tmp_it = S_it;
						(*tmp_it)->~Soldier();
						redSoldier.erase(tmp_it);
					}
				}
				S_it = blueSoldier.begin();
				for (; S_it != blueSoldier.end(); S_it++) {                          
					if ((*S_it)->index == 3 && (*S_it)->getLoyalty() <= 0 && (*S_it)->city != 0) {        //不在对方司令部，忠诚度<=0
						cout << timeToString(minute) << " blue lion " << (*S_it)->id << " ran away\n";
						vector<Soldier*>::iterator tmp_it;
						tmp_it = S_it;
						(*tmp_it)->~Soldier();
						blueSoldier.erase(tmp_it);
					}
				}
			}
			if (minute % 60 == 10) {             //前进
				vector<Soldier*>::iterator S_it;
				S_it = redSoldier.begin();
				for (; S_it != redSoldier.end(); S_it++) {
					if ((*S_it)->city != N + 1) {      //还没到对方司令部
						(*S_it)->city++;
						if ((*S_it)->city != N + 1) {
							if ((*S_it)->index == 2) (*S_it)->element = ((*S_it)->element * 9) / 10;      //生命值减少
							if ((*S_it)->index == 3) (*S_it)->setLoyalty((*S_it)->getLoyalty() - K);     //忠诚减少
							cout << timeToString(minute) << " " << "red " << redQuarter.indexToName[(*S_it)->index] << " " << (*S_it)->id << " marched to city " << (*S_it)->city << " with " << (*S_it)->element << " elements and force " << (*S_it)->force << "\n";
						}
						else if ((*S_it)->city == N + 1) {
							if ((*S_it)->index == 2) (*S_it)->element = ((*S_it)->element * 9) / 10;      //生命值减少
							if ((*S_it)->index == 3) (*S_it)->setLoyalty((*S_it)->getLoyalty() - K);     //忠诚减少
							cout << timeToString(minute) << " " << "red " << redQuarter.indexToName[(*S_it)->index] << " " << (*S_it)->id << " reached blue headquarter with " << (*S_it)->element << " elements and force " << (*S_it)->force << "\n";
							cout << timeToString(minute) << " blue headquarter was taken\n";
							gameover = true;
						}
					}
				}
				S_it = blueSoldier.begin();
				for (; S_it != blueSoldier.end(); S_it++) {
					if ((*S_it)->city != 0) {      //还没到对方司令部
						(*S_it)->city--;
						if ((*S_it)->city != 0) {
							if ((*S_it)->index == 2) (*S_it)->element = ((*S_it)->element * 9) / 10;      //生命值减少
							if ((*S_it)->index == 3) (*S_it)->setLoyalty((*S_it)->getLoyalty() - K);     //忠诚减少
							cout << timeToString(minute) << " " << "blue " << blueQuarter.indexToName[(*S_it)->index] << " " << (*S_it)->id << " marched to city " << (*S_it)->city << " with " << (*S_it)->element << " elements and force " << (*S_it)->force << "\n";
						}
						else if ((*S_it)->city == 0) {
							if ((*S_it)->index == 2) (*S_it)->element = ((*S_it)->element * 9) / 10;      //生命值减少
							if ((*S_it)->index == 3) (*S_it)->setLoyalty((*S_it)->getLoyalty() - K);     //忠诚减少
							cout << timeToString(minute) << " " << "blue " << blueQuarter.indexToName[(*S_it)->index] << " " << (*S_it)->id << " reached red headquarter with " << (*S_it)->element << " elements and force " << (*S_it)->force << "\n";
							cout << timeToString(minute) << " red headquarter was taken\n";
							gameover = true;
						}
					}
				}
			}
			if (minute % 60 == 35 && !gameover) {              //wolf抢夺武器

			}
			if (minute % 60 == 40 && !gameover ) {              //战斗

			}
			if (minute % 60 == 50 && !gameover) {              //司令部报告生命元
				cout << timeToString(minute) << " " << redQuarter.redElement << " " << "elements in red headquarter\n";
				cout << timeToString(minute) << " " << blueQuarter.blueElement << " " << "elements in blue headquarter\n";
			}
			if (minute % 60 == 55 && !gameover) {              //武士报告拥有武器情况

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
