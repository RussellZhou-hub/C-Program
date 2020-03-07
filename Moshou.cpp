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
	int nextGenerate;
	int iniElement[5] = {0,0,0,0,0};
	int iniForce[5]= { 0,0,0,0,0 };
	bool stopGen = false;                   //是否停止制造
	string indexToName[5] = { "dragon","ninja","iceman","lion","wolf" };
	HeadQuarter(int col) {
		color = col;
		nextGenerate = 0;
	}
	int generate() {                 //返回-1表示停止制造
		if (!stopGen && color == 0) {
			int order[5] = { 2,3,4,1,0 };          //红方司令部按照iceman、lion、wolf、ninja、dragon 的顺序制造武士。
			if (redElement - iniElement[order[nextGenerate]] >= 0) {
				redElement -= iniElement[order[nextGenerate]];
				int tmp = nextGenerate;
				nextGenerate = ++nextGenerate % 5;                   //下一次降生
				return order[tmp];
			}
			else if (redElement - iniElement[order[nextGenerate]] < 0) {     //如果司令部中的生命元不足以制造某本该造的武士，那就从此停止制造武士。
				stopGen = true;
				return -1;
			}
		}
		else if(!stopGen && color==1){
			int order[5] = { 3,0,1,2,4 };     //蓝方司令部按照lion、dragon、ninja、iceman、wolf 的顺序制造武士。
			if (blueElement - iniElement[order[nextGenerate]] >= 0) {
				blueElement -= iniElement[order[nextGenerate]];
				int tmp = nextGenerate;
				nextGenerate = ++nextGenerate % 5;                   //下一次降生
				return order[tmp];
			}
			else if (blueElement - iniElement[order[nextGenerate]] < 0) {     //如果司令部中的生命元不足以制造某本该造的武士，那就从此停止制造武士。
				stopGen = true;
				return -1;
			}
		}
		return -1;
	}
};
int HeadQuarter::redElement = 0;
int HeadQuarter::blueElement = 0;    

class Weapon {                            //武器类
public:
	int size,id,attack_effect;       //size该种武器数量
	class Info {                      //武器信息类
	public:
		int available;
		bool used;
		Info() {
			available = 0;
			used = false;
		}
		Info(int a,bool u=false) {
			available = a;
			used = u;
		}
		friend bool operator<(const Info & info,const Info & info2) {
			if (info.used == true && info2.used == false) return true;        //用过的排使用顺序前面
			return false;
		}
	};
	
	vector<Info> mvecInfo;     //每个该种剩余使用次数，最多10个武器,用过的排在前面
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
	void gain() {                     //获得武器时
		if (id == 0) {
			mvecInfo.push_back(Info( 3) );
		}
		else if(id == 1) {
			mvecInfo.push_back(Info(1));
		}
		else if (id == 2) {
			mvecInfo.push_back(Info(2));
		}
		size++;
	}
	void wSort() {                //同种武器排序使用过的排前面
		if (size > 0) {
			sort(mvecInfo.begin(), mvecInfo.end());
		}
	}
	void add(Info newWeapon) {
		mvecInfo.push_back(newWeapon);
		size++;
	}
	vector<Info>::iterator sub() {         //优先减去没用过的
		wSort();
		size--;
		return --mvecInfo.erase(--mvecInfo.end());
	}
	void use() {
		if (id == 1) {
			vector<Info>::iterator it;           //一次性炸弹
			it = mvecInfo.begin();
			mvecInfo.erase(it);
			size--;
		}
		else if(id==2) {
			vector<Info>::iterator it;
			it = mvecInfo.begin();
			if ((*it).used == true) {      //再用就没了
				mvecInfo.erase(it);
				size--;
			}
			else {
				(*it).used = true;       //标记用过了
				(*it).available--;
			}
		}
	}
};


class Soldier {                                //战士
public:
	static int redNumSoldier;
	static int blueNumSoldier;
	bool reachHeadQ = false;                  //达到 对方司令部标志位
	int element,force,id,city,color,index;     //0代表红1代表蓝
	int takeInfo[3] = { 0,0,0 };              //夺取武器信息
	string colorToName[2] = { "red","blue" };
	string indexToName[5] = { "dragon","ninja","iceman","lion","wolf" };
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
	int getTotalWeaponNum() {                //总共几件武器
		int size=0;
		for (auto i = 0; i < 3; i++) {
			size += weapon[i].size;
		}
		return size;
	}
	void weaponSort() {
		for (auto i=0; i < 3; i++) {
			if (weapon[i].size > 0) {
				weapon[i].wSort();
			}
		}
	}
	void hurt(int loss) {
		element -= loss;
	}
	void take(Soldier* rival) {       //获胜后缴获
		for (auto i = 0; i < 3; i++) takeInfo[i] = 0;
		bool taken = false;
		int total = getTotalWeaponNum();
		int rSword, rBomb, rArrow;
		if (total == 10) return;
		rSword = rival->weapon[0].size;
		rBomb = rival->weapon[1].size;
		rArrow = rival->weapon[2].size;
		if (total + rSword <= 10 && weapon[0].size + rSword <= 10) {    //能将对手的sword全部夺取
			takeInfo[0] = rSword;
			for (auto i = 0; i < rSword; i++) {
				weapon[0].add(*(rival->weapon[0].sub()));
			}
			weapon[0].size += rSword;
			total += rSword;
		}
		else if (total + rSword <= 10 && weapon[0].size + rSword > 10) {    //只能夺取一部分
			takeInfo[0] = rSword - (10 - weapon[0].size);
			for (auto i = 0; i < rSword; i++) {
				weapon[0].add(*(rival->weapon[0].sub()));
			}
			weapon[0].size += takeInfo[0];
			total += takeInfo[0];
		}
		if (  total + rBomb <= 10 && weapon[0].size + rSword <= 10) {    //能将对手的bomb全部夺取
			takeInfo[1] = rBomb;
			for (auto i = 0; i < rSword; i++) {
				weapon[0].add(*(rival->weapon[0].sub()));
			}
			weapon[1].size += rBomb;
			total += rBomb;
		}
		else if (  total + rBomb <= 10 && weapon[0].size + rSword > 10) {    //部分 对手的bomb夺取
			takeInfo[1] = rBomb - (10 - weapon[1].size);
			for (auto i = 0; i < rSword; i++) {
				weapon[0].add(*(rival->weapon[0].sub()));
			}
			weapon[1].size += takeInfo[1];
			total += takeInfo[1];
		}
		if (  total + rArrow <= 10 && weapon[2].size + rArrow <= 10) {    //能将对手的arrow全部夺取
			takeInfo[2] = rArrow;
			for (auto i = 0; i < rSword; i++) {
				weapon[0].add(*(rival->weapon[0].sub()));
			}
			weapon[2].size += rArrow;
			total += rArrow;
		}
		else if (  total + rArrow <= 10 && weapon[2].size + rArrow > 10) {    //只能夺取一部分arrow
			takeInfo[2] = rArrow - (10 - weapon[2].size);
			for (auto i = 0; i < rSword; i++) {
				weapon[0].add(*(rival->weapon[0].sub()));
			}
			weapon[2].size += takeInfo[2];
			total += takeInfo[2];
		}
	}
	virtual void attack(Soldier* rival,int weaponId){}
	virtual int* iniTake(Soldier* rival) { return takeInfo; }
	virtual void move(){}
	virtual int getLoyalty() { return 1; }
	virtual void setLoyalty(int x) { }
};
int Soldier::redNumSoldier = 0;
int Soldier::blueNumSoldier = 0;

template<class T>
class LessByCity {          //同一时间发生的事件，按发生地点从西向东依次输出..对于同一城市，同一时间发生的事情，先输出红方的，后输出蓝方的。
public:
	bool operator()(const T & a,const T & b) {
		if ((a->city) < (b->city) || (a->city) == (b->city) && (a->color) < (b->color)) return true;
		else return false;
	}
};


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
	void attack(Soldier* rival, int weaponId) {
		if (weaponId == 0) {        //用剑攻击
			int thisForce = force * weapon[weaponId].attack_effect / 10;
			rival->hurt(thisForce);
		}
		else if (weaponId == 1) {
			int thisForce = force * weapon[weaponId].attack_effect / 10;
			rival->hurt(thisForce);
			thisForce /= 2;
			hurt(thisForce);
			weapon[1].use();
		}
		else if (weaponId == 2) {
			int thisForce = force * weapon[weaponId].attack_effect / 10;
			rival->hurt(thisForce);
			weapon[2].use();
		}
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
		int weaponID = id % 3;   //编号为n的ninja降生时即获得编号为n%3和(n+1) 的武器
		weapon[weaponID].gain();
		weaponID = (id+1) % 3;
		weapon[weaponID].gain();
	}
	~Ninja() {
		if (color == 0) {
			redNumNinja--;
		}
		else {
			blueNumNinja--;
		}
	}
	void attack(Soldier* rival,int weaponId) {      //ninja 使用bomb不会让自己受伤。
		if (weaponId == 0) {        //用剑攻击
			int thisForce = force * weapon[weaponId].attack_effect / 10;
			rival->hurt(thisForce);
		}
		else if (weaponId == 1) {
			int thisForce = force * weapon[weaponId].attack_effect / 10;
			rival->hurt(thisForce);
			weapon[1].use();
		}
		else if (weaponId == 2) {
			int thisForce = force * weapon[weaponId].attack_effect / 10;
			rival->hurt(thisForce);
			weapon[2].use();
		}
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
		int weaponID = id % 3;   //编号为n的iceman降生时即获得编号为n%3 的武器
		weapon[weaponID].gain();
	}
	~Iceman() {
		if (color == 0) {
			redNumIceman--;
		}
		else {
			blueNumIceman--;
		}
	}
	void attack(Soldier* rival, int weaponId) {
		if (weaponId == 0) {        //用剑攻击
			int thisForce = force * weapon[weaponId].attack_effect / 10;
			rival->hurt(thisForce);
		}
		else if (weaponId == 1) {
			int thisForce = force * weapon[weaponId].attack_effect / 10;
			rival->hurt(thisForce);
			thisForce /= 2;
			hurt(thisForce);
			weapon[1].use();
		}
		else if (weaponId == 2) {
			int thisForce = force * weapon[weaponId].attack_effect / 10;
			rival->hurt(thisForce);
			weapon[2].use();
		}
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
			loyalty = lo;
		}
		index = 3;
		int weaponID = id % 3;   //编号为n的lion降生时即获得编号为n%3 的武器
		weapon[weaponID].gain();
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
	void attack(Soldier* rival, int weaponId) {
		if (weaponId == 0) {        //用剑攻击
			int thisForce = force * weapon[weaponId].attack_effect / 10;
			rival->hurt(thisForce);
		}
		else if (weaponId == 1) {
			int thisForce = force * weapon[weaponId].attack_effect / 10;
			rival->hurt(thisForce);
			thisForce /= 2;
			hurt(thisForce);
			weapon[1].use();
		}
		else if (weaponId == 2) {
			int thisForce = force * weapon[weaponId].attack_effect / 10;
			rival->hurt(thisForce);
			weapon[2].use();
		}
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
	void attack(Soldier* rival, int weaponId) {
		if (weaponId == 0) {        //用剑攻击
			int thisForce = force * weapon[weaponId].attack_effect / 10;
			rival->hurt(thisForce);
		}
		else if (weaponId == 1) {
			int thisForce = force * weapon[weaponId].attack_effect / 10;
			rival->hurt(thisForce);
			thisForce /= 2;
			hurt(thisForce);
			weapon[1].use();
		}
		else if (weaponId == 2) {
			int thisForce = force * weapon[weaponId].attack_effect / 10;
			rival->hurt(thisForce);
			weapon[2].use();
		}
	}
	int* iniTake(Soldier* rival) {
		for (auto i = 0; i < 3; i++) takeInfo[i] = 0;
		bool taken = false;
		int total = getTotalWeaponNum();
		int rSword, rBomb, rArrow;
		if (total == 10) return takeInfo;
		rSword = rival->weapon[0].size;
		rBomb = rival->weapon[1].size;
		rArrow = rival->weapon[2].size;
		if (total + rSword <= 10 && weapon[0].size+rSword <=10 ) {    //能将对手的sword全部夺取
			takeInfo[0] = rSword;
			for (auto i = 0; i < rSword;i++) {
				weapon[0].add(*(rival->weapon[0].sub()));
			}
			weapon[0].size += rSword;
			total += rSword;
			taken = true;
		}
		else if ( total + rSword <= 10 && weapon[0].size + rSword > 10) {    //只能夺取一部分
			takeInfo[0] = rSword - (10 - weapon[0].size);
			for (auto i = 0; i < rSword; i++) {
				weapon[0].add(*(rival->weapon[0].sub()));
			}
			weapon[0].size += takeInfo[0];
			total += takeInfo[0];
			taken = true;
		}
		if (!taken &&  total + rBomb <= 10 && weapon[0].size + rSword <= 10) {    //能将对手的bomb全部夺取
			takeInfo[1] = rBomb;
			for (auto i = 0; i < rSword; i++) {
				weapon[0].add(*(rival->weapon[0].sub()));
			}
			weapon[1].size += rBomb;
			total += rBomb;
			taken = true;
		}
		else if (!taken && total + rBomb <= 10 && weapon[0].size + rSword > 10) {    //部分 对手的bomb夺取
			takeInfo[1] = rBomb - (10 - weapon[1].size);
			for (auto i = 0; i < rSword; i++) {
				weapon[0].add(*(rival->weapon[0].sub()));
			}
			weapon[1].size += takeInfo[1];
			total += takeInfo[1];
			taken = true;
		}
		if (!taken && total + rArrow <= 10 && weapon[2].size + rArrow <= 10) {    //能将对手的arrow全部夺取
			takeInfo[2] = rArrow;
			for (auto i = 0; i < rSword; i++) {
				weapon[0].add(*(rival->weapon[0].sub()));
			}
			weapon[2].size += rArrow;
			total += rArrow;
			taken = true;
		}
		else if (!taken && total + rArrow <= 10 && weapon[2].size + rArrow > 10) {    //只能夺取一部分arrow
			takeInfo[2] = rArrow - (10 - weapon[2].size);
			for (auto i = 0; i < rSword; i++) {
				weapon[0].add(*(rival->weapon[0].sub()));
			}
			weapon[2].size += takeInfo[2];
			total += takeInfo[2];
			taken = true;
		}
		return takeInfo;
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

int battle(Soldier* r, Soldier* b,int whoFirst) {          //战斗过程
	if (whoFirst == 0) {
		bool rAttacked = false, bAttacked = false;//本轮攻击结束标志
		int rWeaponRound = 0, bWeaponRound = 0;
		while (r->element > 0 && b->element > 0 && ( r->force>0 || b->force>0 ) && r->getTotalWeaponNum() > 0 && b->getTotalWeaponNum() > 0) {
			if (r->weapon[rWeaponRound].size > 0) {
				r->attack(b, rWeaponRound);
				rAttacked = true;
				if (r->weapon[rWeaponRound].size == 0) rWeaponRound = (++rWeaponRound) % 3;       //这种武器用完
				if (b->element <= 0) return 0;
			}
			if (r->weapon[bWeaponRound].size > 0) {
				r->attack(r, bWeaponRound);
				bAttacked = true;
				if (b->weapon[bWeaponRound].size == 0) bWeaponRound = (++bWeaponRound) % 3;       //这种武器用完
				if (r->element <= 0) return 1;
			}
		}
		//战斗停止
		if (r->element > 0 && b->element > 0) return 2;
		else return -1;
	}
	else {
		bool rAttacked = false, bAttacked = false;//本轮攻击结束标志

	}
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
		vector<Soldier*> allSoldier;         //全部战士容器
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
					allSoldier.push_back(new Dragon(redQuarter.iniElement[index], redQuarter.iniForce[index], 0));
				}
				else if (index == 1) {
					allSoldier.push_back(new Ninja(redQuarter.iniElement[index], redQuarter.iniForce[index], 0));
				}
				else if (index == 2) {
					allSoldier.push_back(new Iceman(redQuarter.iniElement[index], redQuarter.iniForce[index], 0));
				}
				else if (index == 3) {
					allSoldier.push_back(new Lion(redQuarter.iniElement[index], redQuarter.iniForce[index], 0,redQuarter.redElement) );
				}
				else if (index == 4) {
					allSoldier.push_back(new Wolf(redQuarter.iniElement[index], redQuarter.iniForce[index], 0));
				}
				if (index != -1) {
					cout << timeToString(minute) << " red " << redQuarter.indexToName[index] << " " << (*allSoldier.back()).id << " born\n";
					if (index == 3)   cout << "Its loyalty is " << allSoldier.back()->getLoyalty() << "\n";
				}
				index = blueQuarter.generate();
				if (index == 0) {
					allSoldier.push_back(new Dragon(blueQuarter.iniElement[index], blueQuarter.iniForce[index], 1));
				}
				else if (index == 1) {
					allSoldier.push_back(new Ninja(blueQuarter.iniElement[index], blueQuarter.iniForce[index], 1));
				}
				else if (index == 2) {
					allSoldier.push_back(new Iceman(blueQuarter.iniElement[index], blueQuarter.iniForce[index], 1));
				}
				else if (index == 3) {
					allSoldier.push_back(new Lion(blueQuarter.iniElement[index], blueQuarter.iniForce[index], 1,blueQuarter.blueElement) );
				}
				else if (index == 4) {
					allSoldier.push_back(new Wolf(blueQuarter.iniElement[index], blueQuarter.iniForce[index], 1));
				}
				if (index != -1) {
					cout << timeToString(minute) << " blue " << blueQuarter.indexToName[index] << " " << (*allSoldier.back()).id << " born\n";
					if (index == 3)   cout << "Its loyalty is " << allSoldier.back()->getLoyalty() << "\n";
				}
			}
			if (minute % 60 == 5) {             //lion逃跑
				vector<Soldier*>::iterator S_it;
				LessByCity<Soldier*> myLess;
				sort(allSoldier.begin(), allSoldier.end(), myLess);          //先排序
				S_it = allSoldier.begin();
				for (; S_it != allSoldier.end(); ) {
					if ((*S_it)->index == 3 && (*S_it)->getLoyalty() <=0 && (*S_it) ->color==0 && (*S_it)->city!=N+1 ) {                 //不在对方司令部，忠诚度<=0
						cout << timeToString(minute) << " red lion " << (*S_it)->id << " ran away\n";
						(*S_it)->~Soldier();
						S_it = allSoldier.erase(S_it);
						if (S_it == allSoldier.end()) break;
					}
					else if ((*S_it)->index == 3 && (*S_it)->getLoyalty() <= 0 && (*S_it)->color == 1 && (*S_it)->city != 0) {        //不在对方司令部，忠诚度<=0
						cout << timeToString(minute) << " blue lion " << (*S_it)->id << " ran away\n";
						(*S_it)->~Soldier();
						S_it = allSoldier.erase(S_it);
						if (S_it == allSoldier.end()) break;
					}
					else S_it++;
				}
			}
			if (minute % 60 == 10) {             //前进
				LessByCity<Soldier*> myLess;
				vector<Soldier*>::iterator S_it;
				S_it = allSoldier.begin();
				for (; S_it != allSoldier.end(); S_it++) {
					if ((*S_it) ->color==0 && (*S_it)->city != N + 1 && (*S_it)->reachHeadQ==false ) {      //red还没到对方司令部
						(*S_it)->city++;
						if ((*S_it)->city == N + 1) (*S_it)->reachHeadQ = true;
						if ((*S_it)->index == 2) (*S_it)->element = ((*S_it)->element * 9) / 10;      //生命值减少
						if ((*S_it)->index == 3) (*S_it)->setLoyalty((*S_it)->getLoyalty() - K);     //忠诚减少
					}
					else if ((*S_it)->color == 1 && (*S_it)->city != 0 && (*S_it)->reachHeadQ == false) {      //blue还没到对方司令部
						(*S_it)->city--;
						if ((*S_it)->city == 0) (*S_it)->reachHeadQ = true;
						if ((*S_it)->index == 2) (*S_it)->element = ((*S_it)->element * 9) / 10;      //生命值减少
						if ((*S_it)->index == 3) (*S_it)->setLoyalty((*S_it)->getLoyalty() - K);     //忠诚减少
					}
				}
				sort(allSoldier.begin(), allSoldier.end(), myLess);        //前进完后排序
				S_it = allSoldier.begin();
				for (; S_it != allSoldier.end(); S_it++) {
					if ( (*S_it)->color==0 && (*S_it)->city != N + 1) {      //还没到对方司令部
						cout << timeToString(minute) << " " << "red " << redQuarter.indexToName[(*S_it)->index] << " " << (*S_it)->id << " marched to city " << (*S_it)->city << " with " << (*S_it)->element << " elements and force " << (*S_it)->force << "\n";
					}
					else if ((*S_it)->color == 0 && (*S_it)->city == N + 1 && (*S_it)->reachHeadQ == false ) {
						cout << timeToString(minute) << " " << "red " << redQuarter.indexToName[(*S_it)->index] << " " << (*S_it)->id << " reached blue headquarter with " << (*S_it)->element << " elements and force " << (*S_it)->force << "\n";
						cout << timeToString(minute) << " blue headquarter was taken\n";
						(*S_it)->reachHeadQ = true;
						gameover = true;
					}
					else if ((*S_it)->color == 1 && (*S_it)->city != 0) {     //还没到对方司令部
						cout << timeToString(minute) << " " << "blue " << blueQuarter.indexToName[(*S_it)->index] << " " << (*S_it)->id << " marched to city " << (*S_it)->city << " with " << (*S_it)->element << " elements and force " << (*S_it)->force << "\n";
					}
					else if ((*S_it)->color == 1 && (*S_it)->city == 0 && (*S_it)->reachHeadQ == false) {
						cout << timeToString(minute) << " " << "blue " << redQuarter.indexToName[(*S_it)->index] << " " << (*S_it)->id << " reached blue headquarter with " << (*S_it)->element << " elements and force " << (*S_it)->force << "\n";
						cout << timeToString(minute) << " red headquarter was taken\n";
						(*S_it)->reachHeadQ = true;
						gameover = true;
					}
				}
			}
			if (minute % 60 == 35 && !gameover && allSoldier.size()!=0) {              //wolf抢夺武器
				LessByCity<Soldier*> myLess;
				sort(allSoldier.begin(), allSoldier.end(), myLess);            //先排序 
				vector<Soldier*>::iterator S_it,next_it,tmp_it;
				S_it = allSoldier.begin();
				next_it = S_it;
				next_it++;        //bug
				for (; S_it != --allSoldier.end(); S_it++,next_it++) {
					if ((*S_it)->reachHeadQ == false && (*S_it)->city == (*next_it)->city && (*S_it)->color != (*next_it)->color) {     //具备战斗发生条件
						if ((*S_it)->index == 4 && (*next_it)->index != 4 && (*S_it) ->getTotalWeaponNum()<10 ) {     //狼抢武器条件
							int* info;
							info=(*S_it)->iniTake(*next_it);          //调用抢夺函数
							for (auto i = 0; i < 3; i++) {
								if (info[i] != 0) {
									cout << timeToString(minute) << " " << (*S_it)->colorToName[(*S_it)->color] << " " << (*S_it)->indexToName[(*S_it)->index] << " ";
									cout << (*S_it)->id << " took " << info[i] << " " << (*S_it)->weapon[i].idToName[i] << " from ";
									cout << (*next_it)->colorToName[(*next_it)->color] << " " << (*next_it)->indexToName[(*next_it)->index] << " ";
									cout << (*next_it)->id << " in city " << (*next_it)->city<<"\n";
								}
							}
							
						}
						else if ((*S_it)->index != 4 && (*next_it)->index == 4 && (*next_it)->getTotalWeaponNum() < 10) {     //狼抢武器条件
							int* info;
							info = (*next_it)->iniTake(*S_it);          //调用抢夺函数
							for (auto i = 0; i < 3; i++) {
								if (info[i] != 0) {
									cout << timeToString(minute) << " " << (*next_it)->colorToName[(*next_it)->color] << " " << (*next_it)->indexToName[(*next_it)->index] << " ";
									cout << (*next_it)->id << " took " << info[i] << " " << (*next_it)->weapon[i].idToName[i] << " from ";
									cout << (*S_it)->colorToName[(*S_it)->color] << " " << (*S_it)->indexToName[(*S_it)->index] << " ";
									cout << (*S_it)->id << " in city " << (*S_it)->city << "\n";
								}
							}
						}
						tmp_it = next_it;
						tmp_it++;
						if (tmp_it == --allSoldier.end()) break;
						else S_it++, next_it++;        //本次循环后移2位
					}

				}

			}
			if (minute % 60 == 40 && !gameover && allSoldier.size() != 0) {              //战斗
				LessByCity<Soldier*> myLess;
				sort(allSoldier.begin(), allSoldier.end(), myLess);            //先排序 
				vector<Soldier*>::iterator S_it, next_it, tmp_it,r_it,b_it;
				S_it = allSoldier.begin();
				next_it = S_it;
				next_it++;
				for (; S_it != --allSoldier.end() && S_it!= allSoldier.end(); S_it++, next_it++) {
					if ((*S_it)->reachHeadQ == false && (*S_it)->city == (*next_it)->city && (*S_it)->color != (*next_it)->color) {     //具备战斗发生条件
						int city = (*S_it)->city;
						(*S_it)->weaponSort();
						(*next_it)->weaponSort();     //先排序武器
						if ((*S_it)->color == 0) {
							r_it = S_it;
							b_it = next_it;
						}
						else {
							r_it = next_it;
							b_it = S_it;
						}
						int result;              //2都活-1都死 0红杀死蓝 1蓝杀死红
						if (city % 2 == 1) {    //在奇数编号城市，红武士先发起攻击
							result = battle(*r_it,*b_it,0);
						}
						else if (city % 2 == 0) {       //在偶数编号城市，蓝武士先发起攻击
							result = battle(*r_it, *b_it, 1);
						}
						if (result == 0) {     //红杀死蓝 
							(*r_it)->take(*b_it);
							if ((*r_it)->index == 0) {
								cout << timeToString(minute) <<" "<< (*r_it)->colorToName[(*r_it)->color] << " " << (*r_it)->indexToName[(*r_it)->index] << " "<< (*next_it)->id<<" yelled in city "<<city<<"\n";
							}
							(*b_it) ->~Soldier();
							S_it = allSoldier.erase(b_it);
							if (S_it == allSoldier.end()) break;
							else {
								next_it = S_it;
								next_it++;
								continue;
							}
						}
						else if (result == 1) {   //蓝杀死红
							(*b_it)->take(*r_it);
							if ((*b_it)->index == 0) {
								cout << timeToString(minute) << " " << (*b_it)->colorToName[(*b_it)->color] << " " << (*b_it)->indexToName[(*b_it)->index] << " " << (*next_it)->id << " yelled in city " << city << "\n";
							}
							(*r_it) ->~Soldier();
							S_it = allSoldier.erase(r_it);
							if (S_it == allSoldier.end()) break;
							else {
								next_it = S_it;
								next_it++;
								continue;
							}
						}
						else if (result == 2) {    //都活
							cout << timeToString(minute) << " both red " << (*r_it)->indexToName[(*r_it)->index] << " ";
							cout<< (*r_it)->id << " and blue "<<(*b_it)->indexToName[(*b_it)->index] << " " << (*b_it)->id <<" were alive in city " << city << "\n";
							if (next_it == --allSoldier.end()) break;
							else {
								S_it = next_it;
								S_it++;
								next_it = S_it;
								next_it++;
								continue;
							}
						}
						else if (result == -1) {    //都死
							cout << timeToString(minute) << " both red " << (*r_it)->indexToName[(*r_it)->index] << " " << (*r_it)->id << " and blue ";
							cout << (*b_it)->indexToName[(*b_it)->index] << " " << (*b_it)->id << " died in city " << city << "\n";
							(*b_it) ->~Soldier();
							(*r_it) ->~Soldier();
							if (next_it == (--allSoldier.end())) {
								allSoldier.erase(b_it);
								allSoldier.erase(r_it);
								break;
							}
							else {
								allSoldier.erase(S_it);
								S_it = allSoldier.erase(next_it);
								next_it = S_it;
								next_it++;
								continue;
							}
						}
					}


				}
			}
			if (minute % 60 == 50 && !gameover) {              //司令部报告生命元
				cout << timeToString(minute) << " " << redQuarter.redElement << " " << "elements in red headquarter\n";
				cout << timeToString(minute) << " " << blueQuarter.blueElement << " " << "elements in blue headquarter\n";
			}
			if (minute % 60 == 55 && !gameover) {              //武士报告拥有武器情况
				vector<Soldier*>::iterator it_start, it_end;
				LessByCity<Soldier*> myLess;
				sort(allSoldier.begin(), allSoldier.end(),myLess);
				it_start = allSoldier.begin();
				it_end = allSoldier.end();
				for (; it_start != it_end; it_start++) {
					cout << timeToString(minute) << " " << (*it_start)->colorToName[(*it_start)->color] << " " << (*it_start)->indexToName[(*it_start)->index] << " ";
					cout << (*it_start)->id << " has ";
					cout<< (*it_start)->weapon[0].size<< " sword "<< (*it_start)->weapon[1].size<<" bomb "<< (*it_start)->weapon[2].size<<" arrow and "<< (*it_start)->element<< " elements\n";
				}
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
