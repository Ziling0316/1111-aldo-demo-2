#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::stringstream;
using std::setw;

#define show_vec(v, split)                               \
    auto last = v.back(); v.pop_back();                  \
    for(auto& x : v)                                     \
        std::cout << x << split;                         \
    v.push_back(last);                                   \
    std::cout << last << std::endl;
        
struct Student{
    char _class;
    int _id;
    Student(const string& s): _class(s.front()), _id(stoi(s.substr(1))){}; 
    bool operator>(const Student& b){
        if(_class == b._class){
            return _id < b._id;  //( "A123" < "A022" ) = 1
        }
        else return _class > b._class;//( "B034" > "A022" ) = 1
    }
    friend std::ostream& operator<<(std::ostream& out, Student& v) {
        out.fill('0'); 
        out << v._class << setw(3) << v._id;
        return out;
    }
};

void Insertion_sort(vector<Student>& a){
    int j;
    for(int i = 1; i < a.size(); i++){
        j = i;
        Student v = a[i];
        while(j>0 && a[j-1] > v){
            a[j] = a[j-1];
            j--;
        }
        a[j] = v;
        show_vec(a,',')
    }
}

int main(){
    string input, str;
    vector <Student> students;
    getline(cin, input);
    stringstream ss(input);
    while(getline(ss, str, ',')){
        students.emplace_back(str);
    }
    Insertion_sort(students);
    return 0;
}