#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

// Shell sort
void shellSort(int array[], int n) {
  int h = 1;
    do{
        h = h*3+1; //找到比N大的最小值
    }while(h <= n);

  for (int interval = h / 3; interval > 0; interval /= 3) {
    cout << endl;
    cout << "original: " << endl;
    cout << endl;
    for(int i = 0; i<n-1; i++){
        cout << array[i] << ',';
    } 
    cout << array[n-1] << endl; 
    for (int i = interval; i < n; i++) {
      int temp = array[i];
      int j;
      for (j = i; j >= interval && array[j - interval] > temp; j -= interval) {
        array[j] = array[j - interval];
      }
      array[j] = temp;
    }
    h/=3;
    cout << endl;
    cout << "h = " << h << endl;
    cout << endl;
    for(int i = 0; i < n; i++){
        if(i == n-1) {cout << array[i] << endl;}
        else       {cout << array[i] << ",";}
        if(i%h == h-1) { cout << endl; }
    }            
  }
}

int main() {
    string input;
    int n, i = 0;
    int nums[51];
    getline(cin, input);
    stringstream ss(input);
    while(ss >> n){
        ss.ignore(50, ',');
        nums[i] = n;
        i++;
    }
  shellSort(nums, i);
}