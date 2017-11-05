// Basic genetic algorithm C++
// Sammy Hasan
// 2017

/*

fitness = number of ones


*/

# include <iostream>
# include <string>
# include <vector>
# include <random>
# include <algorithm>
# include <cstdlib>
//# include <boost/thread.hpp>
//# include <boost/chrono.hpp>

using namespace std;


string create_R_xome(int);
int fitness (string);
string mutate(string);
string crossover(string,string,int);
bool isFitter (string,string);
void print_str_vec(vector<string>);

int main(int argc, char const *argv[]) {




  // cout << "Define population size (int): ";
  int popSize = 20;
  // cin >> popSize;
  // cout << endl;

  // cout << "Define chromosome size (int): ";
  int xSize = 10;
  // cin >> xSize;
  // cout << endl;


  vector<string> population;

  for (int i=0;i<popSize;i++){
    population.push_back(create_R_xome(xSize)); // create initial population
  }


  int epochs = 14;
  int s70 = popSize*0.7;
  int s30 = popSize-s70;

  // Genetic stuff here
  for(int e=0;e<epochs;e++){
    cout << "Epoch: " << e << "######################" << endl;
    print_str_vec(population);
    // grading the fitness of the chromosomes and sorting vector with fittest at the begining
    sort(population.begin(),population.end(), isFitter);

    // delete worst 30% of population
    population.erase(population.begin()+s70,population.end());

    // generate new 30% from top 70%
    vector<string> popCopy = population;
    for (int r=0;r<s30;r++){
      random_shuffle(popCopy.begin(),popCopy.end());
      string parent1,parent2,child;
      parent1 = popCopy.back();
      popCopy.pop_back();
      parent2 = popCopy.back();
      popCopy.pop_back();
      child = crossover(parent1,parent2,xSize/2);
      population.push_back(child);
    }


    // apply mutation here
    vector<string> mutated;
    transform(population.begin(),population.end(),back_inserter(mutated),[](string s){return mutate(s);});
    population = mutated;

  }
/*
*/
  return 0;
}

////////////////////////////////////////////////////////////////////////////////

double my_rand(){
  random_device rd;
  mt19937 gen(rd());
  uniform_real_distribution<> dis(0.0, 1.0);
  return dis(gen);
}


string create_R_xome(int xSize){
  string xString;

  for(int x = 0;x<xSize;x++){
    if ( my_rand() > 0.5)
      xString += "1";
    else
      xString += "0";
  }
  return xString;
}

int fitness(string xs){
  int count = 0;
  for(char c : xs){
    if (c == '1')
      count++;
    }
  return count;
}

bool isFitter (string xa,string xb){
  return fitness(xa) > fitness(xb);
}

string mutate(string xs){
  for (int c=0;c<xs.length();c++){
    if(my_rand() < 0.01){
      xs[c] = xs[c] == '1'? '0':'1';
    }
  }
  return xs;

}

string crossover(string p1,string p2,int xpt){
  string xc1 = p1.substr(0,xpt) + p2.substr(xpt,p2.length());
  string xc2 = p2.substr(0,xpt) + p1.substr(xpt,p1.length());
  if (rand()%2 == 0)
    xc1 = xc2;

  return xc1;

}

void print_str_vec(vector<string> vec){
  cout << "Population::" << endl;
  for(string s : vec){
    cout << s << "  ::  " << fitness(s) << "\n";
  }
}
