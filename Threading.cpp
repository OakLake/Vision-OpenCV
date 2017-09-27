// C++ threading example: Producer Consumer
// Sammy Hasan

# include <thread>
# include <mutex>
# include <queue>
# include <iostream>

using namespace std;


// making thread safe Queue
template<class T>
class SafeQueue{
  queue<T> q;
  mutex m;

public:
  void push(T elem){
    lock_guard<mutex> lock(m);
    q.push(elem);
    cout << "Pushed: " << elem << endl;
  }
  T pull(){
    lock_guard<mutex> lock(m);
    T elem = q.front();
    q.pop();
    return elem;
  }
};

SafeQueue<int> sq;

void push_call(int x){
  for(int i = 1;i <10;i++){
  sq.push(i);
  }
}
void pull_call(){
  for(int i = 0;i <10;i++){
  int y = sq.pull();
  cout << "Pulled: " << y << endl;
  }
}

int main(){

  int x = 3;

  sq.push(0);


  thread pull_th(pull_call);
  thread push_th(push_call,x);

  pull_th.join();
  push_th.join();

  cout << "Programme Terminated" << endl;
  return 0;
}
