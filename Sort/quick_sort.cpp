#include <iostream>
#include <cctype>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::stringstream;
using std::ostream;
using std::swap;
using std::map;
using std::transform;

map <char, int> suit_map{
    {'H', 4},
    {'S', 3},
    {'D', 2},
    {'C', 1}
};

map <char, int> num_map{
    {'A', 14},{'a', 14},{'j', 11},{'J', 11},{'q', 12},{'Q', 12},{'k', 13},{'K', 13}
};


#define show_vec(v, split)                               \
    auto last = v.back(); v.pop_back();                  \
    for(auto& x : v)                                     \
        cout << x << split;                              \
    v.push_back(last);                                   \
    cout << last << endl;
        

struct Cards{
    char _suit;
    int _number;
    string _name;
    Cards( string& s ){ 
        transform(s.begin(), s.end(), s.begin(), ::toupper);
        _suit = toupper(s.front());
        _number = num_map[s.back()] ? num_map[s.back()] : stoi(s.substr(1));
        _name = s.substr(1);
        };
    bool operator<(const Cards& b){
        if(_suit == b._suit){ 
            return _number <b._number;}
        else { return suit_map[_suit] < suit_map[b._suit]; }
    }
    friend ostream& operator<<(ostream& out, Cards& v){
        out << v._suit << v._name;
        return out;
    }
};
int Partition(vector<Cards>& a, int left, int right){
    int i = left-1;
    Cards v = a[right];
    for(int j = left; j < a.size(); j++){
        if(a[j] < v) { 
            i++; 
            swap(a[i], a[j]);
        }
    }
    i++;
    swap(a[i],a[right]);
    return i;
}
void Quick_sort(vector<Cards>& a, int left, int right){
    if(left < right){
        int i = Partition(a, left, right);
        show_vec(a, ',')
        Quick_sort(a, left, i-1);
        Quick_sort(a, i+1, right);   
    }
}
    

int main(){
    string input, str;
    vector <Cards> cards;
    getline(cin, input);
    stringstream ss(input);
    while(getline(ss, str, ',')){
        cards.emplace_back(str); 
    }
    show_vec(cards,',')
    Quick_sort(cards, 0, cards.size()-1);
    return 0;
}