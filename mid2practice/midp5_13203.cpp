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
	cards = bets = 0;
}
int Human::get_money(){
	return this->money;
}
Human::~Human(){

}
Guard::Guard(int ski) : Human::Human("Guard", 0, ski){
	this->skill = ski;
}
void Guard::Pay(Human *human){
	this->money -= (human->skill - this->skill);
	human->money += (human->skill - this->skill);
}
void Guard::Kick(Human *human, int flag){
	if(flag == 1 && this->skill < human->skill) this->Pay(human);
	human->kicked = true;
}
Banker::Banker(int ski) : Human::Human("Banker", 0, ski){
	this->skill = ski;
}
int bankerToPay;
void Banker::Pay(Human *human){
	if(human->name == "Guard"){
		this->money -= 100;
		human->money += 100;
	}else{
		int bonus = 0;
		if(human->skill < this->skill) bonus = (10 * human->cards);

		if(human->cards == 21) bankerToPay = 2 * (human->bets + bonus);
		else bankerToPay = human->bets + bonus;

		this->money -= bankerToPay;
		human->money += bankerToPay;
	}
}
int Banker::Win(Human *human){
	if(human->cards > 21 && this->cards > 21) return 2; // Nothing happen
	else if(human->cards <= 21 && (human->cards > this->cards || this->cards > 21)) return 0; // Player win
	else return 1; // Banker win
}
void Banker::Draw(){
	this->cards = 0;
	//cin.ignore();
	string card_string;
	getline(cin, card_string);
	istringstream input_stream(card_string); // Included in <sstream>
	int card;
	while (input_stream >> card) cards += card;
}
Banker::~Banker(){

}
Player::Player(string name, int m, int ski) : Human::Human(name, m, ski){
	this->name = name;
	this->money = m;
	this->skill = ski;
}
void Player::Pay(Human *human){
	if(this->bets >= this->money){
		human->money += this->money;
		this->money = 0;
	}else{
		human->money += this->bets;
		this->money -= this->bets;
	}
}
void Player::Bet(){
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
bool Player::Kicked(){
	return this->kicked;
}
bool Player::Bankrupt(){
	if(this->money <= 0) return true;
	else return false;
}
bool Player::Cheat(Human *human){
	if(2 * this->skill < bankerToPay) return true;
	else return false;
}
Player::~Player(){

}


signed main() {
	int guard_skill, banker_skill;
	cin >> guard_skill >> banker_skill;
	Human *guard = new Guard(guard_skill);
	Human *banker = new Banker(banker_skill);

	Human *player[1009];
	int n;
	cin >> n;
	for (int i = 1; i <= n; ++ i) {
		string name;
		int player_money, player_skill;
		cin >> name >> player_money >> player_skill;
		player[i] = new Player(name, player_money, player_skill);
	}

	int k;
	cin >> k;
	while (k--) {
		for (int i = 1; i <= n; ++ i) {
			player[i]->Bet();
			player[i]->Draw();
		}
		banker->Draw();
	
		for (int i = 1; i <= n; ++ i) {
			if (player[i]->Kicked())
				continue;
			
			if (banker->Win(player[i]) == 1) {
				player[i]->Pay(banker);
				if (player[i]->Bankrupt()) {
					banker->Pay(guard);
					guard->Kick(player[i], 0);
				}
			}
			else if (banker->Win(player[i]) == 0) {
				banker->Pay(player[i]);
				if (player[i]->Cheat(banker)) {
					banker->Pay(guard);
					guard->Kick(player[i], 1);
				}
			} // otherwise draw
		}
	}
	
	cout << guard->get_money() << " " << banker->get_money() << endl;
	for (int i = 1; i <= n; ++ i)
		cout << player[i]->name << " " << player[i]->get_money() << endl;
	
}
