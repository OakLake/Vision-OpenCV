// prime divisor
# include <iostream>

using namespace std;

bool is_prime(int n)
{
  bool result = true;
  for(int i = 2; i <= n / 2; ++i)
  {
      if(n % i == 0)
      {
          result = false;
          break;
      }
  }
  return result;
}


int main(){

  int n = 45;

  for(int i = n-1;i>1;i--){
    // first, check divisor
    if (n%i == 0){
      // second check if prime
      bool isPrimeDiv = is_prime(i);
      // add to list
      if (isPrimeDiv){
        // primeDivsList.push_back(i);
        cout << i << endl;
        // should be of max first due to decrementation of i
      }
    }
  }


}
