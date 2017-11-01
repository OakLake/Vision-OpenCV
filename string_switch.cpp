// String switcher
#include <iostream>
#include <string>
#include <list>


using namespace std;

bool my_find(list<char> l,char c){
  bool present = std::find(std::begin(l), std::end(l), c) != std::end(l);
  return present;
}



int main(){

  string s = "Sammy Hasan";
  int l = s.length();

  string my_s = s;

  bool present;
  list<char> closed_list; // closed list

  for (int c = 0; c<l-1; c++){

    present = my_find(closed_list, s[c]);

    if (!present){

      for(int cn = c+1; cn<l; cn++){

        if(!my_find(closed_list, s[cn])){
          cout << "my_s: " <<my_s << endl;
          char temp = s[c];
          my_s[c] = s[cn];
          my_s[cn] = temp;

          // add to closed list
          closed_list.push_back(s[c]);
          closed_list.push_back(s[cn]);
          break;
        }
      }
    }
  }
  cout << "Original: " << s << " Changed: " << my_s << endl;

  return 0;
}
