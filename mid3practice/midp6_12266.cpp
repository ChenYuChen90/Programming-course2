#include <iostream>
#include <map>
using namespace std;

map<string, string> map_poke = {
    {"Wa",	"Waninoko"},
    {"Mi",	"Milotic"},
    {"Ma",	"Magikarp"},
    {"Va",	"Vaporeon"},
    {"Sh",	"Sharpedo"},
    {"Tapu",	"Tapu Fini"},
    {"Em",	"Empoleon"},
    {"La",	"Lapras"},
    {"Pi",	"Pikachu"},
    {"Pe",	"Pikachu"},
    {"Me",	"Mega Gyarados"}
};

int main(){
    int N;
    cin >> N;
    while(N--){
        string name, school;
        cin >> name >> school;
        if(name.length() > 2 && map_poke.find(name.substr(0, 2)) != map_poke.end()) {
            cout << name + " the " + school + " " + map_poke[name.substr(0, 2)] << endl;
        } else if (name.length() > 4 && map_poke.find(name.substr(0, 4)) != map_poke.end()) {
            cout << name + " the " + school + " " + map_poke[name.substr(0, 4)] << endl;
        } else {
            cout << name + " is looking for a Chinese tutor, too!" << endl;
        }
    }
    return 0;
}