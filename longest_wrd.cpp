#include <iostream>
#include <sstream>

using namespace std;

string LongestWord(string sen) {

  // code goes here
  istringstream iss(sen);
  string word;
  string out_wrd;

  while(iss >> word){
    out_wrd = word.length() > out_wrd.length() ? word:out_wrd;
  }
  
  return out_wrd;

}

int main() {

  // keep this function call here
  string sentence = "Hello World this is thelongest";
  cout << LongestWord(sentence) << endl;
  return 0;

}
