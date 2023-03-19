
#include <iostream>
#include <cstring>
#include <cstdio>
using namespace oj;

namespace oj {
class BigInt {
private:
	char *_val;
	int half_adder(const int pos, const int & c){
		if(_val[pos] + c > '9'){
			_val[pos] = 0;
			return 1;
		} else {
			_val[pos]++;
			return 0;
		}
	}
	void add_one(){
		int carry = 1;
		for(int i = strlen(_val) - 1; i >= 0 && carry; i--){
			carry = half_adder(i, carry);
		}
		if(carry){
			char *new_val = new char[strlen(_val) + 2];
			new_val[0] = '1';
			strcpy(&new_val[1], _val);
			delete _val;
			_val = new_val;
		}
	}
	
	void truncate() {
        if (strlen(_val) > 1 && _val[0] != '0') return;
        else if (strlen(_val) == 1) return;
        char* new_val = new char[strlen(_val) + 1];
        strcpy(new_val, _val + 1);	// ???
        delete _val;
        _val = new_val;
    }
	
	int half_subtractor(const int pos, const int & b){
		if(_val[pos] - b < '0'){
			_val[pos] = '9';
			return 1;
		} else {
			_val[pos]--;
			return 0;
		}
	}
	void sub_one(){
		if(_val[0] == '0') return;
		int borrow = 1;
		for(int i = strlen(_val) - 1; i >= 0 && borrow; i--){
			borrow = half_subtractor(i, borrow);
		}
		truncate();
	}
public:
	BigInt(char *s);
  	~BigInt();
  	BigInt& operator++();
  	BigInt operator++(int);
  	BigInt& operator--();
  	BigInt operator--(int);
  	char* to_s();
};
}  // namespace oj

namespace oj
{
	BigInt::BigInt(char *s){
		_val = new char[strlen(s) + 1];
		strcpy(_val, s);
	}
	BigInt::~BigInt(){
		delete _val;
	}
	BigInt & BigInt::operator++(){
		add_one();
		return (*this);
	}
	BigInt BigInt::operator++(int){
		BigInt *copy = new BigInt(_val);
		add_one();
		return (*copy);
	}
	BigInt & BigInt::operator--(){
		sub_one();
		return (*this); 
	}
	BigInt BigInt::operator--(int){
		BigInt *copy = new BigInt(_val);
		sub_one();
		return (*copy);
	}
}


int main() {
  static char s[1024];

  int T;
  std::scanf("%d", &T);
  while (T--) {
    scanf("%s", s);
    BigInt B(s);

    int Q;
    std::scanf("%d", &Q);

    while (Q--) {
      char op[5];
      scanf("%s", op);
      if (!strcmp(op, "++B")) std::printf("%s\n", (++B).to_s());
      if (!strcmp(op, "B++")) std::printf("%s\n", (B++).to_s());
      if (!strcmp(op, "--B")) std::printf("%s\n", (--B).to_s());
      if (!strcmp(op, "B--")) std::printf("%s\n", (B--).to_s());
    }
  }

  return 0;
}
