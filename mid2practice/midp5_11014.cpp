#include <iostream>
#include <string>
#include <cctype>
#include <sstream>
using namespace std;
class Codec {
public:
    virtual void encode() = 0;
    virtual void decode() = 0;
    virtual ~Codec() { } // Do nothing
    virtual void show(std::ostream& os) const = 0;
    virtual bool is_encoded() const = 0;
};

class DummyCodec: public Codec {
public:
    DummyCodec(std::string s): encoded{false}, code_str{s} { }

    void encode() {
        encoded = true;
    }

    void decode() {
        encoded = false;
    }

    void show(std::ostream& os) const {
        os << code_str;
    }

    bool is_encoded() const { return encoded; }

private:
    bool encoded;
    std::string code_str;
};

class RleCodec: public Codec
{
public:
    RleCodec(std::string s): encoded{false}, code_str{s} { }


    void encode();

    void decode();

    void show(std::ostream& os) const {
        os << code_str;
    }

    bool is_encoded() const { return encoded; }


private:
    bool encoded;
    std::string code_str;
};

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



std::ostream& operator<<(std::ostream& os, Codec& data)
{
    data.show(os);
    return os;
}

void encode_decode(Codec & data)
{
    if (!data.is_encoded())
        data.encode();
    else
        data.decode();
}


int main()
{
    std::string input_string;
    std::cin >> input_string;

    DummyCodec dummy{input_string};
    encode_decode(dummy);
    std::cout << "Dummy encoding: ";
    std::cout << dummy << std::endl;
    encode_decode(dummy);
    std::cout << "Dummy decoding: ";
    std::cout << dummy << std::endl;

    RleCodec rle{input_string};
    encode_decode(rle);
    std::cout << "RLE encoding: ";
    std::cout << rle << std::endl;
    encode_decode(rle);
    std::cout << "RLE decoding: ";
    std::cout << rle << std::endl;
}

