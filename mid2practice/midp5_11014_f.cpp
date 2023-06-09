#include <iostream>
#include <string>
#include <cctype>
#include <sstream>
using namespace std;
void RleCodec::encode()
{
    encoded = true;
    stringstream ss;
    int head = 0;
    for(int i = 1; i < code_str.length() + 1; i++) {
        if(i == code_str.length() || code_str[i] != code_str[head]) {
            if(i - head <= 2) ss << code_str.substr(head, i - head);
            else ss << i - head << code_str[head];
            head = i;
        }
    }
    code_str = ss.str();
}

void RleCodec::decode()
{
    encoded = false;
    stringstream ss;
    for(int i = 0; i < code_str.length(); i++) {
        if(isdigit(code_str[i])){
            int j = i+1;
            while(isdigit(code_str[j])) j++;
            ss << string(stoi(code_str.substr(i, j-i)), code_str[j]);
            i = j;
        } else {
            ss << code_str[i];
        }
    }
    code_str = ss.str();
}