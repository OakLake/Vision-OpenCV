// Cellular Automata with * in terminal
// Sammy Hasan
// 2017

/*
rule 30 for chaos
*/
# include <iostream>
# include <cstdlib>
# include <algorithm>
# include <vector>
# include <bitset>
# include <thread>
# include <chrono>

using namespace std;


int t(int i,int j, int k,const int rule){
  string result = " ";
  // cout << j << " : "<< i << " : " << k << endl;
  string binary;
  binary = to_string(j) + to_string(i) + to_string(k);

  unsigned int ix = bitset<32>(binary).to_ulong();
  string rule_str = bitset<8>(rule).to_string();

  result = rule_str[rule_str.length()-ix-1];
  // cout << "Rule: " << rule_str << " Result: " << result << " ix: " << ix << endl;
  return stoi(result);
}

int main(int argc, const char** argv){

  int rule = 30;
  if (argc >= 2){
    rule = atoi (argv[1]);
  }

  cout << "Using Rule: " << rule << endl;

  vector<int> stream(70);
  vector<int> padded;

  generate(stream.begin(),stream.end(),[](){return rand()%2;});

  for(int x = 0;x<5000;x++){
    this_thread::sleep_for(chrono::milliseconds(100));
    padded = stream;
    padded.insert(padded.begin(),stream.front());
    padded.insert(padded.end(),stream.back());
    stream.clear();
    for(auto i = padded.begin()+1; i != padded.end()-1;i++){
      // t(*i,*(i-1),*(i+1),rule);
      stream.push_back(t(*i,*(i-1),*(i+1),rule));
    }


    for(int i : stream){
      cout << ((i == 1)? "\u25A0" : " ");
    }
    cout << endl;

  }




  return 0;
}
