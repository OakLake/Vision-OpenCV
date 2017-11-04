// Morse code C++
// Sammy Hasan
// 2017


# include <iostream>
# include <string>
# include <sstream>
# include <fstream>
# include <vector>
# include <map>


std::vector<std::string> split_string(const std::string s){
    std::istringstream ss(s);
    std::string item;
    std::vector<std::string> tokens;

    while(std::getline(ss,item,',')){
      tokens.push_back(item);
    }
    return tokens;
}


int main(){

  std::ifstream morse_file("morse_file.txt");
  std::ofstream morse_out("morse_text_code.txt");

  std::map<std::string,std::string> morse_map;
  std::map<std::string,std::string> morse_map_rev;

  std::vector<std::string> buffer;
  std::string line;
  while(getline(morse_file,line)){
    buffer = split_string(line);
    morse_map.insert(std::pair<std::string,std::string> (buffer[0],buffer[1]));
    // morse_map_rev.insert(std::pair<std::string,std::string> (buffer[1],buffer[0]));
  }

  for(auto b : morse_map){
    std::cout << b.first << "  ::  " << b.second << std::endl;
  }

  std::cout << "enter text to morsify" << std::endl;
  std::string text;
  std::getline(std::cin,text);
  morse_out << text << "\n\n\n";

  for (char cc : text ){
    cc = (char)::tolower(cc);
    std::string l(1,cc);

    if(morse_map.find(l) != morse_map.end()){
      l = morse_map[l];
    }
    std::cout << l << " ";
    morse_out << l;
  }
  std::cout << std::endl;

  morse_file.close();
  morse_out.close();
  return 0;
}



/*
//morse_file.txt

a,._
b,_...
c,_._.
d,_..
e,.
f,.._.
g,_ _.
h,....
i,..
j,._ _ _
k,_._.
l,._..
m,_ _
n,_.
o,_ _ _
p,._ _.
q,_ _._
r,._.
s,...
t,_
u,.._
v,..._
w,._ _
x,_.._
y,_.__
z,_ _..
1,._ _ _ _
2,.._ _ _
3,..._ _
4,...._
5,.....
6,_....
7,_ _..
8,_ _ _.
9,_ _ _ _.
0,_ _ _ _ _

*/
