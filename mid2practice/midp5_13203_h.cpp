#include <string>
#include <iostream>
#include <sstream>
using namespace std;

class Human {
public:
	string name;
	int money;
	int skill;
	bool kicked;
	int cards;
	int bets;

	Human(string n, int m, int ski);
	
	virtual void Pay(Human *human) = 0;
	virtual void Bet() {}
	virtual void Draw() {}
	virtual bool Kicked() {}
	virtual int Win(Human *human) {}
	virtual bool Bankrupt() {}
	virtual void Kick(Human *human, int flag) {}
	virtual bool Cheat(Human *human) {}
	int get_money();
	~Human();
};

class Guard : public virtual Human {
public:
	Guard(int ski);
	void Pay(Human *human);
	void Kick(Human *human, int flag);
	~Guard(); 
};

class Banker : public virtual Human {
public:
	Banker(int ski);
	void Pay(Human *human);
	int Win(Human *human);
	void Draw();
	~Banker();
};

class Player : public virtual Human {
public:
	Player(string name, int m, int ski);
	void Pay(Human *human);
	void Bet();
	void Draw();
	bool Kicked();
	bool Bankrupt();
	bool Cheat(Human *human);
	~Player();
};

Human::Human(string n, int m, int ski){
    name = n;
    money = m;
    skill = ski;
    kicked = false;
    cards = 0;
    bets = 0;
}
int Human::get_money(){
    return money;
}
Human::~Human() = default;

Guard::Guard(int ski):Human::Human("Guard", 0, ski) {}
void Guard::Pay(Human *human) {
    human->money += human->skill - this->skill;
    this->money -= human->skill - this->skill;
}
void Guard::Kick(Human *human, int flag){
    if(flag == 1 && this->skill < human->skill) this->Pay(human);
    human->kicked = true;
}

Banker::Banker(int ski):Human::Human("Banker", 0, ski) {}
int bankerpay;
void Banker::Pay(Human *human) {
    if(human->name == "Guard") {
        this->money -= 100;
        human->money += 100;
    } else {
        int bonus = 0;
        if(human->skill < this->skill) bonus = (10 * human->cards);
        
        if(human->cards == 21) {
           bankerpay = 2 * (human->bets + bonus);
        } else {
           bankerpay = (human->bets + bonus);
        }
        this->money -= bankerpay;
        human->money += bankerpay;
    }
}
int Banker::Win(Human *human) {
    if(human->cards > 21 && this->cards > 21) return 2;
    else if(human->cards <= 21 && (this->cards > 21 || human->cards > this->cards)) return 0;
    else return 1;
}
void Banker::Draw() {
    this->cards = 0;
	//cin.ignore();
	string card_string;
	getline(cin, card_string);
	istringstream input_stream(card_string); // Included in <sstream>
	int card;
	while (input_stream >> card) cards += card;
}
Banker::~Banker() = default;

Player::Player(string name, int m, int ski):Human::Human(name, m, ski) {}
void Player::Pay(Human *human){
    if(this->bets >= this->money) {
        human->money += this->money;
        this->money = 0;
    } else {
        human->money += this->bets;
        this->money -= this->bets;
    }
}
void Player::Bet() {
    cin >> this->name >> this->bets;
}
void Player::Draw(){
    this->cards = 0;
	cin.ignore();
	string card_string;
	getline(cin, card_string);
	istringstream input_stream(card_string); // Included in <sstream>
	int card;
	while(input_stream >> card) cards += card;
}
bool Player::Kicked() {
    return this->kicked;
}
bool Player::Bankrupt() {
    if(this->money <= 0) return true;
    else return false;
}
bool Player::Cheat(Human *human) {
    if(this->skill * 2 < bankerpay) return true;
    else return false;
}
Player::~Player() = default;