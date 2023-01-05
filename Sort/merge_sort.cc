#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Merge sort 
void merge(vector<int>& arr, int low, int high, int mid, int num)
{
    int i, j, k, c[50];
    i = low;
    k = low;
    j = mid + 1;
    while (i <= mid && j <= high) {
        if (arr[i] < arr[j]) {
            c[k] = arr[i];
            k++;
            i++;
        }
        else  {
            c[k] = arr[j];
            k++;
            j++;
        }
    }
    while (i <= mid) {
        c[k] = arr[i];
        k++;
        i++;
    }
    while (j <= high) {
        c[k] = arr[j];
        k++;
        j++;
    }
    for (i = low; i < k; i++)  {
        arr[i] = c[i];
    }
    for (i = 0; i < num; i++)  {
        cout << arr[i] << " ";
    }
    cout << endl;
}
// read input array and call mergesort
void merge_sort(vector<int>& arr, int low, int high, int num)
{
    int mid;
    if (low < high){
        //divide the array at mid and sort independently using merge sort
        mid=(low+high)/2;
        merge_sort(arr,low,mid,num);
        merge_sort(arr,mid+1,high,num);
        //merge or conquer sorted arrays
        merge(arr,low,high,mid, num);
    }
}
int main()
{
    int num;
    vector<int> my_array;
    string input;
    getline(cin, input);
    stringstream ss(input);
    while(ss >> num){
        ss.ignore(50, ',');
        my_array.push_back(num);
    }
    num = my_array.size();
    merge_sort(my_array, 0, num-1, num);
    cout<<"Sorted array\n";
    for (int i = 0; i < num; i++)
    {
        cout<<my_array[i]<<" ";
    }
}