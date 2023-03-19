#include <iostream>
#include <string>
#include <algorithm>
#include "10993.h"
using namespace std;

Polynomial::Polynomial(){
    greatestPower = 0;
    for(int i=0; i<51; i++) coefficients[i] = 0;
}
Polynomial::Polynomial(const int power, const int arr[51]){
    for(int i=0; i<=power; i++) coefficients[i] = arr[i];
    for(int i=power+1; i<51; i++) coefficients[i] = 0;
    greatestPower = power;
}
Polynomial Polynomial::add( const Polynomial b) const{
    Polynomial temp;
    temp.greatestPower = max(greatestPower, b.greatestPower);
    for(int i=0; i<=temp.greatestPower; i++){
        temp.coefficients[i] = coefficients[i] + b.coefficients[i];
    }
    while(temp.coefficients[temp.greatestPower] == 0){
        temp.greatestPower--;
    }
    return temp;
}
Polynomial Polynomial::subtract( const Polynomial b) const{
    Polynomial temp;
    temp.greatestPower = max(greatestPower, b.greatestPower);
    for(int i=0; i<=temp.greatestPower; i++){
        temp.coefficients[i] = coefficients[i] - b.coefficients[i];
    }
    while(temp.coefficients[temp.greatestPower] == 0){
        temp.greatestPower--;
    }
    return temp;
}
Polynomial Polynomial::multiplication( const Polynomial b) const{
    Polynomial temp;
    temp.greatestPower = greatestPower + b.greatestPower;
    for(int i=0; i<=greatestPower; i++) for(int j=0; j<=b.greatestPower; j++){
        temp.coefficients[i+j] += coefficients[i] * b.coefficients[j];
    }
    return temp;
}
void Polynomial::output() const{
    for(int i=greatestPower; i>=0; i--){
        i == 0 ? cout << coefficients[i] : cout << coefficients[i] << " ";
    }
}