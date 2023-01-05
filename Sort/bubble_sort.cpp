#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

// \ 把換行忽略
#define show_vec(v)                                             \
    for( int i = 0; i < v.size(); i++)                          \
        if(i != v.size()-1) {  std::cout << v[i] << ";"; }      \
        else                {  std::cout << v[i] <<std::endl; }

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::stringstream;
using std::swap;

void Bubble_sort(vector<int>& a){
    int flag, tmp;
    do
    {
        flag = 0;
        for(int i = 1; i < a.size(); i++){
            if( a[i] < a[i-1] ){
                swap(a[i-1], a[i]);
                show_vec(a)
                flag = 1;
            }
        }
    }while(flag == 1);
}

int main() {
    string input;
    int n;
    vector <int> nums;
    getline(cin, input);
    stringstream ss(input);
    while(ss >> n){
        ss.ignore(50, ';');
        nums.push_back(n);
    }
    Bubble_sort(nums);
    return 0;
}