#include <string>
using namespace std;

class Guest {
public:
	Guest();
	Guest(string s, int m, int ski);
	~Guest();
	string get_name();
	int get_money();
	int get_skill();
	void Win(int m);
	
private:
	string name;
	int money;
	int skill;
};

class Casino {
public:
	Casino();
	~Casino();
	void Enterance(int f);
	void GuestEnter(string s, int m, int ski);
	void Win(string s, int m);
	void EndDay();
	void Result();
	
private:
	int fee;
	
	int guest_num;
	Guest *guest[1009];
	
	int income;
	int list_num;
	string blacklist[1009];
};

#include <iostream>

Guest::Guest(){
    name = "";
    money = 0;
    skill = 0;
}
Guest::Guest(string s, int m, int ski){
    name = s;
    money = m;
    skill = ski;
}
Guest::~Guest() = default;
string Guest::get_name(){
    return name;
}
int Guest::get_money(){
    return money;
}
int Guest::get_skill(){
    return skill;
}
void Guest::Win(int m){
    money += m;
}

Casino::Casino(){
    fee = 0;
    guest_num = 0;
    income = 0;
    list_num = 0;
}
Casino::~Casino(){
    for(int i = 0; i < guest_num; i++) if(guest[i]) {
        delete guest[i];
        guest[i] = nullptr;
    }
}
void Casino::Enterance(int f){
    fee = f;
}
void Casino::GuestEnter(string s, int m, int ski){
    // Check if is blanklist
    for(int i = 0; i < list_num; i++){
        if(s == blacklist[i]) return;
    }
    // Check if is in Casino
    for(int i = 0; i < guest_num; i++){
        if(guest[i] && s == guest[i]->get_name()) return;
    }
    // If no money to pay fee
    if(m <= fee){
        income += m;
        blacklist[list_num++] = s;
        return;
    }
    // Else add to guest
    Guest *new_guest = new Guest(s, m-fee, ski);
    income += fee;
    for(int i = 0; i < guest_num; i++){
        if(!guest[i]){
            guest[i] = new_guest;
            return;
        }
    }
    guest[guest_num++] = new_guest;
    /*
    guest[guest_num++] = new Guest(s, m - fee, ski);
	income += fee;
    */
}
void Casino::Win(string s, int m){
    // Check if is blanklist
    for(int i = 0; i < list_num; i++){
        if(s == blacklist[i]) return;
    }
    // Check if is in Casino
    for(int i = 0; i < guest_num; i++){
        if(guest[i] && s == guest[i]->get_name()){
            // Ban if bankrupt or cheat
            if(guest[i]->get_money() + m < 0){
                m = -guest[i]->get_money();
                blacklist[list_num++] = guest[i]->get_name();
                delete guest[i];
                guest[i] = nullptr;
            } else if (m > 2 * guest[i]->get_skill()) {
                blacklist[list_num++] = guest[i]->get_name();
                delete guest[i];
                guest[i] = nullptr;
            } else {
                guest[i]->Win(m);
            }
            income -= m;
            return;
        }
    }
}
void Casino::EndDay(){
    for(int i = 0; i < guest_num; i++) if(guest[i]){
        delete guest[i];
        guest[i] = nullptr;
    }
    guest_num = 0;
}
void Casino::Result(){
    using std::cout;
    using std::endl;
    cout << income << endl;
    for(int i = 0; i < list_num; i++) cout << blacklist[i] << endl;
}