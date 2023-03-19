#include <iostream>
using namespace std;

int find_idx(int *arr, int tmp, int n);

int main(){
    int N;
    int arr[200005];
    cin >> N;
    for(int i = 0; i < N; i++){
        cin >> arr[i];
    }
    int tmp;
    while(cin >> tmp){
        cout << find_idx(arr, tmp, N) << endl;
    }
    return 0;
}

int find_idx(int *arr, int tmp, int n){
    int left = 0, right = n - 1;
    while(left <= right){
        int middle = (left + right) / 2;
        if(tmp < arr[middle]) right = middle - 1;
        else if(tmp > arr[middle]) left = middle + 1;
        else return middle;
    }
    return -1;
}