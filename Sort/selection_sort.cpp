#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

// \ 把換行忽略
#define show_vec(v)                                             \
    for( int i = 0; i < v.size(); i++)                          \
        if(i != v.size()-1) {  std::cout << v[i] << ","; }      \
        else                {  std::cout << v[i] <<std::endl; }

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::stringstream;
using std::swap;

void Selection_sort(vector<int>& a){
    int min, tmp;
    for(int i = 0; i < a.size(); i++){
        min = i;
        for(int j = i+1; j < a.size(); j++){
            if( a[j] < a[min]) min = j;
        }
        swap(a[min], a[i]);
        if(min != i) { show_vec(a) }
    }
}
int main(){
    string input;
    int n;
    vector <int> nums;
    getline(cin, input);
    stringstream ss(input);
    while(ss >> n){
        ss.ignore(50, ',');
        nums.push_back(n);
    }
    Selection_sort(nums);
    return 0;
}