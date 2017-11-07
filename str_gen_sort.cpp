// String Generator

# include <string>
# include <fstream>
# include <random>
# include <iostream>

using namespace std;


int main(){
    int min = 4; // mins num of chars
    int max = 7; // max num of chars
    int num_strings = 10000; // num if strings/words


    // file to save strings to
    ofstream output("output.txt");

    // loop for number of words
    for(int i=0;i<num_strings;i++){

      // simple status update
      cout << "\r::Generating Sting Prog ..... " << 100*(i+1)/num_strings << "\%" << flush;

      // generate random number between min and max of chars in a string.
      int randNum =  rand()%(max-min + 1) + min; // StackOverflow ::> 124525123/ (range) + shift;
      string gen(randNum,' '); // generate empty string
      generate(gen.begin(),gen.end(),[](){return 'A' + rand()%26;}); // generate random chars 'A' is converted to int
      output << gen << "\n"; // pipe to file

    }

    cout << endl;
    output.close();

    // Sorting
    // 1 - Load (subset of) strings
    // 2 - sort with std::sort
    // 3 - save
    // (4) - new subset and repeat.
    // (5) - MergeSort.

    ifstream input("output.txt"); // input file stream
    string word; // placeholder
    vector<string> words; // for storing all the words
    // populate vector with words from file
    while(getline(input,word)){
      words.push_back(word);
    }
    cout << "loaded all words" << endl;
    sort(words.begin(),words.end()); // standard sort
    cout << "sorted all words" << endl;
    // save to sorted file
    ofstream output2("sorted.txt");
    for(string w : words){
      output2 << w << "\n";
    }


    return 0;


}
