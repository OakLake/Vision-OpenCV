// file read/write in c++
// Sammy Hasan
// 2017


/*
reads from file and outputs data to another file,
also reads number of lines
*/
# include <fstream>
# include <iostream>


int main(int argc, char const *argv[]) {


  std::ofstream output_file;
  std::ifstream input_file("input.txt");

  output_file.open("output.txt"); // key.pub viable ?



  if (!input_file){
    std::cout << "File doesn't exist" << std::endl;
    return 1;
  }

  char c;
  int count = 0;

  while(input_file.get(c)){
    output_file << c; // output to file
    if (c == '\n'){
      count++;
    }
  }
  output_file << std::endl;
  output_file.close();
  std::cout << "Total Lines: " << count << std::endl;


  return 0;
}
